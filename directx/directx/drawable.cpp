#include "drawable.h"

void Drawable::draw(const Renderer& renderer) const
{
	for (auto& bind : binds)
	{
		bind->bind(renderer);
	}

	renderer.drawIndexed(indexBuffer->getCount());
}

void Drawable::addBind(std::shared_ptr<Bindable> bind) noexcept
{
	if (typeid(*bind) == typeid(IndexBuffer))
	{
		this->indexBuffer = &static_cast<IndexBuffer&>(*bind);
	}
	binds.push_back(std::move(bind));
}