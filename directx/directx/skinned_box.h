#ifndef SKINNED_BOX
#define SKINNED_BOX

#include "default_drawable_base.h"

class SkinnedBox : public DefaultDrawableBase<SkinnedBox>
{
public:
	SkinnedBox(const Renderer& renderer,
		std::mt19937& range,
		std::uniform_real_distribution<float>& radiusDist,
		std::uniform_real_distribution<float>& anglesDist,
		std::uniform_real_distribution<float>& deltaAnglesDist,
		std::uniform_real_distribution<float>& deltaOrientationDist);
};

#endif
