#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "SDL.h"
#include "../engine/controller/controller.h"
#include "../engine/engine.h"

class UserController : public Controller
{
public:
    UserController(std::string actorName) : Controller(actorName)
    {
    }

    void handleInput(SDL_Event *event) override;
};

#endif