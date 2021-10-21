#ifndef BINDABLE_H
#define BINDABLE_H

#include "renderer.h"

class Bindable
{
public:
	Bindable() : cacheable(false)
	{
	}

	Bindable(bool cacheable) : cacheable(cacheable)
	{
	}

	virtual ~Bindable() = default;

	virtual void bind(const Renderer& renderer) noexcept = 0;
	virtual std::string getUid() const noexcept 
	{
		return "?";
	}

	bool isCacheable() const noexcept
	{
		return cacheable;
	}
protected:
	const bool cacheable;
};

#endif
