#ifndef TEXTURE_H
#define TEXTURE_H

#include "bindable.h"
#include "surface.h"

class Texture : public Bindable
{
public:
	Texture(const Renderer& renderer, const std::string& path, unsigned int slot = 0);
	void bind(const Renderer& rennderer) noexcept override;
	std::string getUid() const noexcept override;

private:
	unsigned int slot;
	std::string path;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureView;
};

#endif