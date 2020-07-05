#include "engine.h"
#include "../utils/constants.h"

Engine::Engine() : window(nullptr), renderer(nullptr), timer(nullptr), delta(0) {}

bool Engine::init()
{
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Roguelike", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    event = new SDL_Event();
    timer = new Timer();

    return true;
}

bool Engine::loadMedia(std::vector<ActorInfo *> infos, std::vector<Controller *> controllers)
{
    for (ActorInfo *info : infos)
    {
        if (actors.find(info->getName()) != actors.end())
        {
            SDL_Log("Duplicatie actor name: %s\n", info->getName().c_str());
            return false;
        }
        Actor *actor = new Actor(info);
        actors.insert(std::pair<std::string, Actor *>(info->getName(), actor));
    }

    for (Controller *controller : controllers)
    {
        if (!controller->init(this))
        {
            SDL_Log("Can't initialize controller for actor name: %s\n", controller->getActorName().c_str());
            return false;
        }

        this->controllers.insert(std::pair<std::string, Controller *>(controller->getActorName(), controller));
    }

    return true;
}

void Engine::update()
{
    timer->start();

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    for (const auto &actorDef : actors)
    {
        actorDef.second->render(renderer);
    }

    SDL_RenderPresent(renderer);

    for (const auto &controllerDef : controllers)
    {
        controllerDef.second->handleInput(event);
    }

    for (const auto &actorDef : actors)
    {
        actorDef.second->update(delta);
    }

    delta = timer->getTicks() * 0.001;
}

void Engine::handleInput()
{
    if (SDL_PollEvent(event) != 0)
    {
        if (event->type == SDL_QUIT)
        {
            quit = true;
        }
    }
}

bool Engine::isQuit()
{
    return quit;
}

void Engine::close()
{
    delete event;
    delete timer;

    for (const auto &actorDef : actors)
    {
        delete actorDef.second;
    }

    actors.clear();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
    event = nullptr;

    SDL_Quit();
}

Actor *Engine::getActor(std::string name)
{
    std::map<std::string, Actor *>::iterator actorPair = actors.find(name);
    if (actorPair == actors.end())
    {
        return nullptr;
    }
    return actorPair->second;
}