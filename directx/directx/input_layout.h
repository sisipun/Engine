#ifndef INPUT_LAYOUT_H
#define INPUT_LAYOUT_H

#include "bindable.h"

class InputLayout : public Bindable
{
public:
	InputLayout(const Renderer& renderer, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* vertexShaderBytecode);

	void bind(const Renderer& renderer) noexcept override;

protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
};

#endif