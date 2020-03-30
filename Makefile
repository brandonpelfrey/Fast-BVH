DOXYGEN := doxygen

CXXFLAGS := -Wall -Wextra -Werror -Wfatal-errors
CXXFLAGS := $(CXXFLAGS) -I $(CURDIR)/include 
CXXFLAGS := $(CXXFLAGS) -std=c++14

VPATH += include/fast_bvh

headers := include/FastBVH.h \
           include/FastBVH/BBox.h \
           include/FastBVH/BuildStrategy1.h \
           include/FastBVH/BuildStrategy.h \
           include/FastBVH/BVH.h \
           include/FastBVH/Config.h \
           include/FastBVH/Intersection.h \
           include/FastBVH/Iterable.h \
           include/FastBVH/Ray.h \
           include/FastBVH/Traverser.h \
           include/FastBVH/Vector3.h

example_headers := examples/Log.h \
                   examples/SimpleScheduler.h \
                   examples/Stopwatch.h \
                   examples/tiny_obj_loader.h

examples := examples/CubeOfSpheres \
            examples/ObjFile

.PHONY: all
all: simple-target

.PHONY: simple-target
simple-target: $(examples)

examples/CubeOfSpheres: examples/CubeOfSpheres.cpp $(headers) $(example_headers)

examples/ObjFile: examples/ObjFile.cpp $(headers) $(example_headers)
	$(CXX) $(CXXFLAGS) -I $(CURDIR)/examples examples/tiny_obj_loader.cc $< -o $@

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
