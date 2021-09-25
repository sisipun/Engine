#ifndef SOLID_SPHERE_H
#define SOLID_SPHERE_H

#include "drawable_base.h"

class SolidSphere : public DrawableBase<SolidSphere>
{
public:
	SolidSphere(const Renderer& renderer, float radius);
	void update(float dt) noexcept override;
	void setPos(DirectX::XMFLOAT3 pos) noexcept;
	DirectX::XMMATRIX getTransform() const noexcept override;
private:
	DirectX::XMFLOAT3 pos = { 1.0f, 1.0f, 1.0f };
};

#endif