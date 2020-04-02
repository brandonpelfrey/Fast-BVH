# Optionally set the compiler in this file.
-include config.mk

CXXFLAGS := -Wall -Wextra -Werror -Wfatal-errors
CXXFLAGS := $(CXXFLAGS) -I ../include
CXXFLAGS := $(CXXFLAGS) -O3 -ffast-math

g++_CXXFLAGS := $(CXXFLAGS) -fverbose-asm -fopt-info-vec-missed

clang++_CXXFLAGS := -Rpass-missed=loop-vectorize

.PHONY: all
all: MortonCurve.lst

MortonCurve.lst: MortonCurve.s
	$(AS) -alhnd $< >$@

.DELETE_ON_ERROR: MortonCurve.s

MortonCurve.s: MortonCurve.cpp
	$(CXX) -S $(CXXFLAGS) $($(CXX)_CXXFLAGS) $<

.PHONY: clean
clean:
	$(RM) *.s
