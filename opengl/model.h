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
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadTextures(aiMaterial *material, aiTextureType type, std::string typeName);
    
    std::vector<Mesh> meshes;
    std::vector<Texture> loadedTextures;
    std::string path;
};

#endif