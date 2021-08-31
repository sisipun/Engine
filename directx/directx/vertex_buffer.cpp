#include "vertex_buffer.h"

void VertexBuffer::bind(const Renderer& renderer) noexcept
{
	const UINT offset = 0u;
	renderer.getContext()->IASetVertexBuffers(0u, 1u, vertexBuffer.GetAddressOf(), &stride, &offset);
}