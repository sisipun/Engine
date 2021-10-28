#ifndef TEXTURE_H
#define TEXTURE_H

#include "bindable.h"
#include "surface.h"

class Texture : public Bindable
{
public:
	Texture(const Renderer& renderer, const std::string& path, unsigned int slot = 0);

	void bind(const Renderer& rennderer) noexcept override;
	static std::string getUid(const std::string& path, unsigned int slot = 0) noexcept;
	bool hasAplha() const noexcept;

private:
	bool hasAlpha = false;
	unsigned int slot;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureView;
};

#endif