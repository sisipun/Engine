#include "bullet.h"

void Bullet::handleActorCollision(Actor *actor)
{
    std::vector<std::string> actorTags = actor->getTags();
    if (std::find(actorTags.begin(), actorTags.end(), "wall") != actorTags.end())
    {
        context->pushEvent(Event("deleteBullet", {{"name", name}}));
    }
}