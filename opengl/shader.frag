#version 330 core
out vec4 FragColor;

in vec2 TextureCoord;

uniform sampler2D texture_diffuse1;

void main()
{
   FragColor = vec4(vec3(texture(texture_diffuse1, TextureCoord)), 1.0);
}