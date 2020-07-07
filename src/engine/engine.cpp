#include "engine.h"
#include "logger/logger.h"

Engine::Engine() : window(nullptr), renderer(nullptr), timer(nullptr), delta(0) {}

bool Engine::init(float screenWidth, float screenHeigh)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Logger::log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Roguelike", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeigh,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        Logger::log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        Logger::log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    storage = new Storage();

    event = new SDL_Event();
    timer = new Timer();

    return true;
}

bool Engine::loadMedia(std::vector<Actor *> actors, std::vector<Controller *> controllers)
{
    for (Actor *actor : actors)
    {
        if (!storage->addActor(actor))
        {
            return false;
        }
    }

    for (Controller *controller : controllers)
    {
        if (!storage->addController(controller))
        {
            return false;
        }
    }

    return true;
}

void Engine::update()
{
    timer->start();

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    for (const auto &actorDef : storage->getActors())
    {
        actorDef.second->render(renderer);
    }

    SDL_RenderPresent(renderer);

    for (const auto &controllerDef : storage->getControllers())
    {
        controllerDef.second->handleInput(event);
    }

    for (const auto &actorDef : storage->getActors())
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
    delete storage;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
    event = nullptr;

    SDL_Quit();
}