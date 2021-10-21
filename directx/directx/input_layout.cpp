#include "input_layout.h"
#include "renderer_throw_macros.h"

InputLayout::InputLayout(const Renderer& renderer, const VertexLayout& layout, ID3DBlob* vertexShaderBytecode) : Bindable(true), layout(layout)
{
	const auto descLayout = layout.getDescLayout();
	HRESULT hResult;
	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateInputLayout(
		descLayout.data(),
		(UINT)descLayout.size(),
		vertexShaderBytecode->GetBufferPointer(),
		vertexShaderBytecode->GetBufferSize(),
		&inputLayout
	));
}

void InputLayout::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->IASetInputLayout(inputLayout.Get());
}

std::string InputLayout::getUid() const noexcept
{
	return typeid(InputLayout).name() + std::string("#") + layout.getCode();
}