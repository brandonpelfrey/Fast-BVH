#pragma once

#include <fstream>
#include <vector>

namespace FastBVH {

//! A simple ray scheduler.
//! This is used to generate primary rays and plot
//! the colors that they return.
//! \tparam Float The floating point type to use for the generated rays.
template <typename Float>
class SimpleScheduler final {
  /// The image pixel data.
  std::vector<unsigned char> pixels;

  //! The width of the image to produce.
  std::size_t img_x_res;

  //! The height of the image to produce.
  std::size_t img_y_res;

  //! The position of the camera in world space.
  Vector3<Float> camera_position{1.6, 1.3, 1.6};

  //! Where the camera is looking at.
  Vector3<Float> camera_focus{0, 0, 0};

  //! The direction of 'up' in camera space.
  Vector3<Float> camera_up{0, 1, 0};

 public:
  //! Constructs a new scheduler.
  //! \param img_w The width of the image to produce.
  //! \param img_h The height of the image to produce.
  SimpleScheduler(std::size_t img_w, std::size_t img_h) {
    pixels.resize(img_w * img_h * 3);
    img_x_res = img_w;
    img_y_res = img_h;
  }

  //! Moves the camera to a different location.
  //! \param pos The position, in world space, to move the camera to.
  void moveCamera(const Vector3<Float>& pos) { camera_position = pos; }

  //! Schedules rays to be traced.
  //! \tparam Tracer The type of the tracer kernel.
  //! \param tracer The tracer kernel that maps rays to colors.
  template <typename Tracer>
  void schedule(Tracer tracer) {
    // Camera tangent space
    Vector3<Float> camera_dir = normalize(camera_focus - camera_position);
    Vector3<Float> camera_u = normalize(cross(camera_dir, camera_up));
    Vector3<Float> camera_v = normalize(cross(camera_u, camera_dir));

    auto fov = Float(0.5f) / std::tan(70.f * 3.14159265 * .5f / 180.f);

    auto* pixel = pixels.data();

    for (std::size_t y = 0; y < img_y_res; y++) {
      for (std::size_t x = 0; x < img_x_res; x++) {
        auto u = (x + 0.5f) / (Float)(img_x_res - 1) - 0.5f;
        auto v = (img_y_res - 1 - y + Float(0.5f)) / (Float)(img_y_res - 1) - 0.5f;

        // This is only valid for square aspect ratio images
        Ray<float> ray(camera_position, normalize(camera_u * u + camera_v * v + camera_dir * fov));

        auto color = tracer(ray);

        pixel[0] = color.x * 255;
        pixel[1] = color.y * 255;
        pixel[2] = color.z * 255;

        pixel += 3;
      }
    }
  }

  //! Saves the result of the render operation to a PPM image file.
  //! \param filename The name of the file to save the results to.
  //! \return True on success, false on failure.
  bool saveResults(const char* filename) {
    std::ofstream file(filename);
    if (!file.good()) {
      return false;
    }

    file << "P6" << std::endl;
    file << img_x_res << std::endl;
    file << img_y_res << std::endl;
    file << "255" << std::endl;

    file.write((const char*)pixels.data(), pixels.size());

    return true;
  }
};

}  // namespace FastBVH
