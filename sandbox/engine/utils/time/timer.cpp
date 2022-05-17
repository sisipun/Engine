#include "timer.h"

Timer::Timer()
{
    mStartTicks = 0;

    mStarted = false;
}

void Timer::start()
{
    mStartTicks = SDL_GetTicks();

    mStarted = true;
}

void Timer::stop()
{
    mStartTicks = 0;

    mStarted = false;
}

Uint32 Timer::getTicks() const
{
    Uint32 time = 0;
    if (mStarted)
    {
        time = SDL_GetTicks() - mStartTicks;
    }
    return time;
}