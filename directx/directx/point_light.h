#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "renderer.h"
#include "solid_sphere.h"
#include "constant_buffer.h"

class PointLight
{
public:
	PointLight(const Renderer& renderer, float radius = 0.5f);
	void spawnControlWindow() noexcept;
	void reset() noexcept;
	void update(const Renderer& renderer) const noexcept;
	void draw(const Renderer& renderer) const noexcept;
private:
	struct ConstantData
	{
		DirectX::XMFLOAT3 lightPos;
		float padding;
	};

	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	mutable SolidSphere mesh;
	mutable PixelConstantBuffer<ConstantData> constantBuffer;
};

#endif