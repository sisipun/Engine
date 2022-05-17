#include "rasterizer.h"
#include "renderer_throw_macros.h"

Rasterizer::Rasterizer(const Renderer& renderer, bool twoSided) : twoSided(twoSided)
{
	HRESULT hResult;

	D3D11_RASTERIZER_DESC description = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
	description.CullMode = twoSided ? D3D11_CULL_NONE : D3D11_CULL_BACK;

	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateRasterizerState(&description, &rasterizer));
}

void Rasterizer::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->RSSetState(rasterizer.Get());
}

std::string Rasterizer::getUid(bool twoSided) noexcept
{
	return typeid(Rasterizer).name() + std::string("#") + (twoSided ? "ts" : "os");
}