#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <map>

class Event
{
public:
    Event(std::string type, std::map<const std::string, const std::string> params) : type(type), params(params)
    {
    }

    Event(std::string type) : type(type), params({})
    {
    }

    const std::string getType() const
    {
        return type;
    }

    const std::string getParam(std::string param) const
    {
        auto it = params.find(param);
        if (params.find(param) != params.end())
        {
            return it->second;
        }
        else
        {
            return "";
        }
    }

protected:
    std::map<const std::string, const std::string> params;

private:
    const std::string type;
};

#endif