#include "index_buffer.h"
#include "renderer_throw_macros.h"

IndexBuffer::IndexBuffer(const Renderer& renderer, const std::vector<unsigned short>& indices) : count((UINT)indices.size())
{
	HRESULT hResult;

	D3D11_BUFFER_DESC indexBufferDesription = {};
	indexBufferDesription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesription.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesription.CPUAccessFlags = 0;
	indexBufferDesription.MiscFlags = 0;
	indexBufferDesription.ByteWidth = UINT(count * sizeof(unsigned short));
	indexBufferDesription.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA indexSourceData = {};
	indexSourceData.pSysMem = indices.data();

	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateBuffer(&indexBufferDesription, &indexSourceData, &indexBuffer));
}

void IndexBuffer::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

UINT IndexBuffer::getCount() const noexcept
{
	return count;
}