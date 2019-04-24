#ifndef Stopwatch_h
#define Stopwatch_h

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/time.h>

class Stopwatch {
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
	double read() const {	return _stopwatch() - start; }
};
#else

#include <numeric>
#include <chrono>
class Stopwatch {
private:
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock>  _stopwatch() const
    {
        return std::chrono::system_clock::now();
    }

public:
    Stopwatch() { reset(); }
    void reset() { start = _stopwatch(); }

    // return second
    double read() const
    {
        std::chrono::duration<double> diff = _stopwatch() - start;
        return diff.count();
    }
};

#endif
#endif
