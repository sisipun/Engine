#include "transform_cbuf.h"


TransformCbuf::TransformCbuf(const Renderer& renderer, const Drawable& parent) : vertexConstantBuffer(renderer), parent(parent)
{
}

void TransformCbuf::bind(const Renderer& renderer) noexcept
{
	vertexConstantBuffer.update(renderer, DirectX::XMMatrixTranspose(parent.getTransform() * renderer.getProjection()));
	vertexConstantBuffer.bind(renderer);
}