#version 330 core
in VS_OUT {
   vec3 FragPos;
   vec3 Normal;
   vec3 Color;
} inFs;

out vec4 outFragColor;

uniform vec3 lightDirection;
uniform vec3 cameraPosition;

void main()
{
    vec3 ambient = vec3(0.1f, 0.1f, 0.1f);

    vec3 normal = normalize(inFs.Normal);
    vec3 normLightDirection = normalize(-lightDirection);

    vec3 diffuse = vec3(max(dot(normal, normLightDirection), 0.0f));

    vec3 normViewDirection = normalize(cameraPosition - inFs.FragPos);
    vec3 halfway = normalize(normViewDirection + normLightDirection);

    vec3 specular = vec3(pow(max(dot(normal, halfway), 0.0f), 16.0f));

    vec3 light = ambient + diffuse + specular;

    outFragColor = vec4(light * inFs.Color, 1.0f);
}