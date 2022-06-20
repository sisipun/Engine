#version 330 core

layout(location = 0) out vec4 fragColor;

in vec3 fragmentPosition;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float random (in vec2 st) {
    return fract(cos(dot(st.xy, vec2(18.4398,-15.233)))*
        sin(dot(st.xy, vec2(23.4398,11.233))) * 10000.0);
}

float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

#define OCTAVES 6
float fbm (in vec2 st) {
    float value = 0.0;
    float amplitude = .5;
    float frequency = 0.;

    for (int i = 0; i < OCTAVES; i++) {
        value += amplitude * noise(st);
        st *= 2.;
        amplitude *= .5;
    }
    return value;
}

vec4 fire(in vec2 fragmentCoords) 
{
	const float speed = 0.1f;
	const float fireSpeed = 0.001f;
	const float details = 0.03f;
	const float force = 0.4f;
	const float shift = 0.4f;
	const float gradientScaleFactor = 3.5f;
	const float gradientShift = 0.4f;

	float gradient = gradientScaleFactor * fragmentCoords.y / u_resolution.y - gradientShift;

	vec2 movingCoords = vec2(fragmentCoords.x,  fragmentCoords.y - u_time * speed) * details;
	
	float noise1 = fbm(movingCoords);
	float noise2 = force * (fbm(movingCoords + noise1 + u_time * fireSpeed) - shift);

	float nnoise1 = force * fbm(vec2(noise1, noise2));
	float nnoise2 = fbm(vec2(noise2, noise1));

	const vec3 red = vec3(0.9, 0.4, 0.2);
	const vec3 darkRed = vec3(0.5, 0.0, 0.0);
	const vec3 yellow = vec3(0.9, 0.9, 0.0);
	const vec3 black = vec3(0.1, 0.1, 0.1);

	vec3 c1 = mix(red, darkRed, nnoise1);
	vec3 c2 = mix(yellow, black, nnoise2);

	vec3 color = c1 + c2 - gradient - noise2;
	return vec4(color, 1.0f);
}

void main() 
{
	fragColor = fire(gl_FragCoord.xy);
}