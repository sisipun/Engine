#include "drawable.h"

void Drawable::draw(const Renderer& renderer) const
{
	for (auto& bind : binds)
	{
		bind->bind(renderer);
	}

	renderer.drawIndexed(indexBuffer->getCount());
}

void Drawable::addBind(std::unique_ptr<Bindable> bind) noexcept
{
	binds.push_back(std::move(bind));
}

void Drawable::addIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer) noexcept
{
	this->indexBuffer = indexBuffer.get();
	binds.push_back(std::move(indexBuffer));
}