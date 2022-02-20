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
    vec2 uv_i = fract(uv);
    vec2 uv_f = floor(uv);
    return mix(random(uv_i), random(uv_i + 1.0), smoothstep(0.0, 1.0, uv_f.x));
}

void main() {
	vec2 uv = gl_FragCoord.xy/u_resolution;
    vec3 color = vec3(0.0);

    uv *= 10.0;
    vec2 fract_uv = fract(uv);
    vec2 floor_uv = floor(uv);
    vec2 tile = rotateTile(fract_uv, random(floor_uv));
    
    color = vec3(smoothstep(0.1, 0.0, abs(tile.x - tile.y)));

	fragColor = vec4(color,1.0);
}