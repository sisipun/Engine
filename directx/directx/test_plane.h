#ifndef TEST_PLANE_H
#define TEST_PLANE_H

#include "drawable.h"

class TestPlane : public Drawable
{
public:
	TestPlane(const Renderer& renderer, float radius);
	void setPos(DirectX::XMFLOAT3 pos) noexcept;
	DirectX::XMMATRIX getTransform() const noexcept override;
	void spawnControlWindow(const Renderer& renderer) noexcept;
private:
	struct ConstantData
	{
		float specularIntensity = 0.18f;
		float specularPower = 18.0f;
		BOOL normalMappingEnabled = TRUE;
		float padding;
	} constData;

	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
};

#endif