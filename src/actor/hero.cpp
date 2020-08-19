#include "hero.h"
#include "../utils/constants.h"

void Hero::renderActor(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Rect rect ={
        static_cast<int>(body.x),
        static_cast<int>(body.y),
        static_cast<int>(body.width),
        static_cast<int>(body.height)
    };
    SDL_RenderFillRect(renderer, &rect);
}

void Hero::update(float delta)
{
    this->lastHorizontalMove = this->horizontalVelocity * delta;
    this->lastVerticalMove = this->verticalVelocity * delta;
    this->body.x += this->lastHorizontalMove;
    this->body.y += this->lastVerticalMove;
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
    std::vector<std::string> actorTags = actor->getTags();
    if (std::find(actorTags.begin(), actorTags.end(), "wall") != actorTags.end())
    {
        this->body.x -= this->lastHorizontalMove;
        this->body.y -= this->lastVerticalMove;
    }
}