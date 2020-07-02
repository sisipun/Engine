#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"

class Engine
{
public:
    Engine();

    bool init();

    bool loadMedia();

    void update();

    void handleInput();

    bool isQuit();

    void close();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event *event;
    bool quit;
};

#endif