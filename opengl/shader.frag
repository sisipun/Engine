#version 330 core
out vec4 FragColor;

in GS_OUT {
   vec2 TextureCoord;
   vec3 Normal;
   vec3 FragPos;
} fs_in;

struct Light {
   vec3 position;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct Material {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   bool hasDiffuse;
   bool hasSpecular;
   sampler2D texture_diffuse1;
   sampler2D texture_specular1;
   sampler2D texture_normal1;
   float shininess;
   float shininessStrenght;
};

uniform Material material;
uniform Light light; 
uniform vec3 viewPos;

void main()
{
   vec3 diffuseTexture = vec3(texture(material.texture_diffuse1, fs_in.TextureCoord));
   vec3 specularTexture = vec3(texture(material.texture_specular1, fs_in.TextureCoord));
   vec3 norm = normalize(fs_in.Normal);

   vec3 ambient = light.ambient * (material.hasDiffuse ? diffuseTexture : material.ambient);

   vec3 lightDir = normalize(light.position - fs_in.FragPos);
   float diff = max(dot(norm, lightDir), 0.0f);
   vec3 diffuse = diff * light.diffuse * (material.hasDiffuse ? diffuseTexture : material.diffuse);

   vec3 viewDir = normalize(viewPos - fs_in.FragPos);
   vec3 halfway = normalize(viewDir + lightDir);
   float spec = pow(max(dot(norm, halfway), 0.0f), material.shininess);
   vec3 specular = spec * light.specular * (material.hasSpecular ? specularTexture : material.specular) *  material.shininessStrenght;

   vec3 result = ambient + diffuse + specular;
   FragColor = vec4(result, 1.0f);
}