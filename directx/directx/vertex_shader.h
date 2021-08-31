#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include "bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(const Renderer& renderer, const std::wstring& path);
	
	void bind(const Renderer& renderer) noexcept override;
	ID3DBlob* getBytecode() const noexcept;

protected:
	Microsoft::WRL::ComPtr<ID3DBlob> bytecodeBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
};

#endif 