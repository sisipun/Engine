#ifndef PIXEL_SHADER_H
#define PIXEL_SHADER_H

#include "bindable.h"

class PixelShader : public Bindable
{
public:
	PixelShader(const Renderer& renderer, const std::string& path);
	
	void bind(const Renderer& renderer) noexcept override;
	static std::string getUid(const std::string& path) noexcept;

protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
};

#endif
