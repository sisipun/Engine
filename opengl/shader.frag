#version 330 core
out vec4 FragColor;

in vec2 TextureCoord;
in vec3 Normal;
in vec3 FragPos;

struct Light {
   vec3 position;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct Material {
   sampler2D texture_diffuse1;
   sampler2D texture_specular1;
   sampler2D texture_normal1;
   float shininess;
};

uniform Material material;
uniform Light light; 
uniform vec3 viewPos;

void main()
{
   vec3 diffuseColor = vec3(texture(material.texture_diffuse1, TextureCoord));
   vec3 specularColor = vec3(texture(material.texture_specular1, TextureCoord));
   vec3 norm = normalize(Normal);

   float ambientStrength = 0.1f;
   vec3 ambient = ambientStrength * light.ambient * diffuseColor;

   float diffuseStrength = 1.0f;
   vec3 lightDir = normalize(light.position - FragPos);
   float diff = max(dot(norm, lightDir), 0.0f);
   vec3 diffuse = diffuseStrength * diff * light.diffuse * diffuseColor;

   float specularStrength = 0.5f;
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 halfway = normalize(viewDir + lightDir);
   float spec = pow(max(dot(norm, halfway), 0.0f), 32);
   vec3 specular = specularStrength * spec * light.specular * specularColor;

   vec3 result = ambient + diffuse + specular;
   FragColor = vec4(result, 1.0f);
}