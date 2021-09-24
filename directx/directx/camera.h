#ifndef CAMERA_H
#define CAMERA_H

#include "renderer.h"

class Camera
{
public:
	DirectX::XMMATRIX getMatrix() const noexcept;
	void spawnControlWindow() noexcept;
	void reset() noexcept;
private:
	float radius = 20.0f;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta = 0.0f;
	float phi = 0.0f;
};

#endif
