#ifndef DEFAULT_DRAWABLE_BASE_H
#define DEFAULT_DRAWABLE_BASE_H

#include "drawable_base.h"

template<typename T>
class DefaultDrawableBase : public DrawableBase<T>
{
public:
	DefaultDrawableBase(
		const Renderer& renderer,
		std::mt19937& range,
		std::uniform_real_distribution<float>& radiusDist,
		std::uniform_real_distribution<float>& anglesDist,
		std::uniform_real_distribution<float>& deltaAnglesDist,
		std::uniform_real_distribution<float>& deltaOrientationDist
	) :
		radius(radiusDist(range)),
		droll(deltaOrientationDist(range)),
		dpitch(deltaOrientationDist(range)),
		dyaw(deltaOrientationDist(range)),
		dtheta(deltaAnglesDist(range)),
		dphi(deltaAnglesDist(range)),
		dchi(deltaAnglesDist(range)),
		theta(anglesDist(range)),
		phi(anglesDist(range)),
		chi(anglesDist(range))
	{
	}

	void update(float dt) noexcept override
	{
		roll += droll * dt;
		pitch += dpitch * dt;
		yaw += dyaw * dt;
		theta += dtheta * dt;
		phi += dphi * dt;
		chi += dchi * dt;
	}

	DirectX::XMMATRIX getTransform() const noexcept override
	{
		return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
			DirectX::XMMatrixTranslation(radius, 0.0f, 0.0f) *
			DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi);
	}

protected:
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
};

#endif 
