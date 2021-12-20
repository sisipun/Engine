#ifndef BINDABLE_H
#define BINDABLE_H

#include "renderer.h"

class Bindable
{
public:
	virtual ~Bindable() = default;

	virtual void bind(const Renderer& renderer) noexcept = 0;
};

#endif
