#include "index_buffer.h"
#include "renderer_throw_macros.h"

IndexBuffer::IndexBuffer(const Renderer& renderer, const std::vector<unsigned short>& indices) : count((UINT)indices.size())
{
	HRESULT hResult;

	D3D11_BUFFER_DESC desription = {};
	desription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desription.Usage = D3D11_USAGE_DEFAULT;
	desription.CPUAccessFlags = 0;
	desription.MiscFlags = 0;
	desription.ByteWidth = UINT(count * sizeof(unsigned short));
	desription.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = indices.data();

	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateBuffer(&desription, &data, &indexBuffer));
}

void IndexBuffer::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

UINT IndexBuffer::getCount() const noexcept
{
	return count;
}
