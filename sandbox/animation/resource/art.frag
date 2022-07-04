#version 330 core

layout(location = 0) out vec4 fragColor;

in vec3 fragmentPosition;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float random (float value) {
    return fract(sin(value * 1000000.0));
}

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12345.0,10000.0)))
                 * 1000000.0);
}

float noise (vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = smoothstep(0.,1.,f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;

    vec2 i = floor(st * 3.0);
	vec2 f = fract(st);
    
	float n = noise(st * (10.0 + 5.0 * random(i.x + 1.0f)));
    
    vec3 leftColor = mix(vec3(1.0, 0.0, 0.0), vec3(0.6, 0.0, 0.0), n);
    vec3 middleColor = mix(vec3(0.6, 0.0, 0.0), vec3(0.4,0.0,0.0), n);
    vec3 rightColor = mix(vec3(0.840,0.818,0.525), vec3(0.625,0.609,0.391), n);
    vec3 backgroundColor = mix(vec3(0.510,0.284,0.160), vec3(0.490,0.205,0.134), noise(st * 20.0));
    
    float offsetValue = (noise(st * (20.0 + 5.0 * random(i.x + 1.0f) * sin(u_time / 3600.0f))) - 0.5) * 0.02;
    
    vec3 leftArt = step(0.03 + offsetValue, st.y) * step(st.y + offsetValue, 0.97) * step(0.03 + offsetValue, st.x) * step(st.x + offsetValue, 0.31) * leftColor;
    vec3 middleArt = step(0.02 + offsetValue, st.y) * step(st.y + offsetValue, 0.98) * step(0.35 + offsetValue, st.x) * step(st.x, 0.65 + offsetValue) * middleColor;
    vec3 rightArt = step(0.05 + offsetValue, st.y) * step(st.y, 0.94 + offsetValue) * step(0.68 + offsetValue, st.x) * step(st.x + offsetValue, 0.98) * rightColor;
    
    vec3 completeArt = leftArt + middleArt + rightArt;

    float artFactor = step(length(completeArt), 0.0);
    vec3 resultColor = mix(completeArt, backgroundColor, artFactor);
    
    fragColor = vec4(resultColor, 1.0);
}
