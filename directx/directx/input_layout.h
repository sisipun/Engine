#ifndef INPUT_LAYOUT_H
#define INPUT_LAYOUT_H

#include "bindable.h"
#include "vertex.h"

class InputLayout : public Bindable
{
public:
	InputLayout(const Renderer& renderer, const VertexLayout& layout, ID3DBlob* vertexShaderBytecode);

	void bind(const Renderer& renderer) noexcept override;
	std::string getUid() const noexcept override;

protected:
	VertexLayout layout;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
};

#endif