#ifndef FILE_MODEL_H
#define FILE_MODEL_H

#include <vector>

#include <assimp/scene.h>

#include "model.h"

class FileModel : public Model
{
public:
    FileModel(std::string const &path);

private:
    void processNode(const aiNode *node, const aiScene *scene);
    Mesh processMesh(const aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadTextures(const aiMaterial *material, const aiTextureType type, const std::string &typeName);

    std::vector<Texture> loadedTextures;
    std::string path;
};

#endif