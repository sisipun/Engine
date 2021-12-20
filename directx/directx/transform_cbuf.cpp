#include "transform_cbuf.h"


TransformCbuf::TransformCbuf(const Renderer& renderer, const Drawable& parent, UINT slot) : parent(parent)
{
	if (!vertexConstantBuffer) 
	{
		vertexConstantBuffer = std::make_unique<VertexConstantBuffer<Transforms>>(renderer, slot);
	}
}

void TransformCbuf::bind(const Renderer& renderer) noexcept
{
	const Transforms transforms = {
		DirectX::XMMatrixTranspose(parent.getTransform()),
		DirectX::XMMatrixTranspose(renderer.getCamera()),
		DirectX::XMMatrixTranspose(renderer.getProjection())
	};
	vertexConstantBuffer->update(renderer, transforms);
	vertexConstantBuffer->bind(renderer);
}

std::unique_ptr<VertexConstantBuffer<TransformCbuf::Transforms>> TransformCbuf::vertexConstantBuffer;