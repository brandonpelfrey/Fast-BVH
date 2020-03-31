DOXYGEN := doxygen

CXXFLAGS := -Wall -Wextra -Werror -Wfatal-errors
CXXFLAGS := $(CXXFLAGS) -O3 -mtune=native -march=native
CXXFLAGS := $(CXXFLAGS) -I $(CURDIR)/include 
CXXFLAGS := $(CXXFLAGS) -std=c++14

VPATH += include/fast_bvh

headers := include/FastBVH.h \
           include/FastBVH/BBox.h \
           include/FastBVH/BuildStrategy.h \
           include/FastBVH/BVH.h \
           include/FastBVH/impl/Config.h \
           include/FastBVH/Intersection.h \
           include/FastBVH/Iterable.h \
           include/FastBVH/Ray.h \
           include/FastBVH/Traverser.h \
           include/FastBVH/Vector3.h \
           include/FastBVH/impl/Array.h \
           include/FastBVH/impl/Config.h \
           include/FastBVH/impl/Memory.h \
           include/FastBVH/impl/MortonCodec.h \
           include/FastBVH/impl/MortonCurve.h \
           include/FastBVH/impl/MortonTable.h \
           include/FastBVH/impl/MortonTraits.h \
           include/FastBVH/impl/Types.h \
           include/FastBVH/impl/VectorPacket.h

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
