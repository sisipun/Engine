#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stbimage/stb_image.h>

#include "model.h"

void Model::bind(const Shader &shader) const
{
    shader.setMat4("model", transform);
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].bind(shader);
    }
}

void Model::draw() const
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].draw();
    }
}