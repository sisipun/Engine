#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
	Timer() noexcept;
	float mark() noexcept;
	float peek() noexcept;

private:
	std::chrono::steady_clock::time_point last;
};

#endif 