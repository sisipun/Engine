#include <pickle/texture.h>

#include <iostream>
#include <stbimage/stb_image.h>

pickle::renderer::Texture::Texture(std::string path)
{
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << "Can't read texture file: " << path << std::endl;
        stbi_image_free(data);
        return;
    }
}

pickle::renderer::Texture::~Texture()
{
    stbi_image_free(data);
}

pickle::renderer::Color pickle::renderer::Texture::getPixel(float x, float y) const
{
    int coordX = x * width;
    int coordY = y * height;
    unsigned char *offset = data + (coordX + height * coordY) * nrChannels;
    return {offset[0], offset[1], offset[2], 0xFF};
}