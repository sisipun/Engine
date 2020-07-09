#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "SDL_mixer.h"
#include <vector>
#include "actor/actor.h"
#include "controller/controller.h"
#include "storage/storage.h"
#include "scene/scene.h"
#include "time/timer.h"

class Engine
{
public:
    Engine();

    bool init(float screenWidth, float screenHeigh);

    bool loadMedia(Scene *startScene, std::vector<Actor *> actors, std::vector<Controller *> controllers);

    bool changeScene(Scene *scene);

    void update();

    void handleInput();

    bool isQuit();

    void close();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event *event;
    Storage *storage;
    Timer *timer;
    Scene *currentScene;
    float delta;

    bool quit;
};

#endif