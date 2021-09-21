#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "bindable.h"
#include "renderer_throw_macros.h"

class VertexBuffer : public Bindable
{
public:
	template<typename V>
	VertexBuffer(const Renderer& renderer, const std::vector<V>& vertices) : stride(sizeof(V))
	{
		HRESULT hResult;

		D3D11_BUFFER_DESC description = {};
		description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		description.Usage = D3D11_USAGE_DEFAULT;
		description.CPUAccessFlags = 0;
		description.MiscFlags = 0;
		description.ByteWidth = UINT(sizeof(V) * vertices.size());
		description.StructureByteStride = sizeof(V);

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = vertices.data();

		RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateBuffer(&description, &data, &vertexBuffer));
	}

	void bind(const Renderer& renderer) noexcept override;

private:
	UINT stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
};

#endif 
