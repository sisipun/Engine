#include "vertex_shader.h"
#include "renderer_throw_macros.h"

VertexShader::VertexShader(const Renderer& renderer, const std::wstring& path)
{
	HRESULT hResult;

	RENDERER_THROW_NOINFO(hResult, D3DReadFileToBlob(path.c_str(), &bytecodeBlob));
	RENDERER_THROW_NOINFO(hResult, renderer.getDevice()->CreateVertexShader(bytecodeBlob->GetBufferPointer(), bytecodeBlob->GetBufferSize(), nullptr, &vertexShader));
}

void VertexShader::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->VSSetShader(vertexShader.Get(), nullptr, 0);
}

ID3DBlob* VertexShader::getBytecode() const noexcept
{
	return bytecodeBlob.Get();
}