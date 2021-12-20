#ifndef INPUT_LAYOUT_H
#define INPUT_LAYOUT_H

#include "bindable.h"
#include "vertex.h"

class InputLayout : public Bindable
{
public:
	InputLayout(const Renderer& renderer, const VertexLayout& layout, ID3DBlob* vertexShaderBytecode);

	void bind(const Renderer& renderer) noexcept override;
	static std::string getUid(const VertexLayout& layout, ID3DBlob* vertexShaderBytecode) noexcept;

protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
};

#endif