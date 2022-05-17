#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "bindable.h"
#include "renderer_throw_macros.h"
#include "vertex.h"

class VertexBuffer : public Bindable
{
public:
	VertexBuffer(const Renderer& renderer, const VertexBufferData& data);

	void bind(const Renderer& renderer) noexcept override;

private:
	UINT stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
};

#endif 
