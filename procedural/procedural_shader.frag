#version 330 core

#define MAX_STEPS 256
#define MAX_DISTANCE 500
#define SURFACE_MIN_DIST 0.0001
#define PI 3.14159265

layout(location = 0) out vec4 fragColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform vec2 u_mouse;

float vmax(vec3 v) {
	return max(max(v.x, v.y), v.z);
}

float fSphere(vec3 p, float r) {
	return length(p) - r;
}

float fBox(vec3 p, vec3 b) {
	vec3 d = abs(p) - b;
	return length(max(d, vec3(0))) + vmax(min(d, vec3(0)));
}

float fPlane(vec3 p, vec3 n, float distanceFromOrigin) {
	return dot(p, n) + distanceFromOrigin;
}

void pR(inout vec2 p, float a) {
	p = cos(a)*p + sin(a)*vec2(p.y, -p.x);
}

float getDistance(vec3 p)
{
    float pd = fPlane(p, vec3(0, 1, 0), 1.0);
    float sd = fSphere(p, 1.0);
    float bd = fBox(p, vec3(0.7));
    return min(pd, mix(sd, bd, sin(u_time) * 0.5 + 0.5));
}

float rayMarching(vec3 ro, vec3 rd)
{
    float resDist = 0;
    for (int i = 0; i < MAX_STEPS; i++)
    {
        float d = getDistance(ro + resDist * rd);       
        resDist += d;
        if (abs(d) < SURFACE_MIN_DIST || resDist > MAX_DISTANCE) break;
    }
    return resDist;
}

vec3 getNormal(vec3 p)
{
    float e = 0.01;
    float dx = getDistance(vec3(p.x, p.y, p.z)) - getDistance(vec3(p.x - e, p.y, p.z));
    float dy = getDistance(vec3(p.x, p.y, p.z)) - getDistance(vec3(p.x, p.y - e, p.z));
    float dz = getDistance(vec3(p.x, p.y, p.z)) - getDistance(vec3(p.x, p.y, p.z - e));
    return normalize(vec3(dx, dy, dz));
}

float getLight(vec3 p) {
    vec3 light = vec3(10.0f, 55.0f, -20.0f);
    vec3 lightDir = normalize(light - p);
    vec3 norm = getNormal(p);
    float val = clamp(dot(lightDir, norm), 0.0f, 1.0f);
    
    float d = rayMarching(p + norm * SURFACE_MIN_DIST * 2.0f, lightDir);
    if (d < length(light - p)) val *= 0.1f;

    return val;
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
    float dist = rayMarching(ro, rd);
    vec3 color = vec3(getLight(ro + dist * rd));
    fragColor = vec4(color, 1.0f);
}