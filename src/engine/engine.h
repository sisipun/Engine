#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include <vector>
#include <map>
#include <string>
#include "actor/actor.h"
#include "actor/actor_info.h"
#include "controller/controller.h"
#include "time/timer.h"

class Engine
{
public:
    Engine();

    bool init();

    bool loadMedia(std::vector<ActorInfo *> infos, std::vector<Controller *> controllers);

    void update();

    void handleInput();

    bool isQuit();

    void close();

    Actor *getActor(std::string name);

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event *event;
    bool quit;

    Timer *timer;
    float delta;

    std::map<std::string, Actor *> actors;
    std::map<std::string, Controller *> controllers;
};

#endif