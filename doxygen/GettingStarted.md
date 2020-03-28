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

### Building a BVH

Now that you've got the project in a usable format, you can start building your first BVH.

Start by including the directory for the @ref FastBVH::BVH data structure.

```cxx
#include <fast_bvh/BVH.h>

int main() {

  return 0;
}
```
