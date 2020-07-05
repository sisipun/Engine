#include "actor.h"

Actor::Actor(ActorInfo *info)
{
    Body infoBody = info->getBody();
    this->body = {infoBody.x, infoBody.y, infoBody.width, infoBody.height};
    this->verticalVelocity = info->getVerticalVelocity();
    this->horizontalVelocity = info->getHorizontalVelocity();
}

void Actor::render(SDL_Renderer *renderer)
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

void Actor::setVerticalVelocity(float verticalVelocity) {
    this->verticalVelocity = verticalVelocity;
}

void Actor::setHorizontalVelocity(float horizontalVelocity) {
    this->horizontalVelocity = horizontalVelocity;
}

Body Actor::getBody()
{
    return this->body;
}