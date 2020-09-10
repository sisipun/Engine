#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"
#include "SDL_types.h"

class Timer
{
public:
    Timer();

    void start();

    void stop();

    Uint32 getTicks() const;

private:
    Uint32 mStartTicks;
    bool mStarted;
};

#endif