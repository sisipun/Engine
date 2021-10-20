#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include "bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(const Renderer& renderer, const std::string& path);
	
	void bind(const Renderer& renderer) noexcept override;
	ID3DBlob* getBytecode() const noexcept;
	std::string getUid() const noexcept override;
	static std::shared_ptr<Bindable> resolve(const Renderer& renderer, const std::string& path);
	static std::string generateUid(const std::string& path);

protected:
	std::string path;
	Microsoft::WRL::ComPtr<ID3DBlob> bytecodeBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
};

#endif 