#include "engine.h"
#include "logger/logger.h"

Engine::Engine() : window(nullptr), renderer(nullptr), storage(nullptr), timer(nullptr), currentScene(nullptr), delta(0) {}

bool Engine::init(float screenWidth, float screenHeigh)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        Logger::log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    storage = new Storage();

    event = new SDL_Event();
    timer = new Timer();

    return true;
}

bool Engine::loadMedia(Scene *startScene, std::vector<Actor *> actors)
{
    for (Actor *actor : actors)
    {
        if (!storage->addActor(actor))
        {
            return false;
        }
    }

    if (!changeScene(startScene))
    {
        return false;
    }

    return true;
}

bool Engine::changeScene(Scene *scene)
{
    if (!scene->init(storage))
    {
        return false;
    }

    this->currentScene = scene;
    return true;
}

void Engine::update()
{
    timer->start();

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    currentScene->renderScene(renderer);

    SDL_RenderPresent(renderer);

    currentScene->updateScene(delta);

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

        currentScene->handleInputScene(event);
    }
}

bool Engine::isQuit()
{
    return quit;
}

void Engine::close()
{
    delete timer;
    delete storage;
    delete currentScene;

    timer = nullptr;
    storage = nullptr;
    currentScene = nullptr;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete event;
    renderer = nullptr;
    window = nullptr;
    event = nullptr;

    SDL_Quit();
}