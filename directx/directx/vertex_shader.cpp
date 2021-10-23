#include <typeinfo>

#include "vertex_shader.h"
#include "renderer_throw_macros.h"

VertexShader::VertexShader(const Renderer& renderer, const std::string& path)
{
	HRESULT hResult;

	RENDERER_THROW_NOINFO(hResult, D3DReadFileToBlob(std::wstring(path.begin(), path.end()).c_str(), &bytecodeBlob));
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

std::string VertexShader::getUid(const std::string& path) noexcept
{
	return typeid(VertexShader).name() + std::string("#") + path;
}