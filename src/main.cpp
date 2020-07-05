#include <iostream>
#include "controller/user_controller.h"
#include "engine/engine.h"
#include "engine/actor/actor_info.h"

int main(int argc, char *argv[])
{
    Engine engine;
    if (!engine.init())
    {
        printf("Failed to initialize!\n");
        return -1;
    }

    std::vector<ActorInfo *> infos;
    ActorInfo *info = new ActorInfo("actor1", {10, 10, 10, 10}, 0, 0);
    ActorInfo *info2 = new ActorInfo("actor2", {20, 20, 10, 10}, 2, 2);
    infos.push_back(info);
    infos.push_back(info2);

    std::vector<Controller *> controllers;
    Controller *userController = new UserController("actor1");
    controllers.push_back(userController);

    if (!engine.loadMedia(infos, controllers))
    {
        printf("Failed to load media!\n");
        return -1;
    }

    for (ActorInfo *info : infos)
    {
        delete info;
    }

    infos.clear();

    while (!engine.isQuit())
    {
        engine.update();
        engine.handleInput();
    }
    engine.close();
    return 0;
}