#include "engine/engine.h"
#include "engine/actor/actor.h"
#include "engine/utils/logger/logger.h"

#include "utils/procedural_generation/drunkard_walk_generator.h"
#include "utils/constants.h"
#include "actor/hero.h"
#include "actor/wall.h"
#include "actor/door.h"
#include "actor/mini_map.h"

int main(int argc, char *argv[])
{
    RandomGenerator generator = RandomGenerator();

    std::vector<Actor *> actors;

    int mapWidth = 10;
    int mapHeight = 10;
    DrunkardWalkGenerator *mapGenerator = new DrunkardWalkGenerator();
    Map *map = mapGenerator->generate(mapWidth, mapHeight, 30, generator);
    actors.push_back(new MiniMap({20, 20, WALL_WIDTH, WALL_WIDTH},
                                 map->getValue(),
                                 map->getWidth(),
                                 map->getHeight(),
                                 map->getStartX(),
                                 map->getStartY()));

    actors.push_back(new Wall("1northWall", {0, 0, SCREEN_WIDTH, WALL_WIDTH}));
    actors.push_back(new Wall("1southWall", {0, SCREEN_HEIGHT - WALL_WIDTH, SCREEN_WIDTH, WALL_WIDTH}));
    actors.push_back(new Wall("1westWall", {0, 0, WALL_WIDTH, SCREEN_HEIGHT}));
    actors.push_back(new Wall("1eastWall", {SCREEN_WIDTH - WALL_WIDTH, 0, WALL_WIDTH, SCREEN_HEIGHT}));

    if (map->getStartY() - 1 >= 0 && *(map->getValue() + (map->getStartX() * map->getHeight()) + map->getStartY() - 1) == 0)
    {
        actors.push_back(new Door("northDoor", {(SCREEN_WIDTH / 2) - (DOOR_WIDTH / 2), 0, DOOR_WIDTH, DOOR_HEIGHT}, {"door", "north"}));
    }
    if (map->getStartY() + 1 < map->getHeight() && *(map->getValue() + (map->getStartX() * map->getHeight()) + map->getStartY() + 1) == 0)
    {
        actors.push_back(new Door("southDoor", {(SCREEN_WIDTH / 2) - (DOOR_WIDTH / 2), SCREEN_HEIGHT - DOOR_HEIGHT, DOOR_WIDTH, DOOR_HEIGHT}, {"door", "south"}));
    }
    if (map->getStartX() - 1 >= 0 && *(map->getValue() + ((map->getStartX() - 1) * map->getHeight()) + map->getStartY()) == 0)
    {
        actors.push_back(new Door("westDoor", {0, (SCREEN_HEIGHT / 2) - (DOOR_WIDTH / 2), DOOR_HEIGHT, DOOR_WIDTH}, {"door", "west"}));
    }
    if (map->getStartX() + 1 < map->getWidth() && *(map->getValue() + ((map->getStartX() + 1) * map->getHeight()) + map->getStartY()) == 0)
    {
        actors.push_back(new Door("eastDoor", {SCREEN_WIDTH - DOOR_HEIGHT, (SCREEN_HEIGHT / 2) - (DOOR_WIDTH / 2), DOOR_HEIGHT, DOOR_WIDTH}, {"door", "east"}));
    }

    actors.push_back(new Hero({SCREEN_WIDTH / 2,
                               SCREEN_HEIGHT / 2,
                               HERO_WIDTH,
                               HERO_HEIGHT}));

    Engine engine;
    if (!engine.init(SCREEN_WIDTH, SCREEN_HEIGHT, actors))
    {
        Logger::log("Failed to initialize!\n");
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