#ifndef PICKLE_RENDERER_MODEL
#define PICKLE_RENDERER_MODEL

#include <vector>

#include <pickle/model/mesh.h>

namespace pickle
{
    namespace renderer
    {
        class Model
        {
        public:
            const std::vector<Mesh> &getMeshes() const;

        protected:
            std::vector<Mesh> meshes;
        };
    }
}

#endif