#version 330 core

#define PI 3.14159265359
#define ANGLE_STEP (PI / 18.0f)
#define TUNNEL_SIZE 20
#define TUNNEL_RADIUS 0.3f
#define TUNNEL_POINT_SIZE 0.01f

layout(location = 0) out vec4 fragColor;

in vec3 fragmentPosition;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;
uniform vec3 u_circles[TUNNEL_SIZE];

void main() {
	vec4 color = vec4(0.0f);

	for (int i = 0; i < TUNNEL_SIZE; i++)
	{
		for (float angle = 0.0f; angle < 2 * PI; angle += ANGLE_STEP)
		{
			vec2 circlePosition = u_circles[i].xy;

			circlePosition.x += TUNNEL_RADIUS * sin(angle);
			circlePosition.y += TUNNEL_RADIUS * cos(angle);

			circlePosition /= u_circles[i].z;

			if (length(circlePosition - fragmentPosition.xy) < TUNNEL_POINT_SIZE && color.a < 1.0f - u_circles[i].z)
			{
				color = vec4(1.0f - u_circles[i].z);
			}
		}
	}

	fragColor = color;
}