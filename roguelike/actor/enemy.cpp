#include "enemy.h"

void Enemy::handleActorCollision(Actor *actor)
{
    std::vector<std::string> actorTags = actor->getTags();
    if (std::find(actorTags.begin(), actorTags.end(), "bullet") != actorTags.end())
    {
        context->pushEvent(Event("deleteEnemy", {{"name", name}}));
    }
}