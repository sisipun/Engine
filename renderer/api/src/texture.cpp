#include <pickle/texture.h>

#include <stbimage/stb_image.h>

#include <pickle/logger.h>

pickle::renderer::Texture::Texture(const std::string &path)
{
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channelsCount, 0);
    if (data)
    {
        this->data = data;
    }
    else
    {
        LOG_ERROR("Texture failed to load at path: ", path);
    }
}

pickle::renderer::Texture::~Texture()
{
    if (data) {
        stbi_image_free(data);
    }
}

int pickle::renderer::Texture::getWidth() const
{
    return width;
}

int pickle::renderer::Texture::getHeight() const
{
    return height;
}

int pickle::renderer::Texture::getChannelsCount() const
{
    return channelsCount;
}

const unsigned char* pickle::renderer::Texture::getData() const
{
    return data;
}