#include <iostream>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stbimage/stb_image.h>

#include "model.h"

int loadTexture(const std::string &path)
{
    unsigned int texture;
    glGenTextures(1, &texture);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        // TODO check for corner cases
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        // TODO use logger here
        std::cout << "Texture failed to load at path: " << path << std::endl;
    }

    stbi_image_free(data);
    return texture;
}

Model::Model(const std::string &path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        // TODO use logger here
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    this->path = path;
    processNode(scene->mRootNode, scene);
}

void Model::draw(const Shader &shader) const
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].draw(shader);
    }
}

// TODO change to links and const method also const
void Model::processNode(const aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(const aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 position;
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;
        vertex.position = position;

        // TODO check ofr has normals
        if (mesh->HasNormals())
        {
            glm::vec3 normal;
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.y = mesh->mNormals[i].z;
            vertex.normal = normal;
        }

        // TODO maintain all texture coords
        glm::vec2 textureCoords;
        if (mesh->mTextureCoords[0])
        {
            textureCoords.x = mesh->mTextureCoords[0][i].x;
            textureCoords.y = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            textureCoords.x = 0;
            textureCoords.y = 0;
        }
        vertex.textureCoords = textureCoords;

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = loadTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        std::vector<Texture> normalMaps = loadTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        std::vector<Texture> heightMaps = loadTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadTextures(const aiMaterial *material, const aiTextureType type, const std::string &typeName)
{
    std::vector<Texture> textures;
    // TODO make optimization with existion textues
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString fileName;
        material->GetTexture(type, i, &fileName);
        std::string filePath = path.substr(0, path.find_last_of('/')) + '/' + fileName.C_Str();

        bool textureExists = false;
        for (unsigned int i = 0; i < loadedTextures.size(); i++)
        {
            if (loadedTextures[i].filePath == filePath)
            {
                textures.push_back(loadedTextures[i]);
                textureExists = true;
                break;
            }
        }

        if (!textureExists)
        {
            Texture texture;
            texture.id = loadTexture(filePath);
            texture.type = typeName;
            texture.filePath = filePath;
            textures.push_back(texture);
            loadedTextures.push_back(texture);
        }
    }

    return textures;
}