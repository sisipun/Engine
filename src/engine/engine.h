#ifndef ENGINE_H
#define ENGINE_H

#include "actor/actor.h"
#include "context/context.h"
#include "utils/time/timer.h"

#include "SDL.h"
#include "SDL_mixer.h"
#include <vector>

class Engine
{
public:
    Engine();

    bool init(float screenWidth, float screenHeigh, std::vector<Actor *> actors);

    void update();

    void handleInput();

    bool isQuit();

    void close();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event *event;
    Context *context;
    Timer *timer;
    float delta;
    bool quit;
};

#endif