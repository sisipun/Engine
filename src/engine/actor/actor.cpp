#include "actor.h"

void Actor::render(SDL_Renderer *renderer)
{
    if (!visiable)
    {
        return;
    }
    this->renderActor(renderer);
}

void Actor::renderActor(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect rect = {
        static_cast<int>(body.x),
        static_cast<int>(body.y),
        static_cast<int>(body.width),
        static_cast<int>(body.height)};
    SDL_RenderFillRect(renderer, &rect);
}

void Actor::update(float delta)
{
    this->body.x += this->horizontalVelocity * delta;
    this->body.y += this->verticalVelocity * delta;
}