#include "hero.h"
#include "bullet.h"

void Hero::renderActor(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Rect rect = {
        static_cast<int>(body.x),
        static_cast<int>(body.y),
        static_cast<int>(body.width),
        static_cast<int>(body.height)};
    SDL_RenderFillRect(renderer, &rect);
}

void Hero::updateActor(float delta)
{
    lastHorizontalMove = horizontalVelocity * delta;
    lastVerticalMove = verticalVelocity * delta;
    body.x += lastHorizontalMove;
    body.y += lastVerticalMove;
}

std::string addBullet(Context* context, unsigned long bulletIndex, Body body, float horizontalVelocity, float verticalVelocity) {
    std::string bulletName = "bullet" + std::to_string(bulletIndex);
    context->storeActor(new Bullet(bulletName, body, horizontalVelocity, verticalVelocity));
    return bulletName;
}

void Hero::handleActorInput(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_RIGHT:
            horizontalVelocity = HERO_VELOCITY;
            break;
        case SDLK_LEFT:
            horizontalVelocity = -HERO_VELOCITY;
            break;
        case SDLK_UP:
            verticalVelocity = -HERO_VELOCITY;
            break;
        case SDLK_DOWN:
            verticalVelocity = HERO_VELOCITY;
            break;
        case SDLK_w:
            bullets.push_back(addBullet(context, bullets.size(), {body.x, body.y, BULLET_WIDTH, BULLET_HEIGHT}, 0, -BULLET_VELOCITY));
            break;
        case SDLK_s:
            bullets.push_back(addBullet(context, bullets.size(), {body.x, body.y, BULLET_WIDTH, BULLET_HEIGHT}, 0, BULLET_VELOCITY));
            break;
        case SDLK_a:
            bullets.push_back(addBullet(context, bullets.size(), {body.x, body.y, BULLET_WIDTH, BULLET_HEIGHT}, -BULLET_VELOCITY, 0));
            break;
        case SDLK_d:
            bullets.push_back(addBullet(context, bullets.size(), {body.x, body.y, BULLET_WIDTH, BULLET_HEIGHT}, BULLET_VELOCITY, 0));
            break;
        }
    }
    else if (event->type == SDL_KEYUP)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_RIGHT:
            horizontalVelocity = 0;
            break;
        case SDLK_LEFT:
            horizontalVelocity = 0;
            break;
        case SDLK_UP:
            verticalVelocity = 0;
            break;
        case SDLK_DOWN:
            verticalVelocity = 0;
            break;
        }
    }
}

void Hero::handleActorCollision(Actor *actor)
{
    std::vector<std::string> actorTags = actor->getTags();
    if (std::find(actorTags.begin(), actorTags.end(), "wall") != actorTags.end())
    {
        body.x -= lastHorizontalMove;
        body.y -= lastVerticalMove;
    }
    if (std::find(actorTags.begin(), actorTags.end(), "door") != actorTags.end())
    {
        body.x = startX;
        body.y = startY;
        for (std::string bulletName: bullets) {
            context->deleteActor(bulletName);
        }
        if (std::find(actorTags.begin(), actorTags.end(), "north") != actorTags.end())
        {
            context->pushEvent(Event("heroUp"));
        }
        else if (std::find(actorTags.begin(), actorTags.end(), "south") != actorTags.end())
        {
            context->pushEvent(Event("heroDown"));
        }
        else if (std::find(actorTags.begin(), actorTags.end(), "west") != actorTags.end())
        {
            context->pushEvent(Event("heroLeft"));
        }
        else if (std::find(actorTags.begin(), actorTags.end(), "east") != actorTags.end())
        {
            context->pushEvent(Event("heroRight"));
        }
    }
}

void Hero::handleActorEvent(Event event)
{
    if (event.getType() == "deleteBullet")
    {
        std::string bulletName = event.getParam("name");
        context->deleteActor(bulletName);
        bullets.erase(std::remove(bullets.begin(), bullets.end(), bulletName), bullets.end());
    }
}
