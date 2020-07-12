#include "main_scene.h"

bool MainScene::init(Storage* storage) {
    this->hero = storage->getActor("hero");
    if (hero == nullptr) {
        return false;
    }
    return true;
}

void MainScene::render(SDL_Renderer* renderer)
{
    hero->render(renderer);
}

void MainScene::update(float delta)
{
    hero->update(delta);
}

void MainScene::handleInput(SDL_Event *event)
{
    hero->handleInput(event);
}