#ifndef PICKLE_RENDERER_TEXTURE
#define PICKLE_RENDERER_TEXTURE

#include <string>
#include <memory>

namespace pickle
{
    namespace renderer
    {
        class Texture
        {
        public:
            Texture(const std::string &path);
            ~Texture();

            Texture(const Texture &application) = delete;
            Texture &operator=(const Texture &application) = delete;

            int getWidth() const;
            int getHeight() const;
            int getChannelsCount() const;
            const unsigned char* getData() const;

        private:
            int width;
            int height;
            int channelsCount;
            unsigned char* data;
        };
    }
}

#endif