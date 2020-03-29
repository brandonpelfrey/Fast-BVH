DOXYGEN := doxygen

CXXFLAGS := -Wall -Wextra -Werror -Wfatal-errors
CXXFLAGS := $(CXXFLAGS) -I $(CURDIR)/include
CXXFLAGS := $(CXXFLAGS) -std=c++14

VPATH += include/fast_bvh

headers := include/FastBVH/BBox.h \
           include/FastBVH/BVH.h \
           include/FastBVH/Intersection.h \
           include/FastBVH/Ray.h \
           include/FastBVH/Traverser.h \
           include/FastBVH/Vector3.h

example_headers := examples/Log.h \
                   examples/Stopwatch.h

examples := examples/CubeOfSpheres

.PHONY: all
all: simple-target

.PHONY: simple-target
simple-target: $(examples)

examples/CubeOfSpheres: examples/CubeOfSpheres.cpp $(headers) $(example_headers)

examples/%: examples/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(examples)

.PHONY: test
test:

.PHONY: docs
docs:
	$(DOXYGEN)
