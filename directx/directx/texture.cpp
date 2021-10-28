#include "texture.h"
#include "renderer_throw_macros.h"

Texture::Texture(const Renderer& renderer, const std::string& path, unsigned int slot) : slot(slot)
{
	const auto surface = Surface::fromFile(path);
	hasAlpha = surface.isAlphaLoaded();

	HRESULT hResult;

	D3D11_TEXTURE2D_DESC textureDescription = {};
	textureDescription.Width = surface.getWidth();
	textureDescription.Height = surface.getHeight();
	textureDescription.MipLevels = 1;
	textureDescription.ArraySize = 1;
	textureDescription.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	textureDescription.SampleDesc.Count = 1;
	textureDescription.SampleDesc.Quality = 0;
	textureDescription.Usage = D3D11_USAGE_DEFAULT;
	textureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDescription.CPUAccessFlags = 0;
	textureDescription.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = surface.getBufferPointer();
	data.SysMemPitch = surface.getWidth() * sizeof(Surface::Color);
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	
	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateTexture2D(&textureDescription, &data, &texture));

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderViewDescription = {};
	shaderViewDescription.Format = textureDescription.Format;
	shaderViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderViewDescription.Texture2D.MostDetailedMip = 0;
	shaderViewDescription.Texture2D.MipLevels = 1;

	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateShaderResourceView(texture.Get(), &shaderViewDescription, &textureView));
}

void Texture::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->PSSetShaderResources(slot, 1, textureView.GetAddressOf());
}

std::string Texture::getUid(const std::string& path, unsigned int slot) noexcept
{
	return typeid(Texture).name() + std::string("#") + path + std::string("#") + std::to_string(slot);
}

bool Texture::hasAplha() const noexcept
{
	return hasAlpha;
}