#include "engine/engine.h"
#include "engine/actor/actor.h"
#include "engine/actor/actor_group.h"
#include "engine/maze/chess_generator.h"
#include "engine/maze/drunkard_walk_generator.h"
#include "engine/maze/cellular_automata_generator..h"
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

    std::vector<Actor *> walls;
    MapGenerator *mazeGenerator = new DrunkardWalkMazeGenerator();
    int mazeWidth = SCREEN_WIDTH / WALL_WIDTH - 2;
    int mazeHeight = SCREEN_HEIGHT / WALL_WIDTH - 2;
    Map *map = mazeGenerator->generate(mazeWidth, mazeHeight);

    for (int i = 0; i < map->getWidth(); i++)
    {
        for (int j = 0; j < map->getHeight(); j++)
        {
            if (*(map->getValue() + (i * map->getHeight()) + j) == 1)
            {
                walls.push_back(new Wall(std::to_string(i), {static_cast<float>((i + 1) * WALL_WIDTH), static_cast<float>((1 + j) * WALL_WIDTH),  WALL_WIDTH, WALL_WIDTH}, 0, 0));
            }
        }
    }

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

    float heroStartX = (map->getStartX() + 1) * WALL_WIDTH;
    float heroStartY = (map->getStartY() + 1) * WALL_WIDTH;
    Hero *hero = new Hero({heroStartX, heroStartY, HERO_WIDTH, HERO_HEIGHT}, 0, 0);
    actors.push_back(hero);

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
    delete mazeGenerator;
    engine.close();
    return 0;
}