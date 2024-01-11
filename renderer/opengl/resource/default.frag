#version 330 core
in VS_OUT {
   vec3 FragPos;
   vec3 Normal;
   vec3 Color;
   vec2 TextureCoordinates;
} inFs;

struct Light {
   vec3 direction;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct Camera {
    vec3 position;
};

out vec4 outFragColor;

uniform Light light;
uniform Camera camera;
uniform sampler2D Texture;

void main()
{
    vec3 diffuseTexture = texture(Texture, inFs.TextureCoordinates).xyz;

    vec3 materialAmbient = diffuseTexture;
    vec3 materialDiffuse = diffuseTexture;

    float ambient = 1.0f;

    vec3 normal = normalize(inFs.Normal);
    vec3 normLightDirection = normalize(light.direction);

    float diffuse = max(dot(normal, -normLightDirection), 0.0f);

    vec3 normViewDirection = normalize(inFs.FragPos - camera.position);
    vec3 halfway = -normalize(normViewDirection + normLightDirection);

    float specular = pow(max(dot(normal, halfway), 0.0f), 16.0f);

    vec3 result = light.ambient * materialAmbient * ambient + light.diffuse * materialDiffuse * diffuse + light.specular * specular;
    outFragColor = vec4(result * inFs.Color, 1.0f);
}