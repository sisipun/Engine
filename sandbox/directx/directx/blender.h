#ifndef BLENDER_H
#define BLENDER_H

#include <array>
#include <optional>

#include "bindable.h"

class Blender : public Bindable
{
public:
	Blender(const Renderer& renderer, bool blending, std::optional<float> factor = {});

	void bind(const Renderer& renderer) noexcept override;
	void setFactor(float factor) noexcept;
	float getFactor() const noexcept;
	static std::string getUid(bool blending, std::optional<float> factor = {}) noexcept;

protected:
	Microsoft::WRL::ComPtr<ID3D11BlendState> blender;
	bool blending;
	std::optional<std::array<float, 4>> factors;
};

#endif