#ifndef PICKLE_RENDERER_MESH
#define PICKLE_RENDERER_MESH

#include <vector>

#include <pickle/math.h>

namespace pickle
{
    namespace renderer
    {
        struct Vertex
        {
            math::Vector<3, float> position;
            math::Vector<3, float> normal;
            math::Vector<2, float> textureCoordinates;
        };

        class Mesh
        {
        public:
            Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);

            const std::vector<Vertex> &getVertices() const;

            const std::vector<unsigned int> &getIndices() const;

        private:
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
        };
    }
}

#endif