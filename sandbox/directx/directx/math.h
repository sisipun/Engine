#ifndef MATH_H
#define MATH_H

#include <math.h>

constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

template<typename T>
constexpr T sq(const T& x)
{
	return x * x;
}

template<typename T>
constexpr T wrap_angle(T theta)
{
	const T modded = fmod(theta, (T)(2.0 * PI_D));
	return modded > (T)PI_D
		? (modded - (T)(2.0 * PI_D))
		: modded;
}

template<typename T>
constexpr T interpolate(const T& src, const T& dest, float alpha)
{
	return src + (dest - src) * alpha;
}

template<typename T>
constexpr T to_rad(T theta)
{
	return theta * PI / (T)180.0;
}
#endif