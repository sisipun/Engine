#version 330 core

out vec4 FragColor;

in VS_OUT {
   vec3 FragPos;
   vec3 Normal;
   vec2 TextureCoord;
} fs_in;

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

   float shiness;
   float shinessStrength;
};

struct Camera {
   vec3 position;
};

uniform Material material;
uniform PointLight light; 
uniform Camera camera;

void main() {
   // textures
   vec3 diffuseTexture = vec3(texture(material.texture_diffuse1, fs_in.TextureCoord));
   vec3 specularTexture = vec3(texture(material.texture_specular1, fs_in.TextureCoord));

   // material colors
   vec3 materialAmbient = material.hasDiffuse ? diffuseTexture : material.ambient;
   vec3 materiaDiffuse = material.hasDiffuse ? diffuseTexture : material.diffuse;
   vec3 materialSpecular = material.hasSpecular ? specularTexture : material.specular;
   
   // attenuation
   vec3 lightToFragment = light.position - fs_in.FragPos;
   float lightDistance = length(lightToFragment);
   float attenuation = 1.0 / (light.constant + light.linear * lightDistance + light.quadratic * (lightDistance * lightDistance));  

   // ambient
   vec3 ambient = light.ambient * materialAmbient;
   
   // diffuse
   vec3 norm = normalize(fs_in.Normal);
   vec3 lightDir = normalize(lightToFragment);

   float diff = max(dot(norm, lightDir), 0.0f);
   vec3 diffuse = diff * light.diffuse * materiaDiffuse;

   // specular
   vec3 viewDir = normalize(camera.position - fs_in.FragPos);
    
   vec3 halfway = normalize(viewDir + lightDir);
   float spec = pow(max(dot(norm, halfway), 0.0f), material.shiness);
   vec3 specular = spec * light.specular * materialSpecular * material.shinessStrength;
    
   // result
   vec3 color = ambient + diffuse + specular;
   FragColor = vec4(color, 1.0f);
}