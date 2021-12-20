#include "pixel_shader.h"
#include "renderer_throw_macros.h"

PixelShader::PixelShader(const Renderer& renderer, const std::string& path)
{
	HRESULT hResult;
	Microsoft::WRL::ComPtr<ID3DBlob> blob;

	RENDERER_THROW_NOINFO(hResult, D3DReadFileToBlob(std::wstring(path.begin(), path.end()).c_str(), &blob));
	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader));
}

void PixelShader::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->PSSetShader(pixelShader.Get(), nullptr, 0);
}

std::string PixelShader::getUid(const std::string& path) noexcept
{
	return typeid(PixelShader).name() + std::string("#") + path;
}