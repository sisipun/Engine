#include <iostream>
#include <string>

#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stbimage/stb_image.h>

#include "file_model.h"

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

FileModel::FileModel(const std::string &path) : path(path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        // TODO use logger here
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
}

// TODO change to links and const method also const
void FileModel::processNode(const aiNode *node, const aiScene *scene)
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

Mesh FileModel::processMesh(const aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

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

    if (mesh->mMaterialIndex < 0)
    {
        return Mesh(vertices, indices, Material(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), {}, 16.0f, 0.5f));
    }

    aiMaterial *aiMaterial = scene->mMaterials[mesh->mMaterialIndex];

    aiColor3D ambientColor;
    aiMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);
    glm::vec3 ambient = glm::vec3(ambientColor.r, ambientColor.g, ambientColor.b);

    aiColor3D diffuseColor;
    aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
    glm::vec3 diffuse = glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);

    aiColor3D specularColor;
    aiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);
    glm::vec3 specular = glm::vec3(specularColor.r, specularColor.g, specularColor.b);

    std::vector<Texture> textures;
    std::vector<Texture> diffuseMaps = loadTextures(aiMaterial, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = loadTextures(aiMaterial, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::vector<Texture> normalMaps = loadTextures(aiMaterial, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    std::vector<Texture> heightMaps = loadTextures(aiMaterial, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    float shiness;
    aiMaterial->Get(AI_MATKEY_SHININESS, shiness);

    float shinessStrength;
    aiMaterial->Get(AI_MATKEY_SHININESS_STRENGTH, shinessStrength);

    Material material(ambient, diffuse, specular, textures, shiness, shinessStrength > 1.0f ? 1.0f : shinessStrength);
    return Mesh(vertices, indices, material);
}

std::vector<Texture> FileModel::loadTextures(const aiMaterial *material, const aiTextureType type, const std::string &typeName)
{
    std::vector<Texture> textures;
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