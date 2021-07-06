#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include <assimp/scene.h>

#include "shader.h"
#include "mesh.h"

class Model
{
public:
    Model(std::string const &path);

    void draw(Shader const &shader) const;

private:
    void processNode(const aiNode *node, const aiScene *scene);
    Mesh processMesh(const aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadTextures(const aiMaterial *material, const aiTextureType type, const std::string &typeName);

    std::vector<Mesh> meshes;
    std::vector<Texture> loadedTextures;
    std::string path;

    glm::mat4 model;
};

#endif