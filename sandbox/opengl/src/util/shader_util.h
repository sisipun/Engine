#ifndef SHADER_UTIL_H
#define SHADER_UTIL_H

#include "../model/shader.h"

class ShaderUtil
{
public:
    static Shader directLightShader()
    {
        return Shader(
            "../resources/shaders/direct-light-shader.vert",
            "../resources/shaders/direct-light-shader.frag");
    }

    static Shader pointLightShader()
    {
        return Shader(
            "../resources/shaders/point-light-shader.vert",
            "../resources/shaders/point-light-shader.frag");
    }
};

#endif