#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <map>

class Actor;

class Storage
{
public:
    ~Storage();
    
    bool addActor(Actor *actor);

    Actor *getActor(std::string name);

    std::map<std::string, Actor *> getActors()
    {
        return actors;
    }

private:
    std::map<std::string, Actor *> actors;
};

#endif