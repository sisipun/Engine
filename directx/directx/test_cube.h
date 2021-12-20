#ifndef TEST_CUBE_H
#define TEST_CUBE_H

#include "drawable.h"

class TestCube : public Drawable
{
public:
	TestCube(const Renderer& renderer, float size);
	void setPos(DirectX::XMFLOAT3 pos) noexcept;
	void setRotation(float roll, float pitch, float yaw) noexcept;
	DirectX::XMMATRIX getTransform() const noexcept override;
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