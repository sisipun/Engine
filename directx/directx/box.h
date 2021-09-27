#ifndef BOX_H
#define BOX_H

#include "default_drawable_base.h"

class Box : public DefaultDrawableBase<Box>
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

	DirectX::XMMATRIX getTransform() const noexcept override;

private:
	DirectX::XMFLOAT3X3 model;
};

#endif
