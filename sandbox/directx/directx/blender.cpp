#include "blender.h"
#include "renderer_throw_macros.h"

Blender::Blender(const Renderer& renderer, bool blending, std::optional<float> factor) : blending(blending)
{
	HRESULT hResult;

	if (factor)
	{
		factors.emplace();
		factors->fill(*factor);
	}

	D3D11_BLEND_DESC description = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
	auto& target = description.RenderTarget[0];
	if (blending)
	{
		target.BlendEnable = TRUE;
		if (factor)
		{
			target.SrcBlend = D3D11_BLEND_BLEND_FACTOR;
			target.DestBlend = D3D11_BLEND_INV_BLEND_FACTOR;
		}
		else 
		{
			target.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			target.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		}
	}

	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateBlendState(&description, &blender));
}

void Blender::bind(const Renderer& renderer) noexcept
{
	const float* data = factors ? factors->data() : nullptr;
	renderer.getContext()->OMSetBlendState(blender.Get(), data, 0xFFFFFFFF);
}

void Blender::setFactor(float factor) noexcept
{
	factors->fill(factor);
}

float Blender::getFactor() const noexcept
{
	return factors->front();
}

std::string Blender::getUid(bool blending, std::optional<float> factor) noexcept
{
	return typeid(Blender).name() + std::string("#") + (blending ? "b" : "n") + (factor ? std::string("#f") + std::to_string(*factor) : "");
}