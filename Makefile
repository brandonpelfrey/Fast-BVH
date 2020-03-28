CXXFLAGS := -Wall -Wextra -Werror -Wfatal-errors -msse3

.PHONY: all
all: simple-target

.PHONY: simple-target
simple-target: RayTracerTest

RayTracerTest: RayTracerTest.o BBox.o BVH.o
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

RayTracerTest.o: RayTracerTest.cpp BVH.h BBox.h Ray.h Vector3.h Log.h \
 Object.h IntersectionInfo.h Sphere.h

BBox.o: BBox.cpp BBox.h Ray.h Vector3.h Log.h

BVH.o: BVH.cpp BVH.h BBox.h Ray.h Vector3.h Log.h Object.h \
 IntersectionInfo.h Stopwatch.h

.PHONY: clean
clean:
	$(RM) RayTracerTest *.o

.PHONY: test
test: RayTracerTest
	./RayTracerTest
