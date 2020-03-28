Getting Started
===============

### Installation

Since Fast-BVH is a header-only library, all you have to to is get the header files into an include directory your project can use.

You can do this either by:

 - Copying all the files into a directory in your project, like `third-party/Fast-BVH/include` or something similar
 - Add the project to yours as a [git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules)
 - Download a ZIP file of the project and extract it to your a place in your project

If your project uses CMake, you can add Fast-BVH as a subdirectory and link to the target `FastBVH` and CMake will take care of adding the include directories to the targets that use the library.
For example:

```cmake
add_subdirectory(third-party/Fast-BVH)

target_link_libraries(myAwesomeRayTracer PRIVATE FastBVH)
```

Note that even though the command is called `target_link_libraries`, there's no linking or compilation taking place.
In CMake, `FastBVH` is an "interface" library. This means that it's only meant to relay things like include directories, compiler flags, etc.

### Preparing the Scene Data

Most ray tracers use primitive shapes to build a scene.
For this example, we'll be using a sphere as a primitive shape.
Just note that we could also be using a triangle, a voxel, or polygonal surface.
Here's an example of our scene so far:

```cxx
#include <vector>

struct Sphere final {
  float x;
  float y;
  float z;
  float radius;
};

int main() {

  std::vector<Sphere> spheres;
  spheres.emplace_back({ 0, 0, 0, 0.1 });
  spheres.emplace_back({ 2, 0, 0, 1.0 });
  spheres.emplace_back({ 1, 3, 2, 0.5 });

  return 0;
}
```

In order to glue this scene to a format that Fast-BVH can use, we'll need to
define a class that converts our spheres to bounding boxes. We'll call this
class `SphereBoxConverter`.

```cxx
#include <FastBVH/BBox.h>

class SphereBoxConverter final {
public:
  FastBVH::BBox<float> operator () (const Sphere<float>& s) const noexcept {

    FastBVH::Vector3<float> min {
      s.x - s.radius,
      s.y - s.radius,
      s.z - s.radius
    };

    FastBVH::Vector3<float> max {
      s.x + s.radius,
      s.y + s.radius,
      s.z + s.radius
    };

    return FastBVH::BBox<float>(min, max);
  }
};
```

We could also have done this in a lambda functor:

```cxx
auto boxConverter = [](const Sphere<float>& s) {

  /* Calculate min and max */

  return FastBVH::BBox<float>(min, max);
};
```

Now we're ready to create our first BVH.

### Building a BVH

Start by including the directory for the @ref FastBVH::BVH data structure.

```cxx
#include <FastBVH/BVH.h>

/* SphereBoxConverter goes here */

int main() {

  /* Create spheres as above */

  FastBVH::BVH<float, Sphere> bvh;

  SphereBoxConverter boxConverter;

  bvh.build(spheres, boxConverter);

  /* We now have our first BVH! */

  return 0;
}
```

### Traversing the BVH

