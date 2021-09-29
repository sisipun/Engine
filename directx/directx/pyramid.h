#ifndef PYRAMID_H
#define PYARMID_H

#include "default_drawable_base.h"

class Pyramid : public DefaultDrawableBase<Pyramid>
{
public:
	Pyramid(const Renderer& renderer,
		std::mt19937& range,
		std::uniform_real_distribution<float>& radiusDist,
		std::uniform_real_distribution<float>& anglesDist,
		std::uniform_real_distribution<float>& deltaAnglesDist,
		std::uniform_real_distribution<float>& deltaOrientationDist,
		std::uniform_real_distribution<float>& tesselationDist);
};

#endif