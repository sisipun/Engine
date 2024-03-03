#ifndef PICKLE_RENDERER_FILE_MODEL
#define PICKLE_RENDERER_FILE_MODEL

#include <string>

#include <assimp/scene.h>

#include <pickle/model/model.h>

namespace pickle
{
    namespace renderer
    {
        class FileModel : public Model
        {
        public:
            FileModel(std::string path);

        private:
            void processNode(const aiNode* node, const aiScene *scene);
        };
    }
}

#endif