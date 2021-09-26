#ifndef BOX_H
#define BOX_H

#include "drawable_base.h"

class Box : public DrawableBase<Box>
{
public:
	Box(const Renderer& renderer,
		std::mt19937& range,
		std::uniform_real_distribution<float>& radiusDist,
		std::uniform_real_distribution<float>& anglesDist,
		std::uniform_real_distribution<float>& deltaAnglesDist,
		std::uniform_real_distribution<float>& deltaOrientationDist,
		std::uniform_real_distribution<float>& sizeDist,
		DirectX::XMFLOAT3 materialColor);

	void update(float dt) noexcept override;
	DirectX::XMMATRIX getTransform() const noexcept override;

private:
	float radius;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;

	float droll;
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;

	DirectX::XMFLOAT3X3 model;
};

#endif
