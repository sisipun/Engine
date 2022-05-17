#ifndef PICKLE_RENDERER_TEXTURE_H
#define PICKLE_RENDERER_TEXTURE_H

#include <string>

#include "color.h"

namespace pickle
{
    namespace renderer
    {
        class Texture
        {
        public:
            Texture(std::string path);

            ~Texture();

            Color getPixel(float x, float y) const;

        private:
            int width;
            int height;
            int nrChannels;
            unsigned char *data;
        };
    }
}

#endif