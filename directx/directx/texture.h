#ifndef TEXTURE_H
#define TEXTURE_H

#include "bindable.h"
#include "surface.h"

class Texture : public Bindable
{
public:
	Texture(const Renderer& renderer, const Surface& surface);
	void bind(const Renderer& rennderer) noexcept override;
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureView;
};

#endif