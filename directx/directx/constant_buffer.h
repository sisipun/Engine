#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

#include "bindable.h"
#include "renderer_throw_macros.h"

template<typename C>
class ConstantBuffer : public Bindable
{
public:
	ConstantBuffer(const Renderer& renderer, const C& consts, UINT slot = 0): slot(slot)
	{
		HRESULT hResult;
		D3D11_BUFFER_DESC description = {};
		description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		description.Usage = D3D11_USAGE_DYNAMIC;
		description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		description.MiscFlags = 0;
		description.ByteWidth = sizeof(consts);
		description.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = &consts;

		RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateBuffer(&description, &data, &constantBuffer));
	}

	ConstantBuffer(const Renderer& renderer, UINT slot = 0): slot(slot)
	{
		HRESULT hResult;
		D3D11_BUFFER_DESC desription = {};
		desription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desription.Usage = D3D11_USAGE_DYNAMIC;
		desription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desription.MiscFlags = 0;
		desription.ByteWidth = sizeof(C);
		desription.StructureByteStride = 0;

		RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateBuffer(&desription, nullptr, &constantBuffer));
	}

	void update(const Renderer& renderer, const C& consts)
	{
		HRESULT hResult;
		D3D11_MAPPED_SUBRESOURCE data;
		RENDERER_THROW_NOINFO(hResult, renderer.getContext()->Map(constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data));
		memcpy(data.pData, &consts, sizeof(consts));
		renderer.getContext()->Unmap(constantBuffer.Get(), 0);
	}

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
	UINT slot;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::constantBuffer;
	using ConstantBuffer<C>::slot;
public:
	using ConstantBuffer<C>::ConstantBuffer;

	void bind(const Renderer& renderer) noexcept
	{
		renderer.getContext()->VSSetConstantBuffers(slot, 1, constantBuffer.GetAddressOf());
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::constantBuffer;
	using ConstantBuffer<C>::slot;
public:
	using ConstantBuffer<C>::ConstantBuffer;

	void bind(const Renderer& renderer) noexcept
	{
		renderer.getContext()->PSSetConstantBuffers(slot, 1, constantBuffer.GetAddressOf());
	}
};

#endif