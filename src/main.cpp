#include "engine/engine.h"
#include "engine/actor/actor.h"
#include "engine/actor/actor_group.h"
#include "engine/actor/scene/scene.h"
#include "engine/utils/procedural_generation/chess_generator.h"
#include "engine/utils/procedural_generation/drunkard_walk_generator.h"
#include "engine/utils/procedural_generation/cellular_automata_generator.h"
#include "engine/utils/procedural_generation/bsp_generator.h"
#include "engine/utils/logger/logger.h"

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
    std::vector<Actor *> walls;

    int mapWidth = SCREEN_WIDTH / WALL_WIDTH - 2;
    int mapHeight = SCREEN_HEIGHT / WALL_WIDTH - 2;
    BSPGenerator *mapGenerator = new BSPGenerator();
    Map *map = mapGenerator->generate(mapWidth, mapHeight);

    for (int i = 0; i < map->getWidth(); i++)
    {
        for (int j = 0; j < map->getHeight(); j++)
        {
            if (*(map->getValue() + (i * map->getHeight()) + j) == 1)
            {
                walls.push_back(new Wall(std::to_string(i), {static_cast<float>((i + 1) * WALL_WIDTH), static_cast<float>((1 + j) * WALL_WIDTH), WALL_WIDTH, WALL_WIDTH}, 0, 0));
            }
        }
    }

    walls.push_back(new Wall("northWall", {0, 0, SCREEN_WIDTH, 20}, 0, 0));
    walls.push_back(new Wall("westWall", {0, 0, 20, SCREEN_HEIGHT}, 0, 0));
    walls.push_back(new Wall("southWall", {0, SCREEN_HEIGHT - 20, SCREEN_WIDTH, 20}, 0, 0));
    walls.push_back(new Wall("eastWall", {SCREEN_WIDTH - 20, 0, 20, SCREEN_HEIGHT}, 0, 0));

    actors.push_back(new ActorGroup("wallGroup", walls));
    actors.push_back(new Hero({static_cast<float>(map->getStartX() + 1) * WALL_WIDTH,
                               static_cast<float>(map->getStartY() + 1) * WALL_WIDTH,
                               HERO_WIDTH,
                               HERO_HEIGHT},
                              0, 0));

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

    delete map;
    delete mapGenerator;
    engine.close();
    return 0;
}