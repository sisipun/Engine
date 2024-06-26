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
	void rotate(float dx, float dy) noexcept;
	void translate(DirectX::XMFLOAT3 translation) noexcept;
	void update(const Renderer& renderer) const noexcept;
private:
	struct ConstantData
	{
		alignas(16) DirectX::XMFLOAT3 cameraPos;
	};

	DirectX::XMFLOAT3 position;
	float pitch;
	float yaw;
	mutable PixelConstantBuffer<ConstantData> constantBuffer;

	static constexpr float sensitivity = 0.002f;
};

#endif
