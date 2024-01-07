#version 330 core
in VS_OUT {
   vec3 FragPos;
   vec3 Normal;
   vec3 Color;
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

void main()
{
    vec3 ambient = vec3(1.0f, 1.0f, 1.0f);

    vec3 normal = normalize(inFs.Normal);
    vec3 normLightDirection = normalize(light.direction);

    vec3 diffuse = vec3(max(dot(normal, -normLightDirection), 0.0f));

    vec3 normViewDirection = normalize(inFs.FragPos - camera.position);
    vec3 halfway = -normalize(normViewDirection + normLightDirection);

    vec3 specular = vec3(pow(max(dot(normal, halfway), 0.0f), 16.0f));

    vec3 result = light.ambient * ambient + light.diffuse * diffuse + light.specular * specular;
    outFragColor = vec4(result * inFs.Color, 1.0f);
}