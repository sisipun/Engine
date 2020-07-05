#include "user_controller.h"
#include "../utils/constants.h"

void UserController::handleInput(SDL_Event *event)
{
    if (!initialized || actor == nullptr)
    {
        return;
    }

    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_RIGHT:
            actor->setHorizontalVelocity(HERO_VELOCITY);
            break;
        case SDLK_LEFT:
            actor->setHorizontalVelocity(-HERO_VELOCITY);
            break;
        case SDLK_UP:
            actor->setVerticalVelocity(-HERO_VELOCITY);
            break;
        case SDLK_DOWN:
            actor->setVerticalVelocity(HERO_VELOCITY);
            break;
        }
    }
    else if (event->type == SDL_KEYUP)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_RIGHT:
            actor->setHorizontalVelocity(0);
            break;
        case SDLK_LEFT:
            actor->setHorizontalVelocity(0);
            break;
        case SDLK_UP:
            actor->setVerticalVelocity(0);
            break;
        case SDLK_DOWN:
            actor->setVerticalVelocity(0);
            break;
        }
    }
}