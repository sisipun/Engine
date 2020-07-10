#include "engine/engine.h"
#include "engine/actor/actor.h"
#include "engine/logger/logger.h"
#include "utils/constants.h"
#include "scene/main_scene.h"
#include "actor/hero.h"

int main(int argc, char *argv[])
{
    Engine engine;
    if (!engine.init(SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        Logger::log("Failed to initialize!\n");
        return -1;
    }

    std::vector<Actor *> actors;
    Actor *info = new Hero("hero", {10, 10, 10, 10}, 0, 0);
    actors.push_back(info);

    Scene* mainScene = new MainScene();

    if (!engine.loadMedia(mainScene, actors))
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