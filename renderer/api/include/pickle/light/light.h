#ifndef PICKLE_RENDERER_LIGHT
#define PICKLE_RENDERER_LIGHT

#include <pickle/math.h>

namespace pickle
{
    namespace renderer
    {
        class Light
        {
        public:
            Light(math::Vector<3, float> ambient, math::Vector<3, float> diffuse, math::Vector<3, float> specular);

            math::Vector<3, float> getAmbient() const;
            math::Vector<3, float> getDiffuse() const;
            math::Vector<3, float> getSpecular() const;
        private:
            math::Vector<3, float> ambient;
            math::Vector<3, float> diffuse;
            math::Vector<3, float> specular;
        };
    }
}

#endif