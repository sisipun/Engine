#ifndef TIMER_H
#define TIMER_H

#include "SDL_types.h"
#include "SDL.h"

class Timer
{
public:
    Timer();

    void start();

    void stop();

    Uint32 getTicks();

private:
    Uint32 mStartTicks;
    bool mStarted;
};

#endif