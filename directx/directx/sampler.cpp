#include "sampler.h"
#include "renderer_throw_macros.h"
#include "bindable_codex.h"

Sampler::Sampler(const Renderer& renderer)
{
	HRESULT hResult;

	D3D11_SAMPLER_DESC description = {};
	description.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	description.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	description.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	description.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateSamplerState(&description, &sampler));
}

void Sampler::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->PSSetSamplers(0, 1, sampler.GetAddressOf());
}