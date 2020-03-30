#include <FastBVH.h>

#include <algorithm>
#include <vector>
#include <sstream>

#include <cstdio>
#include <cstdlib>

#include "Face.h"
#include "FaceBoxConverter.h"
#include "FaceIntersector.h"
#include "Scheduler.h"

#include "../examples/Stopwatch.h"
#include "../examples/tiny_obj_loader.h"

namespace FastBVH {

namespace Benchmark {

namespace {

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

//! Contains the results of a single strategy benchmark.
struct StrategyResults final {
  //! The time it took to build the BVH.
  double build_time;
  //! The time it took to render the scene.
  double render_time;
};

//! Runs a benchmark.
//! \tparam strategy The BVH build strategy that was used.
//! \param faces The faces of the mesh to render.
//! \param attrib Contains the vertices and the texture coordinates of the mesh.
//! \return The results of the benchmark.
template <int strategy>
StrategyResults bench(const std::vector<Face>& faces, const tinyobj::attrib_t& attrib) {

  std::vector<std::uint32_t> face_indices;

  face_indices.resize(faces.size());

  for (std::size_t i = 0; i < face_indices.size(); i++) {
    face_indices[i] = std::uint32_t(i);
  }

  // Begins benchmarking the BVH construction here.

  FastBVH::Stopwatch stopwatch;

  FaceBoxConverter box_converter(attrib, faces);

  FastBVH::BuildStrategy<float, strategy> build_strategy;

  auto bvh = build_strategy(face_indices, box_converter);

  auto build_time = stopwatch.read();

  // Ends benchmarking BVH construction

  FaceIntersector intersector(attrib, faces);

  FastBVH::Traverser<float, uint32_t, decltype(intersector)> traverser(bvh, intersector);

  auto tracer = [traverser](const FastBVH::Ray<float>& ray) {
    auto isect = traverser.traverse(ray);
    if (isect) {
      return FastBVH::Vector3<float>{isect.uv[0], isect.uv[1], 1};
    } else {
      return FastBVH::Vector3<float>{0, 0, 0};
    }
  };

  auto observer = [](std::size_t line, std::size_t line_max) {

    auto percent_done = (line * 100.0f) / line_max;

    std::printf("\r  Percent Completion: %%%.02f", percent_done);

    std::fflush(stdout);
  };

  auto cam_pos = Vector3<float> {
    -1000, 1000, 0.0
  };

  auto cam_look_at = Vector3<float> {
    0, 0, 0
  };

  FastBVH::Benchmark::Scheduler<float> scheduler(2000, 2000);
  scheduler.moveCamera(cam_pos);
  scheduler.lookAt(cam_look_at);

  // Begins benchmarking ray tracing here

  stopwatch.reset();

  scheduler.schedule(tracer, observer);

  auto render_time = stopwatch.read();

  std::printf("\n");

  // Ends benchmarking ray tracing here

  std::ostringstream filename_stream;
  filename_stream << "benchmark_result_";
  filename_stream << strategy;
  filename_stream << ".ppm";

  scheduler.saveResults(filename_stream.str().c_str());

  return StrategyResults { build_time, render_time };
}

}  // namespace

} // namespace Benchmark

} // namespace FastBVH

#ifndef MODEL_PATH
#define MODEL_PATH "test_model/sponza.obj"
#endif

int main() {

  const char* filename = MODEL_PATH;

  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(filename)) {
    std::fprintf(stderr, "%s: %s", filename, reader.Error().c_str());
    return EXIT_FAILURE;
  }

  auto faces = FastBVH::Benchmark::combineFaces(reader.GetShapes());

  std::vector<FastBVH::Benchmark::StrategyResults> results;

  // Uncomment this if you'd like to either:
  //   - Generate a 'known good' image
  //   - Wait a really long time
  //
  //std::printf("Running benchmark for strategy 0\n");
  //results.emplace_back(FastBVH::Benchmark::bench<0>(faces, reader.GetAttrib()));

  std::printf("Running benchmark for strategy 1\n");
  results.emplace_back(FastBVH::Benchmark::bench<1>(faces, reader.GetAttrib()));

  std::printf("Results:\n");
  std::printf("              | Build Time (sec) | Render Time (sec) |\n");
  std::printf("              |------------------|-------------------|\n");

  for (std::size_t i = 0; i < results.size(); i++) {

    auto strategy = int(i + 0);
    auto btime = results[i].build_time;
    auto rtime = results[i].render_time;

    std::printf("  Strategy %02d | %8.04f         | %8.04f          |\n", strategy, btime, rtime);
  }

  return EXIT_SUCCESS;
}
