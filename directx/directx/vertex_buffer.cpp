#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(const Renderer& renderer, const VertexBufferData& data) : stride(data.getLayout().size())
{
	HRESULT hResult;

	D3D11_BUFFER_DESC description = {};
	description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	description.Usage = D3D11_USAGE_DEFAULT;
	description.CPUAccessFlags = 0;
	description.MiscFlags = 0;
	description.ByteWidth = UINT(data.sizeBytes());
	description.StructureByteStride = stride;

	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = data.getData();

	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateBuffer(&description, &subresourceData, &vertexBuffer));
}

void VertexBuffer::bind(const Renderer& renderer) noexcept
{
	const UINT offset = 0u;
	renderer.getContext()->IASetVertexBuffers(0u, 1u, vertexBuffer.GetAddressOf(), &stride, &offset);
}