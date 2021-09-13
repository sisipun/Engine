#include "transform_cbuf.h"


TransformCbuf::TransformCbuf(const Renderer& renderer, const Drawable& parent) : parent(parent)
{
	if (!vertexConstantBuffer) 
	{
		vertexConstantBuffer = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(renderer);
	}
}

void TransformCbuf::bind(const Renderer& renderer) noexcept
{
	vertexConstantBuffer->update(renderer, DirectX::XMMatrixTranspose(parent.getTransform() * renderer.getProjection()));
	vertexConstantBuffer->bind(renderer);
}

std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> TransformCbuf::vertexConstantBuffer;