#version 330 core

#define STARS_COUNT 100
#define STAR_SIZE 0.01f

layout(location = 0) out vec4 fragColor;

in vec3 fragmentPosition;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;
uniform vec3 u_stars[STARS_COUNT];

void main() {
	fragColor = vec4(0.0f);

	for (int i = 0; i < STARS_COUNT; i++)
	{
		vec2 starPosition = u_stars[i].xy / u_stars[i].z;
		if (length(starPosition - fragmentPosition.xy) < STAR_SIZE)
		{
			fragColor = vec4(1.0f - u_stars[i].z);
		}
	}
}