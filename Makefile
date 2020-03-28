DOXYGEN := doxygen

CXXFLAGS := -Wall -Wextra -Werror -Wfatal-errors
CXXFLAGS := $(CXXFLAGS) -I $(CURDIR)/include
CXXFLAGS := $(CXXFLAGS) -std=c++14

VPATH += include/fast_bvh

headers := include/FastBVH/BBox.h \
           include/FastBVH/BVH.h \
           include/FastBVH/IntersectionInfo.h \
           include/FastBVH/Log.h \
           include/FastBVH/Ray.h \
           include/FastBVH/Stopwatch.h \
           include/FastBVH/Traverser.h \
           include/FastBVH/Vector3.h

examples := examples/Basic

.PHONY: all
all: simple-target

.PHONY: simple-target
simple-target: $(examples)

examples/Basic: examples/Basic.cpp $(headers)

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
