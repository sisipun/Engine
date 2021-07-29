#include "timer.h"

Timer::Timer() noexcept
{
	last = std::chrono::steady_clock::now();
}

float Timer::mark() noexcept
{
	const std::chrono::steady_clock::time_point old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> markTime = last - old;
	return markTime.count();
}

float Timer::peek() noexcept
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
}