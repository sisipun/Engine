#ifndef TEXTURE_H
#define TEXTURE_H

#include "bindable.h"
#include "surface.h"

class Texture : public Bindable
{
public:
	Texture(const Renderer& renderer, const Surface& surface, unsigned int slot = 0);
	void bind(const Renderer& rennderer) noexcept override;
private:
	unsigned int slot;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureView;
};

#endif