#include "engine/engine.h"
#include "engine/actor/actor.h"
#include "engine/logger/logger.h"
#include "utils/constants.h"
#include "controller/user_controller.h"
#include "scene/main_scene.h"

int main(int argc, char *argv[])
{
    Engine engine;
    if (!engine.init(SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        Logger::log("Failed to initialize!\n");
        return -1;
    }

    std::vector<Actor *> actors;
    Actor *info = new Actor("hero", {10, 10, 10, 10}, 0, 0);
    Actor *info2 = new Actor("actor2", {20, 20, 10, 10}, 2, 2);
    actors.push_back(info);
    actors.push_back(info2);

    std::vector<Controller *> controllers;
    Controller *userController = new UserController("hero");
    controllers.push_back(userController);

    Scene* mainScene = new MainScene();

    if (!engine.loadMedia(mainScene, actors, controllers))
    {
        Logger::log("Failed to load media!\n");
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