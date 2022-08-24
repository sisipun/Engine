#version 330 core

layout(location = 0) out vec4 fragColor;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float sdlSphere(vec2 uv, float r)
{
	return length(uv) - r;
}

vec3 hash( vec3 p )
{
	p = vec3( dot(p,vec3(127.1,311.7, 74.7)),
			  dot(p,vec3(269.5,183.3,246.1)),
			  dot(p,vec3(113.5,271.9,124.6)));

	return -1.0 + 2.0*fract(sin(p)*43758.5453123);
}

float noise( in vec2 val )
{
	vec3 x = vec3(val, 0.0f);
    vec3 p = floor(x);
    vec3 w = fract(x);
    
    vec3 u = w*w*w*(w*(w*6.0-15.0)+10.0);

    vec3 ga = hash( p+vec3(0.0,0.0,0.0) );
    vec3 gb = hash( p+vec3(1.0,0.0,0.0) );
    vec3 gc = hash( p+vec3(0.0,1.0,0.0) );
    vec3 gd = hash( p+vec3(1.0,1.0,0.0) );
    vec3 ge = hash( p+vec3(0.0,0.0,1.0) );
    vec3 gf = hash( p+vec3(1.0,0.0,1.0) );
    vec3 gg = hash( p+vec3(0.0,1.0,1.0) );
    vec3 gh = hash( p+vec3(1.0,1.0,1.0) );
    
    float va = dot( ga, w-vec3(0.0,0.0,0.0) );
    float vb = dot( gb, w-vec3(1.0,0.0,0.0) );
    float vc = dot( gc, w-vec3(0.0,1.0,0.0) );
    float vd = dot( gd, w-vec3(1.0,1.0,0.0) );
    float ve = dot( ge, w-vec3(0.0,0.0,1.0) );
    float vf = dot( gf, w-vec3(1.0,0.0,1.0) );
    float vg = dot( gg, w-vec3(0.0,1.0,1.0) );
    float vh = dot( gh, w-vec3(1.0,1.0,1.0) );
	
    return va + 
           u.x*(vb-va) + 
           u.y*(vc-va) + 
           u.z*(ve-va) + 
           u.x*u.y*(va-vb-vc+vd) + 
           u.y*u.z*(va-vc-ve+vg) + 
           u.z*u.x*(va-vb-ve+vf) + 
           u.x*u.y*u.z*(-va+vb+vc-vd+ve-vf-vg+vh);
}

#define OCTAVES 8.0f

vec3 fire(vec2 position, vec3 outherColor, vec3 middleColor, vec3 innerColor, float fireSpeed)
{
    float noiseValue = noise(position * OCTAVES + vec2(0.0f, u_time * -fireSpeed));
    
    float noiseDistributionY = clamp(position.y, 0.0f, 1.0f);
    float noiseDistributionX = 0.1f;
    vec2 noiseDistribution = noiseValue * vec2(noiseDistributionX, noiseDistributionY);

    vec2 outherPoint = (position) + noiseDistribution;
	vec2 middlePoint = (position + vec2(0.0f, 0.05f)) + noiseDistribution;
	vec2 innerPoint = (position + vec2(0.0f, 0.1f)) + noiseDistribution;

    float outherSphere = step(sdlSphere(outherPoint, 0.20f), 0.0f);
	float middleSphere = step(sdlSphere(middlePoint, 0.10f), 0.0f);
	float innerSphere = step(sdlSphere(innerPoint, 0.05f), 0.0f);

    return outherSphere * outherColor + middleSphere * middleColor + innerSphere * innerColor;
}

void main() 
{
	vec2 uv = gl_FragCoord.xy / u_resolution.xy;

    vec3 fire1 = fire(uv - vec2(0.8f, 0.5f), vec3(1.0f, 0.5f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), 0.003f);
    vec3 fire2 = fire(uv - vec2(0.2f, 0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.5f, 1.0f), vec3(1.0f, 1.0f, 1.0f), 0.005f);
    vec3 fire3 = fire(uv - vec2(0.5f, 0.2f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.5f), vec3(1.0f, 1.0f, 1.0f), 0.005f);
	fragColor = vec4(fire1 + fire2 + fire3, 0.0f);
}