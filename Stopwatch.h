#pragma once

#include <sys/time.h>

namespace FastBVH {

class Stopwatch final {
  private:
    double start;
    double _stopwatch() const
    {
      struct timeval time;
      gettimeofday(&time, 0 );
      return 1.0 * time.tv_sec + time.tv_usec / (double)1e6;
    }
  public:
    Stopwatch() { reset(); }
    void reset() { start = _stopwatch(); }
    double read() const { return _stopwatch() - start; }
};

} // namespace FastBVH
