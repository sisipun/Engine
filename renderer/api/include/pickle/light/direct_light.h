#ifndef PICKLE_RENDERER_DIRECT_LIGHT
#define PICKLE_RENDERER_DIRECT_LIGHT

#include "light.h"

namespace pickle
{
    namespace renderer
    {
        class DirectLight : public Light
        {
        public:
            DirectLight(math::Vector<3, float> ambient, math::Vector<3, float> diffuse, math::Vector<3, float> specular, math::Vector<3, float> direction);
            
            math::Vector<3, float> getDirection() const;

        private:
            math::Vector<3, float> direction;
        };
    }
}

#endif