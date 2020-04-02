#pragma once

namespace FastBVH {

namespace benchmark {

//! \brief A single triangular face from a mesh.
//! The positions and UV coordinates are indexed.
//! In this example, an instance of 'Face' is a geometric primitive.
struct Face final {
  //! The indices to each position of the face.
  int pos[3];

  //! The indices to each UV coordinate.
  int uv[3];
};

} // namespace benchmark

} // namespace FastBVH
