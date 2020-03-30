#include <FastBVH.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Log.h"
#include "SimpleScheduler.h"
#include "Stopwatch.h"
#include "tiny_obj_loader.h"

namespace {

//! \brief A single triangular face from a mesh.
//! The positions and UV coordinates are indexed.
//! In this example, an instance of 'Face' is a geometric primitive.
struct Face final {
  //! The indices to each position of the face.
  int pos[3];

  //! The indices to each UV coordinate.
  int uv[3];
};

//! \brief Converts a face into a bounding box.
//! Used by @ref FaceBVH::BVH during the build process.
class FaceBoxConverter final {
  /// The minimum X values of the mesh faces.
  std::vector<float> min_x;

  /// The minimum Y values of the mesh faces.
  std::vector<float> min_y;

  /// The minimum Z values of the mesh faces.
  std::vector<float> min_z;

  /// The maximum X values of the mesh faces.
  std::vector<float> max_x;

  /// The maximum Y values of the mesh faces.
  std::vector<float> max_y;

  /// The maximum Z values of the mesh faces.
  std::vector<float> max_z;

 public:
  //! Constructs a new instance of the box converter.
  //! \param attrib Used to resolve the face indices
  //! into points that can be used to determine the
  //! bounding box of a face.
  //! \param faces The faces of the mesh.
  FaceBoxConverter(const tinyobj::attrib_t& attrib, const std::vector<Face>& faces) {
    min_x.resize(faces.size());
    min_y.resize(faces.size());
    min_z.resize(faces.size());

    max_x.resize(faces.size());
    max_y.resize(faces.size());
    max_z.resize(faces.size());

    for (std::size_t i = 0; i < faces.size(); i++) {
      const auto& face = faces[i];

      FastBVH::Vector3<float> pos_a = {attrib.vertices[(face.pos[0] * 3) + 0], attrib.vertices[(face.pos[0] * 3) + 1],
                                       attrib.vertices[(face.pos[0] * 3) + 2]};

      FastBVH::Vector3<float> pos_b = {attrib.vertices[(face.pos[1] * 3) + 0], attrib.vertices[(face.pos[1] * 3) + 1],
                                       attrib.vertices[(face.pos[1] * 3) + 2]};

      FastBVH::Vector3<float> pos_c = {attrib.vertices[(face.pos[2] * 3) + 0], attrib.vertices[(face.pos[2] * 3) + 1],
                                       attrib.vertices[(face.pos[2] * 3) + 2]};

      auto min = FastBVH::min(pos_a, pos_b);
      auto max = FastBVH::max(pos_a, pos_b);

      min = FastBVH::min(min, pos_c);
      max = FastBVH::max(max, pos_c);

      min_x[i] = min.x;
      min_y[i] = min.y;
      min_z[i] = min.z;

      max_x[i] = max.x;
      max_y[i] = max.y;
      max_z[i] = max.z;
    }
  }

  //! Converts a face to a bounding box.
  //! \param face_index The index of the face to get the bounding box of.
  //! \return The bounding box that fits the specified face.
  FastBVH::BBox<float> operator()(std::size_t face_index) const noexcept {
    FastBVH::Vector3<float> min{
        min_x[face_index],
        min_y[face_index],
        min_z[face_index],
    };

    FastBVH::Vector3<float> max{
        max_x[face_index],
        max_y[face_index],
        max_z[face_index],
    };

    return FastBVH::BBox<float>(min, max);
  }
};

//! \brief Checks for intersection between a ray and a face.
//! Used by @ref FaceBVH::Traverse during BVH traversal.
class FaceIntersector final {
  //! Contains the object file vertices and texture coordinates.
  const tinyobj::attrib_t& attrib;

  //! The faces in the object file.
  const std::vector<Face>& faces;

 public:
  //! \brief Constructs a new instance of a face intersector.
  //! Normally, at this point, we'd pre-compute some more acceleration data,
  //! but we're going to keep this example short and sweet.
  FaceIntersector(const tinyobj::attrib_t& attrib_, const std::vector<Face>& faces_) : attrib(attrib_), faces(faces_) {}

