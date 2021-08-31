#include "input_layout.h"
#include "renderer_throw_macros.h"

InputLayout::InputLayout(const Renderer& renderer, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* vertexShaderBytecode)
{
	HRESULT hResult;
	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateInputLayout(
		layout.data(),
		(UINT)layout.size(),
		vertexShaderBytecode->GetBufferPointer(),
		vertexShaderBytecode->GetBufferSize(),
		&inputLayout
	));
}

void InputLayout::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->IASetInputLayout(inputLayout.Get());
}