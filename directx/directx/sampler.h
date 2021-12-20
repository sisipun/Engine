#ifndef SAMPLER_H
#define SAMPLER_H

#include "bindable.h"

class Sampler : public Bindable
{
public:
	Sampler(const Renderer& renderer);
	void bind(const Renderer& renderer) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler;
};

#endif 