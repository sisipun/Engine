#include "pixel_shader.h"
#include "renderer_throw_macros.h"

PixelShader::PixelShader(const Renderer& renderer, const std::wstring& path)
{
	HRESULT hResult;
	Microsoft::WRL::ComPtr<ID3DBlob> blob;

	RENDERER_THROW_NOINFO(hResult, D3DReadFileToBlob(path.c_str(), &blob));
	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader));
}

void PixelShader::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->PSSetShader(pixelShader.Get(), nullptr, 0);
}