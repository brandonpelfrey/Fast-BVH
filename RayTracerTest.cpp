#include <cstdio>
#include <vector>
#include <cstdlib>
#include "BVH.h"
#include "Sphere.h"
using std::vector;

// Return a random number in [0,1]
float rand01() {
  return rand() * (1.f / RAND_MAX);
}

// Return a random vector with each component in the range [-1,1]
Vector3 randVector3() {
  return Vector3(rand01(), rand01(), rand01())*2.f - Vector3(1,1,1);
}

int main(int argc, char **argv) {

  // Create a million spheres packed in the space of a cube
  const unsigned int N = 1000000;
  vector<Object*> objects;
  printf("Constructing %d spheres...\n", N);
  for(size_t i=0; i<N; ++i) {
    objects.push_back(new Sphere(randVector3(), .005f));
  }

  // Compute a BVH for this object set
  BVH bvh(&objects);

  // Allocate space for some image pixels
  const unsigned int width=800, height=800;
  float* pixels = new float[width*height*3];

  // Create a camera from position and focus point
  Vector3 camera_position(1.6, 1.3, 1.6);
  Vector3 camera_focus(0,0,0);
  Vector3 camera_up(0,1,0);

  // Camera tangent space
  Vector3 camera_dir = normalize(camera_focus - camera_position);
  Vector3 camera_u = normalize(camera_dir ^ camera_up);
  Vector3 camera_v = normalize(camera_u ^ camera_dir);

  printf("Rendering image (%dx%d)...\n", width, height);
  // Raytrace over every pixel
#pragma omp parallel for
  for(size_t i=0; i<width; ++i) {
    for(size_t j=0; j<height; ++j) {
      size_t index = 3*(width * j + i);

      float u = (i+.5f) / (float)(width-1) - .5f;
      float v = (height-1-j+.5f) / (float)(height-1) - .5f;
      float fov = .5f / tanf( 70.f * 3.14159265*.5f / 180.f);

      // This is only valid for square aspect ratio images
      Ray ray(camera_position, normalize(u*camera_u + v*camera_v + fov*camera_dir));

      IntersectionInfo I;
      bool hit = bvh.getIntersection(ray, &I, false);

      if(!hit) {
        pixels[index] = pixels[index+1] = pixels[index+2] = 0.f;
      } else {

        // Just for fun, we'll make the color based on the normal
        const Vector3 normal = I.object->getNormal(I);
        const Vector3 color(fabs(normal.x), fabs(normal.y), fabs(normal.z));

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
