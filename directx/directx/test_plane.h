#ifndef TEST_PLANE_H
#define TEST_PLANE_H

#include "drawable.h"

class TestPlane : public Drawable
{
public:
	TestPlane(const Renderer& renderer, float radius);
	void setPos(DirectX::XMFLOAT3 pos) noexcept;
	DirectX::XMMATRIX getTransform() const noexcept override;
	void update(const Renderer& renderer) noexcept;
	void spawnControlWindow(const Renderer& renderer) noexcept;
private:
	struct ConstantData
	{
		float specularIntensity = 0.1f;
		float specularPower = 20.0f;
		BOOL normalMappingEnabled = TRUE;
		float padding;
	} constData;

	DirectX::XMFLOAT3 pos = { 1.0f, 1.0f, 1.0f };
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
};

#endif