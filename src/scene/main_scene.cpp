#include "main_scene.h"

void MainScene::render(SDL_Renderer* renderer)
{
    storage->getActor("hero")->render(renderer);
}

void MainScene::update(float delta)
{
    storage->getActor("hero")->update(delta);
}

void MainScene::handleInput(SDL_Event *event)
{
    storage->getActor("hero")->handleInput(event);
}