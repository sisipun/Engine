#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTextureCoord;

out vec2 TextureCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

void main()
{
   TextureCoord = aTextureCoord;
   Normal = mat3(transpose(inverse(view * model))) * aNorm;
   FragPos = vec3(view * model * vec4(aPos, 1.0f));
   LightPos = vec3(view * vec4(lightPos, 1.0f));
   gl_Position = projection * view * model * vec4(aPos, 1.0);
}