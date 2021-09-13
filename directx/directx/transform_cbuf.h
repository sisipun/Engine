#ifndef TRANSFORM_CBUF_H
#define TRANSFORM_CBUF_H

#include <DirectXMath.h>

#include "constant_buffer.h"
#include "drawable.h"

class TransformCbuf : public Bindable
{
public:
	TransformCbuf(const Renderer& renderer, const Drawable& parent);

	void bind(const Renderer& renderer) noexcept override;

private:
	static std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> vertexConstantBuffer;
	const Drawable& parent;
};

#endif
