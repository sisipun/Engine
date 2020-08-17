#include "engine/engine.h"
#include "engine/actor/actor.h"
#include "engine/actor/actor_group.h"
#include "engine/actor/scene/scene.h"
#include "engine/utils/procedural_generation/chess_generator.h"
#include "engine/utils/procedural_generation/drunkard_walk_generator.h"
#include "engine/utils/procedural_generation/cellular_automata_generator.h"
#include "engine/utils/procedural_generation/bsp_generator.h"
#include "engine/utils/procedural_generation/box_generator.h"
#include "engine/utils/logger/logger.h"

#include "utils/constants.h"
#include "actor/hero.h"
#include "actor/wall.h"
#include "actor/mini_map.h"

int main(int argc, char *argv[])
{
    Engine engine;
    if (!engine.init(SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        Logger::log("Failed to initialize!\n");
        return -1;
    }

    RandomGenerator generator = RandomGenerator();

    std::vector<Actor *> actors;
    std::vector<Actor *> walls;

    int mapWidth = 10;
    int mapHeight = 10;
    DrunkardWalkGenerator *mapGenerator = new DrunkardWalkGenerator();
    Map *map = mapGenerator->generate(mapWidth, mapHeight, 30, generator);

    if (map->getValue() != nullptr)
    {
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
    }

    if (map->getStartY() - 1 >= 0 && *(map->getValue() + (map->getStartX() * map->getHeight()) + map->getStartY() - 1) == 0)
    {
        walls.push_back(new Wall("northWallLeft", {0, 0, (SCREEN_WIDTH / 2) - (DOOR_WIDTH / 2), WALL_WIDTH}, 0, 0));
        walls.push_back(new Wall("northWallRight", {(SCREEN_WIDTH / 2) + (DOOR_WIDTH / 2), 0, SCREEN_WIDTH, WALL_WIDTH}, 0, 0));
    }
    else
    {
        walls.push_back(new Wall("northWall", {0, 0, SCREEN_WIDTH, WALL_WIDTH}, 0, 0));
    }
    if (map->getStartY() + 1 < map->getHeight() && *(map->getValue() + (map->getStartX() * map->getHeight()) + map->getStartY() + 1) == 0)
    {
        walls.push_back(new Wall("southWallLeft", {0, SCREEN_HEIGHT - WALL_WIDTH, (SCREEN_WIDTH / 2) - (DOOR_WIDTH / 2), WALL_WIDTH}, 0, 0));
        walls.push_back(new Wall("southWallRight", {(SCREEN_WIDTH / 2) + (DOOR_WIDTH / 2), SCREEN_HEIGHT - WALL_WIDTH, SCREEN_WIDTH, WALL_WIDTH}, 0, 0));
    }
    else
    {
        walls.push_back(new Wall("southWall", {0, SCREEN_HEIGHT - WALL_WIDTH, SCREEN_WIDTH, WALL_WIDTH}, 0, 0));
    }
    if (map->getStartX() - 1 >= 0 && *(map->getValue() + ((map->getStartX() - 1) * map->getHeight()) + map->getStartY()) == 0)
    {
        walls.push_back(new Wall("westWallTop", {0, 0, WALL_WIDTH, (SCREEN_HEIGHT / 2) - (DOOR_WIDTH / 2)}, 0, 0));
        walls.push_back(new Wall("westWallBottom", {0, (SCREEN_HEIGHT / 2) + (DOOR_WIDTH / 2), WALL_WIDTH, SCREEN_HEIGHT}, 0, 0));
    }
    else
    {
        walls.push_back(new Wall("westWall", {0, 0, WALL_WIDTH, SCREEN_HEIGHT}, 0, 0));
    }
    if (map->getStartX() + 1 < map->getWidth() && *(map->getValue() + ((map->getStartX() + 1) * map->getHeight()) + map->getStartY()) == 0)
    {
        walls.push_back(new Wall("eastWallTop", {SCREEN_WIDTH - WALL_WIDTH, 0, WALL_WIDTH, (SCREEN_HEIGHT / 2) - (DOOR_WIDTH / 2)}, 0, 0));
        walls.push_back(new Wall("eastWallBottom", {SCREEN_WIDTH - WALL_WIDTH, (SCREEN_HEIGHT / 2) + (DOOR_WIDTH / 2), WALL_WIDTH, SCREEN_HEIGHT}, 0, 0));
    }
    else
    {
        walls.push_back(new Wall("eastWall", {SCREEN_WIDTH - WALL_WIDTH, 0, WALL_WIDTH, SCREEN_HEIGHT}, 0, 0));
    }

    actors.push_back(new ActorGroup("wallGroup", walls));
    actors.push_back(new Hero({SCREEN_WIDTH / 2,
                               SCREEN_HEIGHT / 2,
                               HERO_WIDTH,
                               HERO_HEIGHT},
                              0, 0));

    actors.push_back(new MiniMap({10, 10, WALL_WIDTH, WALL_WIDTH},
                                 map->getValue(),
                                 map->getWidth(),
                                 map->getHeight(),
                                 map->getStartX(),
                                 map->getStartY()));

    std::vector<std::string> mainSceneActors;
    mainSceneActors.push_back("hero");
    mainSceneActors.push_back("wallGroup");
    mainSceneActors.push_back("miniMap");
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