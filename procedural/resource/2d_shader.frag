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

float cross(in vec2 _st, in float boldness)
{
    vec2 l = _st - vec2(0.5);
    return 1.0 - step(boldness, abs(abs(l.x) - abs(l.y)));
}

void main() {
	vec2 st = gl_FragCoord.xy/u_resolution;
    vec3 color = vec3(0.0);

    st *= 3.0;
    vec2 fract_st = fract(st);
    vec2 floor_st = floor(st);

    float alph = step(1.0, mod(floor_st.x + floor_st.y, 2.0));
    color = vec3(fract_st, 0.0);
    color = vec3(alph * cross(fract_st,0.1) + (1.0 - alph) * circle(fract_st, 0.5));

	gl_FragColor = vec4(color,1.0);
}