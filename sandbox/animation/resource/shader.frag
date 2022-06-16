#version 330 core

layout(location = 0) out vec4 fragColor;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

void main() {
	fragColor = vec4(u_mouse.x / u_resolution.x, u_mouse.y / u_resolution.y, 0.0f, 1.0f);
}