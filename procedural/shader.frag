#version 330 core

#define MAX_STEPS 100
#define MAX_DISTANCE 100
#define SURFACE_MIN_DIST 0.01

layout(location = 0) out vec4 fragColor;

uniform vec2 u_resolution;
uniform float u_time;

float GetDistance(vec3 position)
{
    vec4 sphere = vec4(0, 1, 6, 1);
    float sphereDist = length(position - sphere.xyz) - sphere.w;
    float planeDist = position.y;
    return min(sphereDist, planeDist);
}

float RayMarching(vec3 cameraPosition, vec3 cameraDirection)
{
    float resDist = 0;
    for (int i = 0; i < MAX_STEPS; i++)
    {
        float dist = GetDistance(cameraPosition + resDist * cameraDirection);       
        resDist += dist;
        if (dist < SURFACE_MIN_DIST || resDist > MAX_DISTANCE) break;
    }
    return resDist;
}

vec3 GetNormal(vec3 position)
{
    float e = 0.01;
    float dx = GetDistance(vec3(position.x, position.y, position.z)) - GetDistance(vec3(position.x - e, position.y, position.z));
    float dy = GetDistance(vec3(position.x, position.y, position.z)) - GetDistance(vec3(position.x, position.y - e, position.z));
    float dz = GetDistance(vec3(position.x, position.y, position.z)) - GetDistance(vec3(position.x, position.y, position.z - e));
    return normalize(vec3(dx, dy, dz));
}

float GetLight(vec3 position) {
    vec3 lightPosition = vec3(0.0f, 5.0f, 6.0f);
    lightPosition.xy += vec2(sin(u_time), cos(u_time)); 
    vec3 lightDirection = normalize(lightPosition - position);
    vec3 norm = GetNormal(position);
    float dotValue = clamp(dot(lightDirection, norm), 0.0f, 1.0f);
    
    float lightToPositionDistance = length(lightPosition - position);
    float positionToLightDistance = RayMarching(position + norm * SURFACE_MIN_DIST, lightDirection);
    if (positionToLightDistance < lightToPositionDistance) dotValue *= 0.1f;

    return dotValue;
}

void main()
{
    vec2 uv = (gl_FragCoord.xy - 0.5f * u_resolution.xy) / u_resolution.y;
    vec3 cameraPosition = vec3(0.0f, 1.0f, 0.0f);
    vec3 cameraDirection = normalize(vec3(uv.x, uv.y, 1.0f));
    float dist = RayMarching(cameraPosition, cameraDirection);
    vec3 color = vec3(GetLight(cameraPosition + dist * cameraDirection));
    fragColor = vec4(color, 1.0f);
}