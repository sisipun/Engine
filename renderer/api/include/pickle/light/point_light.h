#ifndef PICKLE_RENDERER_POINT_LIGHT
#define PICKLE_RENDERER_POINT_LIGHT

#include "light.h"

namespace pickle
{
    namespace renderer
    {
        class PointLight : public Light
        {
        public:
            PointLight(math::Vector<3, float> ambient, math::Vector<3, float> diffuse, math::Vector<3, float> specular, math::Vector<3, float> position, math::Vector<3, float> direction);

            math::Vector<3, float> getPosition() const;
            math::Vector<3, float> getDirection() const;

        private:
            math::Vector<3, float> position;
            math::Vector<3, float> direction;
        };
    }
}

#endif