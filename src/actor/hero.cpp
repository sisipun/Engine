#include "hero.h"
#include "../utils/constants.h"

void Hero::update(float delta)
{
    this->lastHorizontalMove = this->horizontalVelocity * delta;
    this->lastVerticalMove = this->verticalVelocity * delta;
    this->body.x += this->lastHorizontalMove;
    this->body.y += this->lastVerticalMove;
    if (this->rigidBody != nullptr) {
        this->rigidBody->updateBody(body.x, body.y);
    }
}

void Hero::handleInput(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_RIGHT:
            this->horizontalVelocity = HERO_VELOCITY;
            break;
        case SDLK_LEFT:
            this->horizontalVelocity = -HERO_VELOCITY;
            break;
        case SDLK_UP:
            this->verticalVelocity = -HERO_VELOCITY;
            break;
        case SDLK_DOWN:
            this->verticalVelocity = HERO_VELOCITY;
            break;
        }
    }
    else if (event->type == SDL_KEYUP)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_RIGHT:
            this->horizontalVelocity = 0;
            break;
        case SDLK_LEFT:
            this->horizontalVelocity = 0;
            break;
        case SDLK_UP:
            this->verticalVelocity = 0;
            break;
        case SDLK_DOWN:
            this->verticalVelocity = 0;
            break;
        }
    }
}

void Hero::handleCollision(Actor *actor)
{
    this->body.x -= this->lastHorizontalMove;
    this->body.y -= this->lastVerticalMove;
}