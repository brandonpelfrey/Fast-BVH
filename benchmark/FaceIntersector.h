#pragma once

#include <FastBVH/Intersection.h>
#include <FastBVH/Ray.h>

#include "Face.h"

#include "../examples/tiny_obj_loader.h"

#include <vector>

namespace FastBVH {

namespace Benchmark {

//! \brief Checks for intersection between a ray and a face.
//! Used by @ref FaceBVH::Traverse during BVH traversal.
class FaceIntersector final {
  //! Contains the object file vertices and texture coordinates.
  const tinyobj::attrib_t& attrib;

  //! The faces in the object file.
  const std::vector<Face>& faces;

 public:

  //! A simple type definition for a ray.
  using Ray = FastBVH::Ray<float>;

  //! A simple type definition for an intersection.
  using Intersection = FastBVH::Intersection<float, uint32_t>;

  //! \brief Constructs a new instance of a face intersector.
  //! Normally, at this point, we'd pre-compute some more acceleration data,
  //! but we're going to keep this example short and sweet.
  FaceIntersector(const tinyobj::attrib_t& attrib_, const std::vector<Face>& faces_) : attrib(attrib_), faces(faces_) {}

  Intersection operator()(uint32_t face_index, const Ray& ray) const noexcept {

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
    if (t < std::numeric_limits<float>::epsilon()) {
      return FastBVH::Intersection<float, uint32_t>{};
    }

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

} // namespace Benchmark

} // namespace FastBVH
