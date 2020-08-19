#include "engine/engine.h"
#include "engine/actor/actor.h"
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
#include "actor/door.h"
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

    int mapWidth = 10;
    int mapHeight = 10;
    DrunkardWalkGenerator *mapGenerator = new DrunkardWalkGenerator();
    Map *map = mapGenerator->generate(mapWidth, mapHeight, 30, generator);
    actors.push_back(new MiniMap({ 10, 10, WALL_WIDTH, WALL_WIDTH },
        map->getValue(),
        map->getWidth(),
        map->getHeight(),
        map->getStartX(),
        map->getStartY()));

    if (map->getStartY() - 1 >= 0 && *(map->getValue() + (map->getStartX() * map->getHeight()) + map->getStartY() - 1) == 0)
    {
        actors.push_back(new Wall("northWestWall", { 0, 0, (SCREEN_WIDTH / 2) - (DOOR_WIDTH / 2), WALL_WIDTH }));
        actors.push_back(new Door("northDoor", { (SCREEN_WIDTH / 2) - (DOOR_WIDTH / 2), 0, (SCREEN_WIDTH / 2) + (DOOR_WIDTH / 2), WALL_WIDTH }));
        actors.push_back(new Wall("northEastWall", { (SCREEN_WIDTH / 2) + (DOOR_WIDTH / 2), 0, SCREEN_WIDTH, WALL_WIDTH }));
    }
    else
    {
        actors.push_back(new Wall("northWall", { 0, 0, SCREEN_WIDTH, WALL_WIDTH }));
    }
    if (map->getStartY() + 1 < map->getHeight() && *(map->getValue() + (map->getStartX() * map->getHeight()) + map->getStartY() + 1) == 0)
    {
        actors.push_back(new Wall("southWestWall", { 0, SCREEN_HEIGHT - WALL_WIDTH, (SCREEN_WIDTH / 2) - (DOOR_WIDTH / 2), WALL_WIDTH }));
        actors.push_back(new Door("southDoor", { (SCREEN_WIDTH / 2) - (DOOR_WIDTH / 2), SCREEN_HEIGHT - WALL_WIDTH, (SCREEN_WIDTH / 2) + (DOOR_WIDTH / 2), WALL_WIDTH }));
        actors.push_back(new Wall("southEastWall", { (SCREEN_WIDTH / 2) + (DOOR_WIDTH / 2), SCREEN_HEIGHT - WALL_WIDTH, SCREEN_WIDTH, WALL_WIDTH }));
    }
    else
    {
        actors.push_back(new Wall("southWall", { 0, SCREEN_HEIGHT - WALL_WIDTH, SCREEN_WIDTH, WALL_WIDTH }));
    }
    if (map->getStartX() - 1 >= 0 && *(map->getValue() + ((map->getStartX() - 1) * map->getHeight()) + map->getStartY()) == 0)
    {
        actors.push_back(new Wall("westNorthWall", { 0, 0, WALL_WIDTH, (SCREEN_HEIGHT / 2) - (DOOR_WIDTH / 2) }));
        actors.push_back(new Door("westDoor", { 0, (SCREEN_HEIGHT / 2) - (DOOR_WIDTH / 2), WALL_WIDTH, (SCREEN_HEIGHT / 2) + (DOOR_WIDTH / 2) }));
        actors.push_back(new Wall("westSouthWall", { 0, (SCREEN_HEIGHT / 2) + (DOOR_WIDTH / 2), WALL_WIDTH, SCREEN_HEIGHT }));
    }
    else
    {
        actors.push_back(new Wall("westWall", { 0, 0, WALL_WIDTH, SCREEN_HEIGHT }));
    }
    if (map->getStartX() + 1 < map->getWidth() && *(map->getValue() + ((map->getStartX() + 1) * map->getHeight()) + map->getStartY()) == 0)
    {
        actors.push_back(new Wall("eastNorthWall", { SCREEN_WIDTH - WALL_WIDTH, 0, WALL_WIDTH, (SCREEN_HEIGHT / 2) - (DOOR_WIDTH / 2) }));
        actors.push_back(new Door("eastDoor", { SCREEN_WIDTH - WALL_WIDTH, (SCREEN_HEIGHT / 2) - (DOOR_WIDTH / 2), WALL_WIDTH, (SCREEN_HEIGHT / 2) + (DOOR_WIDTH / 2) }));
        actors.push_back(new Wall("eastSouthWall", { SCREEN_WIDTH - WALL_WIDTH, (SCREEN_HEIGHT / 2) + (DOOR_WIDTH / 2), WALL_WIDTH, SCREEN_HEIGHT }));
    }
    else
    {
        actors.push_back(new Wall("eastWall", { SCREEN_WIDTH - WALL_WIDTH, 0, WALL_WIDTH, SCREEN_HEIGHT }));
    }

    actors.push_back(new Hero({ SCREEN_WIDTH / 2,
        SCREEN_HEIGHT / 2,
        HERO_WIDTH,
        HERO_HEIGHT },
        0, 0));

    std::vector<std::string> mainSceneActors;
    for (Actor* actor : actors) {
        mainSceneActors.push_back(actor->getName());
    }
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