#include "texture.h"
#include "renderer_throw_macros.h"

Texture::Texture(const Renderer& renderer, const std::string& path, unsigned int slot) : slot(slot)
{
	const auto surface = Surface::fromFile(path);
	alpha = surface.isAlphaLoaded();

	HRESULT hResult;

	D3D11_TEXTURE2D_DESC textureDescription = {};
	textureDescription.Width = surface.getWidth();
	textureDescription.Height = surface.getHeight();
	textureDescription.MipLevels = 0;
	textureDescription.ArraySize = 1;
	textureDescription.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	textureDescription.SampleDesc.Count = 1;
	textureDescription.SampleDesc.Quality = 0;
	textureDescription.Usage = D3D11_USAGE_DEFAULT;
	textureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDescription.CPUAccessFlags = 0;
	textureDescription.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	
	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateTexture2D(&textureDescription, nullptr, &texture));

	renderer.getContext()->UpdateSubresource(texture.Get(), 0, nullptr, surface.getBufferPointerConst(), surface.getWidth() * sizeof(Surface::Color), 0);

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderViewDescription = {};
	shaderViewDescription.Format = textureDescription.Format;
	shaderViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderViewDescription.Texture2D.MostDetailedMip = 0;
	shaderViewDescription.Texture2D.MipLevels = -1;

	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateShaderResourceView(texture.Get(), &shaderViewDescription, &textureView));
	renderer.getContext()->GenerateMips(textureView.Get());
}

void Texture::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->PSSetShaderResources(slot, 1, textureView.GetAddressOf());
}

std::string Texture::getUid(const std::string& path, unsigned int slot) noexcept
{
	return typeid(Texture).name() + std::string("#") + path + std::string("#") + std::to_string(slot);
}

bool Texture::hasAlpha() const noexcept
{
	return alpha;
}