#include "engine/engine.h"
#include "engine/actor/actor.h"
#include "engine/actor/actor_group.h"
#include "engine/logger/logger.h"
#include "utils/constants.h"
#include "actor/hero.h"
#include "actor/wall.h"

int main(int argc, char *argv[])
{
    Engine engine;
    if (!engine.init(SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        Logger::log("Failed to initialize!\n");
        return -1;
    }

    std::vector<Actor *> actors;

    Hero *hero = new Hero({30, 30, 10, 10}, 0, 0);
    actors.push_back(hero);

    std::vector<Actor *> walls;
    Actor *northWall = new Wall("northWall", {0, 0, SCREEN_WIDTH, 20}, 0, 0);
    Actor *westWall = new Wall("westWall", {0, 0, 20, SCREEN_HEIGHT}, 0, 0);
    Actor *southWall = new Wall("southWall", {0, SCREEN_HEIGHT - 20, SCREEN_WIDTH, 20}, 0, 0);
    Actor *eastWall = new Wall("eastWall", {SCREEN_WIDTH - 20, 0, 20, SCREEN_HEIGHT}, 0, 0);

    walls.push_back(northWall);
    walls.push_back(westWall);
    walls.push_back(southWall);
    walls.push_back(eastWall);

    ActorGroup *wallGroup = new ActorGroup("wallGroup", walls);
    actors.push_back(wallGroup);

    std::vector<std::string> mainSceneActors;
    mainSceneActors.push_back("hero");
    mainSceneActors.push_back("wallGroup");
    Scene *mainScene = new Scene(mainSceneActors);

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