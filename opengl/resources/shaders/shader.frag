#version 330 core
out vec4 FragColor;

in VS_OUT {
   vec2 TextureCoord;
   vec3 Normal;
   vec3 FragPos;
} fs_in;

struct DirLight {
   vec3 direction;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct PointLight {
   vec3 position;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

   float constant;
   float linear;
   float quadratic;
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
uniform PointLight light; 
uniform vec3 viewPos;

vec3 calculatePointLight(PointLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor, vec3 norm, vec3 viewDir, vec3 fragPos, float shininess, float shininessStrenght) {
   float lightDistance = length(light.position - fragPos);
   float attenuation = 1.0 / (light.constant + light.linear * lightDistance + light.quadratic * (lightDistance * lightDistance));  

   vec3 ambient = light.ambient * ambientColor;

   vec3 lightDir = normalize(light.position - fragPos);
   float diff = max(dot(norm, lightDir), 0.0f);
   vec3 diffuse = diff * light.diffuse * diffuseColor;

   vec3 halfway = normalize(viewDir + lightDir);
   float spec = pow(max(dot(norm, halfway), 0.0f), shininess);
   vec3 specular = spec * light.specular * specularColor *  shininessStrenght;

   return ambient + diffuse + specular;
}

vec3 calculateDirLight(DirLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor, vec3 norm, vec3 viewDir, float shininess, float shininessStrenght) {
   vec3 ambient = light.ambient * ambientColor;

   vec3 lightDir = normalize(-light.direction);
   float diff = max(dot(norm, lightDir), 0.0f);
   vec3 diffuse = diff * light.diffuse * diffuseColor;

   vec3 halfway = normalize(viewDir + lightDir);
   float spec = pow(max(dot(norm, halfway), 0.0f), shininess);
   vec3 specular = spec * light.specular * specularColor *  shininessStrenght;

   return ambient + diffuse + specular;
}

void main()
{
   vec3 diffuseTexture = vec3(texture(material.texture_diffuse1, fs_in.TextureCoord));
   vec3 specularTexture = vec3(texture(material.texture_specular1, fs_in.TextureCoord));
   vec3 norm = normalize(fs_in.Normal);
   vec3 viewDir = normalize(viewPos - fs_in.FragPos);

   vec3 result = calculatePointLight(
      light, 
      material.hasDiffuse ? diffuseTexture : material.ambient,
      material.hasDiffuse ? diffuseTexture : material.diffuse,
      material.hasSpecular ? specularTexture : material.specular,
      norm,
      viewDir,
      fs_in.FragPos,
      material.shininess,
      material.shininessStrenght
   );

   FragColor = vec4(result, 1.0f);
}