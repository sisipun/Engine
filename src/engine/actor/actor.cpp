#include "actor.h"

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

void Actor::updateActor(float delta)
{
    body.x += horizontalVelocity * delta;
    body.y += verticalVelocity * delta;
}