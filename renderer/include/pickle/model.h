#ifndef PICKLE_RENDERER_MODEL_H
#define PICKLE_RENDERER_MODEL_H

#include <string>
#include <vector>

#include <pickle/math.h>

namespace pickle
{
    namespace renderer
    {
        class Model
        {
        public:
            Model(std::string path);

            pickle::math::Vector<3, float> getVertex(int i) const;
            pickle::math::Vector<3, float> getTextureCoord(int i) const;
            pickle::math::Vector<9, int> getFace(int i) const;

            int getVerticesCount() const;
            int getFacesCount() const;

        private:
            std::vector<pickle::math::Vector<3, float>> vertices;
            std::vector<pickle::math::Vector<3, float>> textureCoords;
            std::vector<pickle::math::Vector<9, int>> faces;
        };
    }
}

#endif