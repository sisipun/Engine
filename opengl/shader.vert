#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTextureCoord;

out vec2 TextureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   TextureCoord = aTextureCoord;
   gl_Position = projection * view * model * vec4(aPos, 1.0);
}