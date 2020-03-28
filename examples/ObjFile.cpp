#include <FastBVH/BVH.h>
#include <FastBVH/Traverser.h>

#include <vector>

#include <cstdio>
#include <cstdlib>

#include "Log.h"
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
class FaceBoxConverter final {
  //! Contains all the vertices from the .obj file.
  //! Used to find the bounding box of a face.
  const tinyobj::attrib_t& attrib;
public:
  //! Constructs a new instance of the box converter.
  //! @param attrib_ Used to resolve the face indices
  //! into points that can be used to determine the
  //! bounding box of a face.
  FaceBoxConverter(const tinyobj::attrib_t& attrib_)
    : attrib(attrib_) {}
  //! Converts a face to a bounding box.
  //! \param face The face to get the bounding box of.
  //! \return The bounding box that fits the specified face.
  FastBVH::BBox<float> operator () (const Face& face) const noexcept {

    FastBVH::Vector3<float> pos_a = {
      attrib.vertices[(face.pos[0] * 3) + 0],
      attrib.vertices[(face.pos[0] * 3) + 1],
      attrib.vertices[(face.pos[0] * 3) + 2]
    };

    FastBVH::Vector3<float> pos_b = {
      attrib.vertices[(face.pos[1] * 3) + 0],
      attrib.vertices[(face.pos[1] * 3) + 1],
      attrib.vertices[(face.pos[1] * 3) + 2]
    };

    FastBVH::Vector3<float> pos_c = {
      attrib.vertices[(face.pos[2] * 3) + 0],
      attrib.vertices[(face.pos[2] * 3) + 1],
      attrib.vertices[(face.pos[2] * 3) + 2]
    };

    auto min = FastBVH::min(pos_a, pos_b);
    auto max = FastBVH::max(pos_a, pos_b);

    min = FastBVH::min(min, pos_c);
    max = FastBVH::max(max, pos_c);

    return FastBVH::BBox<float>(min, max);
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
      faces.emplace_back(Face {
        {
          shape.mesh.indices[i - 2].vertex_index,
          shape.mesh.indices[i - 1].vertex_index,
          shape.mesh.indices[i - 0].vertex_index
        },
        {
          shape.mesh.indices[i - 2].texcoord_index,
          shape.mesh.indices[i - 1].texcoord_index,
          shape.mesh.indices[i - 0].texcoord_index
        }
      });
    }
  }

  return faces;
}

} // namespace

int main(int argc, char** argv) {

  const char* filename = (argc > 1) ? argv[1] : nullptr;

  if (!filename) {
    std::fprintf(stderr, "No .obj file provided.\n");
    return EXIT_FAILURE;
  }

  tinyobj::ObjReader reader;

  std::printf("Reading '%s'\n", filename);

  if (!reader.ParseFromFile(filename)) {

    std::fprintf(stderr, "%s: %s",
                 filename,
                 reader.Error().c_str());

    return EXIT_FAILURE;
  }

  std::printf("Combining faces\n");

  auto faces = combineFaces(reader.GetShapes());

  std::printf("Building BVH\n");

  FaceBoxConverter boxConverter(reader.GetAttrib());

  FastBVH::BVH<float, Face> bvh;

  FastBVH::Stopwatch stopwatch;

  bvh.build(std::move(faces), boxConverter);

  auto time = stopwatch.read();

  std::printf("Completing BVH in %.02f ms\n", time * 1000.0);

  return EXIT_SUCCESS;
#if 0
  BVH<float, Sphere<float>> bvh;

  SphereBoxConverter<float> boxConverter;

  Stopwatch sw;

  // Compute a BVH for this object set
  bvh.build(std::move(objects), boxConverter);

  // Output tree build time and statistics
  double constructionTime = sw.read();

  LOG_STAT("Built BVH (%u nodes, with %u leafs) in %.02f ms",
           (unsigned int) bvh.getNodeCount(),
           (unsigned int) bvh.getLeafCount(),
           1000.0 * constructionTime);

  // Allocate space for some image pixels
  const unsigned int width=800, height=800;
  float* pixels = new float[width*height*3];

  // Create a camera from position and focus point
  Vector3<float> camera_position { 1.6, 1.3, 1.6 };
  Vector3<float> camera_focus { 0,0,0 };
  Vector3<float> camera_up { 0,1,0 };

  // Camera tangent space
  Vector3<float> camera_dir = normalize(camera_focus - camera_position);
  Vector3<float> camera_u = normalize(camera_dir ^ camera_up);
  Vector3<float> camera_v = normalize(camera_u ^ camera_dir);

  SphereIntersector<float> intersector;

  Traverser<float, Sphere<float>, decltype(intersector)> traverser(bvh, intersector);

  printf("Rendering image (%dx%d)...\n", width, height);
  // Raytrace over every pixel
  for(size_t i=0; i<width; ++i) {
    for(size_t j=0; j<height; ++j) {
      size_t index = 3*(width * j + i);

      float u = (i+.5f) / (float)(width-1) - .5f;
      float v = (height-1-j+.5f) / (float)(height-1) - .5f;
      float fov = .5f / tanf( 70.f * 3.14159265*.5f / 180.f);

      // This is only valid for square aspect ratio images
      Ray<float> ray(camera_position, normalize(camera_u*u + camera_v*v + camera_dir*fov));

      auto I = traverser.traverse(ray, false);

      if(!I) {
        pixels[index] = pixels[index+1] = pixels[index+2] = 0.f;
      } else {

        // Just for fun, we'll make the color based on the normal

        const Vector3<float> color {
          std::fabs(I.normal.x),
          std::fabs(I.normal.y),
          std::fabs(I.normal.z)
        };

        pixels[index  ] = color.x;
        pixels[index+1] = color.y;
        pixels[index+2] = color.z;
      }
    }
  }

  // Output image file (PPM Format)
  printf("Writing out image file: \"render.ppm\"\n");
  FILE *image = fopen("render.ppm", "w");
  fprintf(image, "P6\n%d %d\n255\n", width, height);
  for(size_t j=0; j<height; ++j) {
    for(size_t i=0; i<width; ++i) {
      size_t index = 3*(width * j + i);
      unsigned char r = std::max(std::min(pixels[index  ]*255.f, 255.f), 0.f);
      unsigned char g = std::max(std::min(pixels[index+1]*255.f, 255.f), 0.f);
      unsigned char b = std::max(std::min(pixels[index+2]*255.f, 255.f), 0.f);
      fprintf(image, "%c%c%c", r,g,b);
    }
  }
  fclose(image);

  // Cleanup
  delete[] pixels;
#endif
}
