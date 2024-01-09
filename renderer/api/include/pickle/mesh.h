#ifndef PICKLE_RENDERER_MESH
#define PICKLE_RENDERER_MESH

#include <vector>

namespace pickle
{
    namespace renderer
    {
        struct Vertex
        {
        };

        class Mesh
        {
        public:
            Mesh(std::vector<Vertex> vertices);

            const std::vector<Vertex>& getVertices() const;

        private:
            std::vector<Vertex> vertices;
        };
    }
}

#endif