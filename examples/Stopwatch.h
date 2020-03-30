#pragma once

#include <chrono>

namespace FastBVH {

//! \brief Used for profiling the performance
//! of the BVH construction.
class Stopwatch final {
  //! A type definition for the clock used by this class.
  using Clock = std::chrono::high_resolution_clock;

  //! A type definition for a single point in time.
  using TimePoint = Clock::time_point;

  //! A type definition for a duration of time.
  using Duration = std::chrono::duration<double>;

  //! The starting time of the stop watch.
  TimePoint start;

  //! Gets the current time.
  //! \return The current time.
  static TimePoint now() noexcept { return Clock::now(); }

 public:
  //! Constructs a new instance of the stopwatch.
  Stopwatch() noexcept { reset(); }

  //! Resets the stop watch to a new starting time.
  //! This should be called right before the profiling begins.
  void reset() noexcept { start = now(); }

  //! Reads the current time value from the stopwatch.
  //! \return The number of ellapsed seconds since either
  //! the construction of the stop watch or the last call
  //! to @ref Stopwatch::reset (which ever was more recent.)
  double read() const noexcept {
    return std::chrono::duration_cast<std::chrono::duration<double>>(now() - start).count();
  }
};

}  // namespace FastBVH
