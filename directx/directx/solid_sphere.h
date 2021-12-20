#ifndef SOLID_SPHERE_H
#define SOLID_SPHERE_H

#include "drawable.h"

class SolidSphere : public Drawable
{
public:
	SolidSphere(const Renderer& renderer, float radius);
	void setPos(DirectX::XMFLOAT3 pos) noexcept;
	DirectX::XMMATRIX getTransform() const noexcept override;
private:
	DirectX::XMFLOAT3 pos = { 1.0f, 1.0f, 1.0f };
};

#endif