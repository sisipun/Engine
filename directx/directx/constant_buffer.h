#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

#include "bindable.h"
#include "renderer_throw_macros.h"

template<typename C>
class ConstantBuffer : public Bindable
{
public:
	ConstantBuffer(const Renderer& renderer, const C& consts)
	{
		HRESULT hResult;
		D3D11_BUFFER_DESC constantBufferDesription = {};
		constantBufferDesription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesription.Usage = D3D11_USAGE_DYNAMIC;
		constantBufferDesription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantBufferDesription.MiscFlags = 0;
		constantBufferDesription.ByteWidth = sizeof(consts);
		constantBufferDesription.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA constantSourceData = {};
		constantSourceData.pSysMem = &consts;

		RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateBuffer(&constantBufferDesription, &constantSourceData, &constantBuffer));
	}

	ConstantBuffer(const Renderer& renderer)
	{
		HRESULT hResult;
		D3D11_BUFFER_DESC constantBufferDesription = {};
		constantBufferDesription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesription.Usage = D3D11_USAGE_DYNAMIC;
		constantBufferDesription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantBufferDesription.MiscFlags = 0;
		constantBufferDesription.ByteWidth = sizeof(C);
		constantBufferDesription.StructureByteStride = 0;

		RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateBuffer(&constantBufferDesription, nullptr, &constantBuffer));
	}

	void update(const Renderer& renderer, const C& consts)
	{
		HRESULT hResult;
		D3D11_MAPPED_SUBRESOURCE mappedSubResource;
		RENDERER_THROW_NOINFO(hResult, renderer.getContext()->Map(constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource));
		memcpy(mappedSubResource.pData, &consts, sizeof(consts));
		renderer.getContext()->Unmap(constantBuffer.Get(), 0);
	}

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::constantBuffer;
public:
	using ConstantBuffer<C>::ConstantBuffer;

	void bind(const Renderer& renderer) noexcept
	{
		renderer.getContext()->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::constantBuffer;
public:
	using ConstantBuffer<C>::ConstantBuffer;

	void bind(const Renderer& renderer) noexcept
	{
		renderer.getContext()->PSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
	}
};

#endif