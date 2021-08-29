#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

#include <string>

class Shader
{
public:
    unsigned int ID;

    Shader(const std::string &vertexPath, const std::string &fragmentPath) : vertexPath(vertexPath), fragmentPath(fragmentPath)
    {
    }

    void load();

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setMat4(const std::string &name, glm::mat4 value) const;

    void setVec3(const std::string &name, glm::vec3 value) const;

    void use() const;

private:
    std::string vertexPath;
    std::string geometryPath;
    std::string fragmentPath;

    void checkShaderCompilation(unsigned int shader) const;

    void checkProgramLinking(unsigned int program) const;
};

#endif