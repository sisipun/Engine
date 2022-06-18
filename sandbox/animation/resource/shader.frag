#version 330 core

layout(location = 0) out vec4 fragColor;

in vec3 fragmentPosition;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

void main() {
	fragColor = vec4(0.0f);
}