  FastBVH::Intersection<float, uint32_t> operator()(uint32_t face_index, const FastBVH::Ray<float>& ray) const
      noexcept {
    const auto& face = faces[face_index];

    FastBVH::Vector3<float> v0 = {attrib.vertices[(face.pos[0] * 3) + 0], attrib.vertices[(face.pos[0] * 3) + 1],
                                  attrib.vertices[(face.pos[0] * 3) + 2]};

    FastBVH::Vector3<float> v1 = {attrib.vertices[(face.pos[1] * 3) + 0], attrib.vertices[(face.pos[1] * 3) + 1],
                                  attrib.vertices[(face.pos[1] * 3) + 2]};

    FastBVH::Vector3<float> v2 = {attrib.vertices[(face.pos[2] * 3) + 0], attrib.vertices[(face.pos[2] * 3) + 1],
                                  attrib.vertices[(face.pos[2] * 3) + 2]};

    // Basic Möller and Trumbore algorithm

    auto v0v1 = v1 - v0;
    auto v0v2 = v2 - v0;

    auto pvec = cross(ray.d, v0v2);

    auto det = dot(v0v1, pvec);

    if (std::fabs(det) < std::numeric_limits<float>::epsilon()) {
      return FastBVH::Intersection<float, uint32_t>{};
    }

    auto inv_det = 1.0f / det;

    auto tvec = ray.o - v0;

    auto u = dot(tvec, pvec) * inv_det;

    if ((u < 0) || (u > 1)) {
      return FastBVH::Intersection<float, uint32_t>{};
    }

    auto qvec = cross(tvec, v0v1);

    auto v = dot(ray.d, qvec) * inv_det;

    if ((v < 0) || (u + v) > 1) {
      return FastBVH::Intersection<float, uint32_t>{};
    }

    auto t = dot(v0v2, qvec) * inv_det;

    // At this point, we know we have a hit.
    // We just need to calculate the UV coordinates.

    float uv[2] = {u, v};

    // Some .obj files don't have texture coordinates.
    // Ideally, we'd check this outside side of an intersector.
    // For this example, it'll have to do.

    if (attrib.texcoords.size() > 0) {
      int vt0i[2] = {(face.uv[0] * 2) + 0, (face.uv[0] * 2) + 1};
      int vt1i[2] = {(face.uv[1] * 2) + 0, (face.uv[1] * 2) + 1};
      int vt2i[2] = {(face.uv[2] * 2) + 0, (face.uv[2] * 2) + 1};

      float vt0[2] = {attrib.texcoords[vt0i[0]], attrib.texcoords[vt0i[1]]};
      float vt1[2] = {attrib.texcoords[vt1i[0]], attrib.texcoords[vt1i[1]]};
      float vt2[2] = {attrib.texcoords[vt2i[0]], attrib.texcoords[vt2i[1]]};

      uv[0] = vt0[0] * (1.0f - u - v);
      uv[1] = vt0[1] * (1.0f - u - v);

      uv[0] += vt1[0] * u;
      uv[1] += vt1[1] * u;

      uv[0] += vt2[0] * v;
      uv[1] += vt2[1] * v;
    }

    return FastBVH::Intersection<float, uint32_t>{t, &face_index, {0, 0, 1}, {uv[0], uv[1]}};
  }
};

//! Combines all the face indices so that we can render the
//! object as a single mesh, instead of a collection of meshes.
//! \param shapes The shapes from the obj file to combine.
//! \return An array of face indices.
std::vector<Face> combineFaces(const std::vector<tinyobj::shape_t>& shapes) {
  std::vector<Face> faces;

  for (const auto& shape : shapes) {
    for (std::size_t i = 2; i < shape.mesh.indices.size(); i += 3) {
      faces.emplace_back(Face{{shape.mesh.indices[i - 2].vertex_index, shape.mesh.indices[i - 1].vertex_index,
                               shape.mesh.indices[i - 0].vertex_index},
                              {shape.mesh.indices[i - 2].texcoord_index, shape.mesh.indices[i - 1].texcoord_index,
                               shape.mesh.indices[i - 0].texcoord_index}});
    }
  }

  return faces;
}

//! Finds a good place for the camera to view the object.
//! \param bvh The BVH containing the object primitives.
//! \return A position in world space to place the camera at.
FastBVH::Vector3<float> findGoodCameraPosition(const FastBVH::BVH<float, uint32_t>& bvh) {
  FastBVH::Vector3<float> pos{0, 0, -1};

  if (!bvh.getNodes().size()) {
    return pos;
  }

  const auto& root_node = bvh.getNodes()[0];

  const auto& root_box = root_node.bbox;

  auto diagonal_length = length(root_box.extent);

  pos.x = diagonal_length * 0.3;
  pos.y = diagonal_length * 0.8;
  pos.z = diagonal_length * 0.9;

  return pos;
}

}  // namespace

int main(int argc, char** argv) {
  const char* filename = (argc > 1) ? argv[1] : nullptr;
  if (!filename) {
    std::fprintf(stderr, "No .obj file provided.\n");
    return EXIT_FAILURE;
  }

  tinyobj::ObjReader reader;

  std::printf("Reading '%s'\n", filename);
  if (!reader.ParseFromFile(filename)) {
    std::fprintf(stderr, "%s: %s", filename, reader.Error().c_str());

    return EXIT_FAILURE;
  }

  std::printf("Combining faces\n");
  auto faces = combineFaces(reader.GetShapes());

  std::vector<std::uint32_t> face_indices;
  face_indices.resize(faces.size());
  for (std::size_t i = 0; i < face_indices.size(); i++) {
    face_indices[i] = std::uint32_t(i);
  }

  std::printf("Building BVH\n");
  FastBVH::Stopwatch stopwatch;

  FaceBoxConverter box_converter(reader.GetAttrib(), faces);

  FastBVH::BuildStrategy<float, 1> build_strategy;

  auto bvh = build_strategy(face_indices, box_converter);

  auto time = stopwatch.read();
  std::printf("Completing BVH in %.02f ms\n", time * 1000.0);

  stopwatch.reset();
  FaceIntersector intersector(reader.GetAttrib(), faces);

  FastBVH::Traverser<float, uint32_t, decltype(intersector)> traverser(bvh, intersector);
  auto traceKernel = [traverser](const FastBVH::Ray<float>& ray) {
    auto isect = traverser.traverse(ray);
    if (isect) {
      return FastBVH::Vector3<float>{isect.uv[0], isect.uv[1], 1};
    } else {
      return FastBVH::Vector3<float>{0, 0, 0};
    }
  };

  FastBVH::SimpleScheduler<float> scheduler(800, 800);
  scheduler.moveCamera(findGoodCameraPosition(bvh));
  scheduler.schedule(traceKernel);

  time = stopwatch.read();
  std::printf("Model rendered in %.02f ms\n", time * 1000.0);

  scheduler.saveResults("render2.ppm");
  return EXIT_SUCCESS;
}
