#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNorm;
layout (location = 2) in vec2 inTextureCoordinates;

out VS_OUT {
   vec3 FragPos;
   vec3 Normal;
   vec2 TextureCoordinates;
} outVs;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
    outVs.FragPos = vec3(model * vec4(inPos, 1.0f));
    outVs.Normal = mat3(transpose(inverse(model))) * inNorm;
    outVs.TextureCoordinates = inTextureCoordinates;
    gl_Position = projection * view * model * vec4(inPos, 1.0f);
}