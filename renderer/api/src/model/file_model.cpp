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
    }
    else
    {
        processNode(scene->mRootNode, scene);
        LOG_INFO("File model with path ", path, " loaded");
    }
}

void pickle::renderer::FileModel::processNode(const aiNode *node, const aiScene *scene)
{
    LOG_ERROR(std::to_string(node->mNumMeshes));
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void pickle::renderer::FileModel::processMesh(const aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    LOG_ERROR(std::to_string(mesh->mNumVertices));
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        LOG_ERROR(std::to_string(i));
        math::Vector<3, float> position;
        aiVector3D positionVector = mesh->mVertices[i];
        position.data[0] = positionVector.x;
        position.data[1] = positionVector.y;
        position.data[2] = positionVector.z;

        math::Vector<3, float> normal;
        if (mesh->HasNormals())
        {
            aiVector3D normalVector = mesh->mNormals[i];
            normal.data[0] = normalVector.x;
            normal.data[1] = normalVector.y;
            normal.data[2] = normalVector.z;
        }

        math::Vector<2, float> textureCoordinates;
        if (mesh->mTextureCoords[0])
        {
            aiVector3D textureCoordinatesVector = mesh->mTextureCoords[0][i];
            textureCoordinates.data[0] = textureCoordinatesVector.x;
            textureCoordinates.data[1] = textureCoordinatesVector.y;
        }
        vertices.push_back({position, normal, textureCoordinates});

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }
    }

    meshes.push_back({vertices, indices});
}