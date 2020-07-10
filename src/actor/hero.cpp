#include "hero.h"
#include "../utils/constants.h"

void Hero::handleInput(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_RIGHT:
            setHorizontalVelocity(HERO_VELOCITY);
            break;
        case SDLK_LEFT:
            setHorizontalVelocity(-HERO_VELOCITY);
            break;
        case SDLK_UP:
            setVerticalVelocity(-HERO_VELOCITY);
            break;
        case SDLK_DOWN:
            setVerticalVelocity(HERO_VELOCITY);
            break;
        }
    }
    else if (event->type == SDL_KEYUP)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_RIGHT:
            setHorizontalVelocity(0);
            break;
        case SDLK_LEFT:
            setHorizontalVelocity(0);
            break;
        case SDLK_UP:
            setVerticalVelocity(0);
            break;
        case SDLK_DOWN:
            setVerticalVelocity(0);
            break;
        }
    }
}