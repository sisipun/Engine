#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stbimage/stb_image.h>

#include "model.h"

void Model::draw(const Shader &shader) const
{
    shader.setMat4("model", transform);
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].draw(shader);
    }
}