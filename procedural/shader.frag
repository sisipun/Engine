#version 330 core

layout(location = 0) out vec4 fragColor;

uniform vec2 u_resolution;

void main()
{
    vec2 uv = (2.0 * gl_FragCoord.xy - u_resolution.xy) / u_resolution.xy;
    fragColor = vec4(uv.x, uv.y, 0.0f, 1.0f);
}