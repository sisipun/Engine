#ifndef LIGHT_UTIL_H
#define LIGHT_UTIL_H

#include "../light/point_light.h"
#include "../light/dir_light.h"

class LightUtil
{
public:
    static DirLight dirLight()
    {
        return DirLight(glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    static PointLight pointLight()
    {
        return PointLight(glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 3.0f), 1.0f, 2.0f);
    }
};

#endif