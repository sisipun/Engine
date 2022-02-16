
#version 330 core

#define MAX_STEPS 256
#define MAX_DISTANCE 500.0
#define SURFACE_MIN_DIST 0.0001
#define PI 3.14159265

layout(location = 0) out vec4 fragColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform vec2 u_mouse;

struct HitObject
{
    vec3 color;
    float ambientStrength;
    float diffuseStrength;
    float specularStrength;
    float shadowStrength;
    float shininess;
    float dist;
};

float vmax(vec3 v)
{
    return max(max(v.x, v.y), v.z);
}

float fSphere(vec3 p, float r)
{
    return length(p) - r;
}

float fBox(vec3 p, vec3 b)
{
    vec3 d = abs(p) - b;
    return length(max(d, vec3(0.0))) + vmax(min(d, vec3(0.0)));
}

float fPlane(vec3 p, vec3 n, float distanceFromOrigin)
{
    return dot(p, n) + distanceFromOrigin;
}

void pR(inout vec2 p, float a)
{
    p = cos(a) * p + sin(a) * vec2(p.y, -p.x);
}

HitObject hitMin(HitObject a, HitObject b)
{
    return a.dist < b.dist ? a : b;
}

HitObject hitMax(HitObject a, HitObject b)
{
    return a.dist > b.dist ? a : b;
}

HitObject hitMix(HitObject a, HitObject b, float value)
{
    return HitObject(
        mix(a.color, b.color, value), 
        mix(a.ambientStrength, b.ambientStrength, value), 
        mix(a.diffuseStrength, b.diffuseStrength, value), 
        mix(a.specularStrength, b.specularStrength, value), 
        mix(a.shadowStrength, b.shadowStrength, value), 
        mix(a.shininess, b.shininess, value), 
        mix(a.dist, b.dist, value)
    );
}

HitObject getHit(vec3 p)
{
    HitObject plane = HitObject(
        vec3(0.2 + 0.4 * mod(floor(p.x) + floor(p.z), 2.0)),
        0.2,
        1.0,
        0.5,
        0.1,
        32, 
        fPlane(p, vec3(0.0, 1.0, 0.0), 1.0)
    );
    HitObject sphere = HitObject(
        vec3(0.9, 0.0, 0.0), 
        0.3,
        1.0,
        0.5,
        0.1,
        32, 
        fSphere(p, 1.0)
    );
    HitObject box = HitObject(
        vec3(0.0, 0.0, 0.9), 
        0.3,
        1.0,
        0.5,
        0.1,
        32, 
        fBox(p, vec3(0.7))
    );
    return hitMin(plane, hitMix(sphere, box, sin(u_time) * 0.5 + 0.5));
}

HitObject rayMarching(vec3 ro, vec3 rd)
{
    HitObject hit, object = HitObject(vec3(0.0), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    for (int i = 0; i < MAX_STEPS; i++)
    {
        HitObject hit = getHit(ro + object.dist * rd);
        object.color = hit.color;
        object.ambientStrength = hit.ambientStrength;
        object.diffuseStrength = hit.diffuseStrength;
        object.specularStrength = hit.specularStrength;
        object.shadowStrength = hit.shadowStrength;
        object.shininess = hit.shininess;
        object.dist += hit.dist;
        if (abs(hit.dist) < SURFACE_MIN_DIST || object.dist > MAX_DISTANCE) break;
    }
    return object;
}

vec3 getNormal(vec3 p)
{
    float e = 0.01;
    float dx = getHit(vec3(p.x, p.y, p.z)).dist - getHit(vec3(p.x - e, p.y, p.z)).dist;
    float dy = getHit(vec3(p.x, p.y, p.z)).dist - getHit(vec3(p.x, p.y - e, p.z)).dist;
    float dz = getHit(vec3(p.x, p.y, p.z)).dist - getHit(vec3(p.x, p.y, p.z - e)).dist;
    return normalize(vec3(dx, dy, dz));
}

vec3 getLight(vec3 p, vec3 ro, HitObject object)
{
    vec3 light = vec3(10.0f, 55.0f, -20.0f);
    vec3 lightDir = normalize(light - p);
    vec3 viewDir = normalize(ro - p);
    vec3 norm = getNormal(p);
    vec3 halfway = normalize(lightDir + viewDir);
    
    float ambient = clamp(object.ambientStrength, 0.0f, 1.0f);
    float diffuse = clamp(object.diffuseStrength * dot(lightDir, norm), 0.0f, 1.0f);
    float specular = pow(clamp(object.specularStrength * dot(norm, halfway), 0.0f, 1.0f), 32);

    float d = rayMarching(p + norm * SURFACE_MIN_DIST * 2.0f, lightDir).dist;
    if (d < length(light - p)) {
        return (ambient + diffuse * object.shadowStrength) * object.color;
    }

    return (ambient + diffuse + specular) * object.color;
}

mat3 getCamera(vec3 ro, vec3 lookAt)
{
    vec3 forward = normalize(vec3(lookAt - ro));
    vec3 right = normalize(cross(vec3(0.0f, 1.0f, 0.0f), forward));
    vec3 up = cross(forward, right);
    return mat3(right, up, forward);
}

void mouseControl(inout vec3 ro)
{
    vec2 mouse = u_mouse / u_resolution;
    pR(ro.yz, mouse.y * PI * 0.5 - PI * 0.25);
    pR(ro.xz, mouse.x * 2 * PI);
}

void main()
{
    vec2 uv = (gl_FragCoord.xy - 0.5f * u_resolution.xy) / u_resolution.y;
    vec3 ro = vec3(3.0f, 3.0f, -3.0f);
    mouseControl(ro);
    vec3 lookAt = vec3(0.0f, 0.0f, 0.0f);
    vec3 rd = getCamera(ro, lookAt) * normalize(vec3(uv, 1.0f));
    HitObject object = rayMarching(ro, rd);
    vec3 color;
    if (object.dist < MAX_DISTANCE)
    {
        color = getLight(ro + object.dist * rd, ro, object);
    }
    else
    {
        color = vec3(0.5, 0.8, 0.9);
    };
    fragColor = vec4(color, 1.0f);
}