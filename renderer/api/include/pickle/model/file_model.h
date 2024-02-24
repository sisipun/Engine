#ifndef PICKLE_RENDERER_FILE_MODEL
#define PICKLE_RENDERER_FILE_MODEL

#include <string>

#include <pickle/model/model.h>

namespace pickle
{
    namespace renderer
    {
        class FileModel : public Model
        {
        public:
            FileModel(std::string path);
        };
    }
}

#endif