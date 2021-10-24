#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "bindable.h"
#include "index_buffer.h"

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable& drawable) = delete;
	virtual ~Drawable() = default;

	virtual DirectX::XMMATRIX getTransform() const noexcept = 0;
	void draw(const Renderer& renderer) const;

protected:
	template<typename T>
	std::shared_ptr<T> queryBindable() noexcept
	{
		for (auto& bindable : bindables)
		{
			if (typeid(*bindable) == typeid(T))
			{
				return std::static_pointer_cast<T>(bindable);
			}
		}

		return nullptr;
	}

	void addBind(std::shared_ptr<Bindable> bindable) noexcept;
	const IndexBuffer* indexBuffer = nullptr;
private:
	std::vector<std::shared_ptr<Bindable>> bindables;
};

#endif 
