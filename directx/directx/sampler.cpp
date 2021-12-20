#include "sampler.h"
#include "renderer_throw_macros.h"

Sampler::Sampler(const Renderer& renderer)
{
	HRESULT hResult;

	D3D11_SAMPLER_DESC description = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());
	description.Filter = D3D11_FILTER_ANISOTROPIC;
	description.MaxAnisotropy = D3D11_REQ_MAXANISOTROPY;
	description.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	description.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;

	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateSamplerState(&description, &sampler));
}

void Sampler::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->PSSetSamplers(0, 1, sampler.GetAddressOf());
}