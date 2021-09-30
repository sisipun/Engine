#ifndef SUZANNE_H
#define SUZANNE_H

#include "default_drawable_base.h"

class Suzanne : public DefaultDrawableBase<Suzanne>
{
public:
	Suzanne(const Renderer& renderer,
		std::mt19937& range,
		std::uniform_real_distribution<float>& radiusDist,
		std::uniform_real_distribution<float>& anglesDist,
		std::uniform_real_distribution<float>& deltaAnglesDist,
		std::uniform_real_distribution<float>& deltaOrientationDist,
		DirectX::XMFLOAT3 materialColor,
		float scale);
};

#endif