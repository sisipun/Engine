#ifndef CYLINDER_H
#define CYLINDER_H

#include "default_drawable_base.h"

class Cylinder : public DefaultDrawableBase<Cylinder>
{
public:
	Cylinder(const Renderer& renderer,
		std::mt19937& range,
		std::uniform_real_distribution<float>& radiusDist,
		std::uniform_real_distribution<float>& anglesDist,
		std::uniform_real_distribution<float>& deltaAnglesDist,
		std::uniform_real_distribution<float>& deltaOrientationDist,
		std::uniform_real_distribution<float>& tesselationDist);
};

#endif