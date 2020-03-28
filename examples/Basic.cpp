#include <cstdio>
#include <vector>
#include <cstdlib>

#include <FastBVH/BVH.h>
#include <FastBVH/Traverser.h>

#include "Log.h"
#include "Sphere.h"
#include "Stopwatch.h"

namespace {

using std::vector;

using namespace FastBVH;

// Return a random number in [0,1]
float rand01() {
  return rand() * (1.f / RAND_MAX);
}

// Return a random vector with each component in the range [-1,1]
Vector3<float> randVector3() {
  return Vector3<float> { rand01(), rand01(), rand01() } * 2.0f - Vector3<float> { 1, 1, 1 };
}

//! Used for calculating the bounding boxes
//! associated with spheres.
//! \tparam Float The floating point type of the sphere and bounding box vectors.
template <typename Float>
class SphereBoxConverter final {
public:
  //! Converts a sphere to a bounding box.
  //! \param sphere The sphere to convert to a bounding box.
  //! \return A bounding box that encapsulates the sphere.
  BBox<Float> operator () (const Sphere<Float>& sphere) const noexcept {

    const auto& r = sphere.r;

    auto box_delta = Vector3<Float> { r, r, r };

    return BBox<Float>(sphere.center - box_delta,
                       sphere.center + box_delta);
  }
};

} // namespace

int main() {

  // Create a million spheres packed in the space of a cube
  const unsigned int N = 1000000;

  vector<Sphere<float>> objects;

  printf("Constructing %d spheres...\n", N);
  for(size_t i=0; i<N; ++i) {
    objects.emplace_back(Sphere<float>(randVector3(), .005f));
  }

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

  Traverser<float, Sphere<float>> traverser(bvh);

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
        const Vector3<float> normal = getNormal(*I.object, I);

        const Vector3<float> color {
          std::fabs(normal.x),
          std::fabs(normal.y),
          std::fabs(normal.z)
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
}
