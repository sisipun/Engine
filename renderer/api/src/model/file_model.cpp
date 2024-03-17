#include <pickle/model/file_model.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <pickle/logger.h>

pickle::renderer::FileModel::FileModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        LOG_ERROR("Can't load file model with path ", path, ". Cause: ", importer.GetErrorString());
    } else {
        LOG_INFO("File model with path ", path, " loaded");
    }
}

void pickle::renderer::FileModel::processNode(const aiNode* node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    }
}