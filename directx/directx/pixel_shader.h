#ifndef PIXEL_SHADER_H
#define PIXEL_SHADER_H

#include "bindable.h"

class PixelShader : public Bindable
{
public:
	PixelShader(const Renderer& renderer, const std::string& path);
	
	void bind(const Renderer& renderer) noexcept override;
	std::string getUid() const noexcept override;

protected:
	std::string path;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
};

#endif
