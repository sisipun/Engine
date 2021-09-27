#ifndef CAMERA_H
#define CAMERA_H

#include "renderer.h"
#include "constant_buffer.h"

class Camera
{
public:
	Camera(const Renderer& renderer);
	DirectX::XMMATRIX getMatrix() const noexcept;
	void spawnControlWindow() noexcept;
	void reset() noexcept;
	void update(const Renderer& renderer) const noexcept;
private:
	struct ConstantData
	{
		alignas(16) DirectX::XMFLOAT3 cameraPos;
	};

	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta = 0.0f;
	float phi = 0.0f;
	ConstantData constData;
	mutable PixelConstantBuffer<ConstantData> constantBuffer;
};

#endif
