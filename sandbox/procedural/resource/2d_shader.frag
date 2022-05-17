#version 330 core

layout(location = 0) out vec4 fragColor;

uniform vec2 u_resolution;
uniform float u_time;

float square(in vec2 uv, in vec2 pos, in vec2 size) 
{
    vec2 bord = (1.0 - size) * 0.5;
    vec2 bl = smoothstep(bord, bord + 0.01, uv - pos);
    vec2 tr = smoothstep(bord, bord + 0.01, (1.0 - uv) + pos);
    return bl.x * bl.y * tr.x * tr.y;
}

float circle(in vec2 uv, in float size)
{
    return 1.0 - step(size, length(uv - 0.5));
}

float cross(in vec2 uv, in float size)
{
    vec2 c = uv - vec2(0.5);
    return 1.0 - step(size, abs(abs(c.x) - abs(c.y)));
}

float random(in vec2 uv) 
{
    return fract(sin(dot(uv, vec2(43.785493, 175.24559232))) * 5306.12970583);
}

vec2 rotateTile(in vec2 uv, in float index)
{
    if (index > 0.75)
    {
        return vec2(1.0) - uv;
    } 
    else if (index > 0.5)
    {
        return vec2(1.0 - uv.x, uv.y);
    } 
    else if (index > 0.25)
    {
        return vec2(uv.x, 1.0 - uv.y);
    }

    return uv;
}

float noise(in vec2 uv)
{
    vec2 uv_i = floor(uv);
    vec2 uv_f = fract(uv);
    vec2 sm = smoothstep(0.0, 1.0, uv_f);
    
    float a = random(uv_i);
    float b = random(uv_i + vec2(1.0, 0.0));
    float c = random(uv_i + vec2(0.0, 1.0));
    float d = random(uv_i + vec2(1.0, 1.0));

    return mix(mix(a, c, sm.y), mix(b, d, sm.y), sm.x);
}

void main() {
	vec2 uv = gl_FragCoord.xy/u_resolution;

    vec3 color = vec3(noise(uv * 5.0));

	fragColor = vec4(color,1.0);
}