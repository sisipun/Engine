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

		D3D11_BUFFER_DESC vertexBufferDesription = {};
		vertexBufferDesription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesription.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesription.CPUAccessFlags = 0;
		vertexBufferDesription.MiscFlags = 0;
		vertexBufferDesription.ByteWidth = UINT(sizeof(V) * vertices.size());
		vertexBufferDesription.StructureByteStride = sizeof(V);

		D3D11_SUBRESOURCE_DATA vertexSourceData = {};
		vertexSourceData.pSysMem = vertices.data();

		RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateBuffer(&vertexBufferDesription, &vertexSourceData, &vertexBuffer));
	}

	void bind(const Renderer& renderer) noexcept override;

private:
	UINT stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
};

#endif 
