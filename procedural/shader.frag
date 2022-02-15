#version 330 core

#define MAX_STEPS 100
#define MAX_DISTANCE 100
#define SURFACE_MIN_DIST 0.01

layout(location = 0) out vec4 fragColor;

uniform vec2 u_resolution;
uniform float u_time;

mat2 rotation(float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    return mat2(c, -s, s, c);
}

float planeSdf(vec3 position, vec3 norm)
{
    return dot(position, norm);
}

float sphereSdf(vec3 position, vec3 sphere, float radius)
{
    return length(position - sphere) - radius;
}

float capsuleSdf(vec3 position, vec3 sphereA, vec3 sphereB, float radius)
{
    vec3 ab = sphereB - sphereA;
    vec3 ap = position - sphereA;
    float delta = dot(ab, ap) / dot(ab, ab);
    delta = clamp(delta, 0.0f, 1.0f);
    vec3 c = sphereA + delta * ab;

    return length(position - c) - radius;
}

float torusSdf(vec3 position, vec3 torus, float smallRadius, float bigRadius)
{
    vec3 offsetPosition = position - torus;
    float x = length(offsetPosition.xz) - bigRadius;
    float y = offsetPosition.y;
    return length(vec2(x, y)) - smallRadius;
}

float boxSdf(vec3 position, vec3 box, vec3 size)
{
    vec3 offsetPosition = position - box;
    offsetPosition = abs(offsetPosition) - size;
    return length(max(offsetPosition, 0.0f)) + min(max(offsetPosition.x, max(offsetPosition.y, offsetPosition.z)), 0.0f);
}

float getDistance(vec3 position)
{
    float planeDistance = planeSdf(position, vec3(0.0f, 1.0f, 0.0f));
    float sphereDistance = sphereSdf(position, vec3(1.0f, 1.0f, 6.0f), 1.0f);
    float capsuleDistance = capsuleSdf(position, vec3(0.0f, 1.0f, 6.0f), vec3(1.0f, 2.0f, 6.0f), 0.2f);
    float torusDistance = torusSdf(position, vec3(0.0f, 0.5f, 6.0f), 0.5f, 1.5f);
    float boxDistance = boxSdf(position, vec3(1.0f, 1.0f, 6.0f), vec3(0.7f));
    return min(planeDistance, mix(boxDistance, sphereDistance, sin(u_time) * 0.5f + 0.5f));
}

float rayMarching(vec3 cameraPosition, vec3 cameraDirection)
{
    float resDist = 0;
    for (int i = 0; i < MAX_STEPS; i++)
    {
        float dist = getDistance(cameraPosition + resDist * cameraDirection);       
        resDist += dist;
        if (dist < SURFACE_MIN_DIST || resDist > MAX_DISTANCE) break;
    }
    return resDist;
}

vec3 getNormal(vec3 position)
{
    float e = 0.01;
    float dx = getDistance(vec3(position.x, position.y, position.z)) - getDistance(vec3(position.x - e, position.y, position.z));
    float dy = getDistance(vec3(position.x, position.y, position.z)) - getDistance(vec3(position.x, position.y - e, position.z));
    float dz = getDistance(vec3(position.x, position.y, position.z)) - getDistance(vec3(position.x, position.y, position.z - e));
    return normalize(vec3(dx, dy, dz));
}

float getLight(vec3 position) {
    vec3 lightPosition = vec3(0.0f, 5.0f, 3.0f);
    lightPosition.xz += vec2(sin(u_time), cos(u_time)); 
    vec3 lightDirection = normalize(lightPosition - position);
    vec3 norm = getNormal(position);
    float dotValue = clamp(dot(lightDirection, norm), 0.0f, 1.0f);
    
    float lightToPositionDistance = length(lightPosition - position);
    float positionToLightDistance = rayMarching(position + norm * SURFACE_MIN_DIST * 2.0f, lightDirection);
    if (positionToLightDistance < lightToPositionDistance) dotValue *= 0.1f;

    return dotValue;
}

void main()
{
    vec2 uv = (gl_FragCoord.xy - 0.5f * u_resolution.xy) / u_resolution.y;
    vec3 cameraPosition = vec3(0.0f, 3.0f, 0.0f);
    vec3 cameraDirection = normalize(vec3(uv.x, uv.y - 0.4f, 1.0f));
    float dist = rayMarching(cameraPosition, cameraDirection);
    vec3 color = vec3(getLight(cameraPosition + dist * cameraDirection));
    fragColor = vec4(color, 1.0f);
}