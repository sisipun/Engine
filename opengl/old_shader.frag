#version 330 core
out vec4 FragColor;

in vec2 TextureCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

uniform sampler2D fragmentTexture;
uniform vec3 lightColor;

void main()
{
   //vec3 color = vec3(texture(fragmentTexture, TextureCoord));
   vec3 color = vec3(1.0f, 0.5f, 0.31f);
   vec3 norm = normalize(Normal);

   float ambientStrength = 0.1f;
   vec3 ambient = ambientStrength * lightColor;

   float diffuseStrength = 1.0f;
   vec3 lightDir = normalize(LightPos - FragPos);
   float diff = max(dot(norm, lightDir), 0.0f);
   vec3 diffuse = diffuseStrength * diff * lightColor;

   float specularStrength = 0.5f;
   vec3 viewDir = normalize(-FragPos);
   vec3 halfway = normalize(viewDir + lightDir);
   float spec = pow(max(dot(norm, halfway), 0.0f), 32);
   vec3 specular = specularStrength * spec * lightColor;

   vec3 result = (ambient + diffuse + specular) * color;
   FragColor = vec4(result, 1.0f);
}