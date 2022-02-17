#version 330 core

layout(location = 0) out vec4 fragColor;

uniform vec2 u_resolution;
uniform float u_time;

float square(vec2 uv, vec2 pos, vec2 size) 
{
    vec2 bord = (1.0 - size) * 0.5;
    vec2 bl = smoothstep(bord, bord + 0.01, uv - pos);
    vec2 tr = smoothstep(bord, bord + 0.01, (1.0 - uv) + pos);
    return bl.x * bl.y * tr.x * tr.y;
}

float circle(vec2 uv)
{
    return 1.0 - step(0.5, length(uv - 0.5));
}

void main()
{
    vec2 uv = gl_FragCoord.xy / u_resolution;
    float sq = square(uv, vec2(sin(u_time) * 0.25, cos(u_time) * 0.25), vec2(0.5, 0.5));
    float cir = circle(uv);
    vec3 color = vec3(sq, cir, 0.0);
    fragColor = vec4(color, 1.0);
}