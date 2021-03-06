#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

void Shader::load()
{
    std::fstream vertexFile(vertexPath), geometryFile(geometryPath), fragmentFile(fragmentPath);
    if (!vertexFile)
    {
        // TODO use logger
        std::cout << "Can't read vertex file" << std::endl;
    }
    if (!geometryFile)
    {
        // TODO use logger
        std::cout << "Can't read geometry file" << std::endl;
    }
    if (!fragmentFile)
    {
        // TODO use logger
        std::cout << "Can't read fragment file" << std::endl;
    }
    std::stringstream vertexStream, geometryStream, fragmentStream;
    vertexStream << vertexFile.rdbuf();
    geometryStream << geometryFile.rdbuf();
    fragmentStream << fragmentFile.rdbuf();
    vertexFile.close();
    geometryFile.close();
    fragmentFile.close();

    std::string vertexCodeString = vertexStream.str();
    std::string geometryCodeString = geometryStream.str();
    std::string fragmentCodeString = fragmentStream.str();

    const char *vertexCode = vertexCodeString.c_str();
    const char *geometryCode = geometryCodeString.c_str();
    const char *fragmentCode = fragmentCodeString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilation(vertexShader);

    unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geometryCode, NULL);
    glCompileShader(geometryShader);
    checkShaderCompilation(geometryShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilation(fragmentShader);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, geometryShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    checkProgramLinking(ID);
    glDeleteShader(vertexShader);
    glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);
}

void Shader::setBool(const std::string &name, bool value) const
{
    setInt(name, value ? 1 : 0);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, false, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::use() const
{
    glUseProgram(ID);
}

void Shader::checkShaderCompilation(unsigned int shader) const
{
    int success;
    char log[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, log);
        // TODO use logger
        std::cout << "Can't compile shader: " << log << std::endl;
    }
}

void Shader::checkProgramLinking(unsigned int program) const
{
    int success;
    char log[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, log);
        // TODO use logger
        std::cout << "Can't link programm: " << log << std::endl;
    }
}