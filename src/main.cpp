#include <iostream>
#include "controller/user_controller.h"
#include "engine/engine.h"
#include "engine/actor/actor.h"
#include "utils/constants.h"

int main(int argc, char *argv[])
{
    Engine engine;
    if (!engine.init(SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        printf("Failed to initialize!\n");
        return -1;
    }

    std::vector<Actor *> actors;
    Actor *info = new Actor("actor1", {10, 10, 10, 10}, 0, 0);
    Actor *info2 = new Actor("actor2", {20, 20, 10, 10}, 2, 2);
    actors.push_back(info);
    actors.push_back(info2);

    std::vector<Controller *> controllers;
    Controller *userController = new UserController("actor1");
    controllers.push_back(userController);

    if (!engine.loadMedia(actors, controllers))
    {
        printf("Failed to load media!\n");
        return -1;
    }

    while (!engine.isQuit())
    {
        engine.update();
        engine.handleInput();
    }
    engine.close();
    return 0;
}