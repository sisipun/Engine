#ifndef DRAWABLE_BASE_H
#define DRAWABLE_BASE_H

#include "drawable.h"

template<typename T>
class DrawableBase : public Drawable
{
protected:
	static bool isStaticInitialized() noexcept
	{
		return !staticBinds.empty();
	}

	static void addStaticBind(std::unique_ptr<Bindable> bind) noexcept
	{
		staticBinds.push_back(std::move(bind));
	}

	void addStaticIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer) noexcept
	{
		this->indexBuffer = indexBuffer.get();
		staticBinds.push_back(std::move(indexBuffer));
	}

	void setIndexFromStatic() noexcept
	{
		for (const auto& bind : staticBinds)
		{
			if (const auto pointer = dynamic_cast<IndexBuffer*>(bind.get()))
			{
				indexBuffer = pointer;
				return;
			}
		}
	}

private:
	const std::vector<std::unique_ptr<Bindable>>& getStaticBinds() const noexcept override
	{
		return staticBinds;
	}

	static std::vector<std::unique_ptr<Bindable>> staticBinds;
};

template<typename T>
std::vector<std::unique_ptr<Bindable>> DrawableBase<T>::staticBinds;

#endif
