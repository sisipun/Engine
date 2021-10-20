#include <typeinfo>

#include "vertex_shader.h"
#include "renderer_throw_macros.h"
#include "bindable_codex.h"

VertexShader::VertexShader(const Renderer& renderer, const std::string& path) : path(path)
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

std::string VertexShader::getUid() const noexcept
{
	return generateUid(path);
}

std::shared_ptr<Bindable> VertexShader::resolve(const Renderer& renderer, const std::string& path)
{
	auto bindable = Codex::resolve(generateUid(path));
	if (!bindable)
	{
		bindable = std::make_shared<VertexShader>(renderer, path);
	}
	return bindable;
}

std::string VertexShader::generateUid(const std::string& path)
{
	return typeid(VertexShader).name() + std::string("#") + path;
}