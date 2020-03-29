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
class `SphereBoxConverter`. Note that we also include the `FastBVH.h` header.

```cxx
#include <FastBVH.h>

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

When constructing a BVH, there are many different algorithms that have their own trade offs
between build time and quality of the BVH. In this library, we separate these algorithms into
what are called "strategies." It's beyond the scope of this tutorial to go through the different
algorithms, so we'll just be using the @ref DefaultBuilder type definition and stick with that.

```cxx
#include <FastBVH.h>

/* SphereBoxConverter goes here */

int main() {

  /* Create spheres as above */

  FastBVH::DefaultBuilder<float> builder;

  SphereBoxConverter box_converter;

  auto bvh = builder(spheres, box_converter);

  /* We now have our first BVH! */

  return 0;
}
```

The next step is to traverse rays through the BVH, calculating the ray-primitive intersections.

### Traversing the BVH

Fast-BVH comes with a BVH traverser, for the sake of convenience.

In order to use it, you'll need to need to define a class that handles intersections between rays and primitives.

For our sphere class, it will look like this:

```cxx
class SphereIntersector final {
public:
  Intersection<float, Sphere> operator () (const Sphere& sphere, const Ray<float>& ray) noexcept {

    /* There's plenty of articles online on how to check
     * for intersection between a sphere and a ray, so we
     * won't repeat it here. We'll just name the variables
     * that you need to make a good intersection instance. */

    if (ray_missed) {
      /* This returns an intersection instance
       * that indicates a miss. */
      return Intersection<float, Sphere> { };
    }

    /* You'll need to calculate these values */

    /* The degree at which the ray
     * is scaled to meet the surface of the sphere. */
    float t = 0;

    /* The surface normal at the point of intersection. */
    FastBVH::Vector3<float> normal {
      0,
      0,
      0
    };

    return Intersection<float, Sphere> {
      t,
      &sphere,
      normal
    };
  }
};
```

Now that we've got our intersector class ready, we can traverse our BVH!

```cxx
/* Headers from the rest of the tutorial go here */

#include <FastBVH/Traverser.h>

/* Classes from the rest of the tutorial go here */

int main() {

  /* Here the spheres are created and then the BVH is built. */

  /* Generate primary rays */

  SphereIntersector intersector;

  BvhTraverser<float, Sphere, decltype(intersector)> traverser(bvh, intersector);

  for (const auto& ray : primary_rays) {
    auto isect = traverser.traverse(ray, false /* not an occlusion ray */);
    if (isect) {
      /* Ray hit. Plot the color
       * at the intersection and queue
       * the reflected, refracted rays */
      plotColor(isect);
      queueReflected(isect, reflected_rays);
      queueRefracted(isect, refracted_rays);
    } else {
      /* Ray missed. Do nothing.*/
    }
  }

  return 0;
}
```

And there you have it! If you want a more complete example, without anything missing, you can checkout one of the examples.
