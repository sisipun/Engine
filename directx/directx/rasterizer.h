#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "bindable.h"

class Rasterizer : public Bindable
{
public:
	Rasterizer(const Renderer& renderer, bool twoSided);

	void bind(const Renderer& renderer) noexcept override;
	static std::string getUid(bool twoSided) noexcept;

protected:
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer;
	bool twoSided;
};

#endif
