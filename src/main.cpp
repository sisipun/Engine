#include "engine/engine.h"
#include "engine/actor/actor.h"
#include "engine/actor/actor_group.h"
#include "engine/maze/maze_generator.h"
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

    Hero *hero = new Hero({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, HERO_WIDTH, HERO_HEIGHT}, 0, 0);
    actors.push_back(hero);

    std::vector<Actor *> walls;
    int mazeWidth = SCREEN_WIDTH / 10;
    int mazeHeight = SCREEN_HEIGHT / 10;
    int *maze = MazeGenerator::generate(mazeWidth, mazeHeight);
    for (int i = 0; i < mazeWidth; i++)
    {
        for (int j = 0; j < mazeHeight; j++)
        {
            if (*(maze + (i * mazeHeight) + j) == 1)
            {
                walls.push_back(new Wall(std::to_string(i), {static_cast<float>(i * WALL_WIDTH), static_cast<float>(j * WALL_WIDTH),  WALL_WIDTH, WALL_WIDTH}, 0, 0));
            }
        }
    }
    //Actor *northWall = new Wall("northWall", {0, 0, SCREEN_WIDTH, WALL_WIDTH}, 0, 0);
    //Actor *westWall = new Wall("westWall", {0, 0, WALL_WIDTH, SCREEN_HEIGHT}, 0, 0);
    //Actor *southWall = new Wall("southWall", {0, SCREEN_HEIGHT - WALL_WIDTH, SCREEN_WIDTH, WALL_WIDTH}, 0, 0);
    //Actor *eastWall = new Wall("eastWall", {SCREEN_WIDTH - WALL_WIDTH, 0, WALL_WIDTH, SCREEN_HEIGHT}, 0, 0);

    //walls.push_back(northWall);
    //walls.push_back(westWall);
    //walls.push_back(southWall);
    //walls.push_back(eastWall);

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