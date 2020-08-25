#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event
{
public:
    Event(std::string type) : type(type)
    {
    }

    const std::string getType() const
    {
        return type;
    }

private:
    const std::string type;
};

#endif