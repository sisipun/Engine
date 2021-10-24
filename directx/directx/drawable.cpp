#include "drawable.h"

void Drawable::draw(const Renderer& renderer) const
{
	for (auto& bindable : bindables)
	{
		bindable->bind(renderer);
	}

	renderer.drawIndexed(indexBuffer->getCount());
}

void Drawable::addBind(std::shared_ptr<Bindable> bindable) noexcept
{
	if (typeid(*bindable) == typeid(IndexBuffer))
	{
		this->indexBuffer = &static_cast<IndexBuffer&>(*bindable);
	}
	bindables.push_back(std::move(bindable));
}