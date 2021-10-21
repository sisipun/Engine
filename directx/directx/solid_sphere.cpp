#include "solid_sphere.h"
#include "constant_buffer.h"
#include "index_buffer.h"
#include "input_layout.h"
#include "pixel_shader.h"
#include "topology.h"
#include "transform_cbuf.h"
#include "vertex_buffer.h"
#include "vertex_shader.h"
#include "vertex.h"
#include "sphere.h"

SolidSphere::SolidSphere(const Renderer& renderer, float radius)
{
	auto model = Sphere::make();
	model.transform(DirectX::XMMatrixScaling(radius, radius, radius));

	addBind(std::make_unique<VertexBuffer>(renderer, model.vertexBufferData));

	auto vertexShader = std::make_unique<VertexShader>(renderer, "solid_vertex.cso");
	auto vertexShaderBytecode = vertexShader->getBytecode();
	addBind(std::move(vertexShader));
	addBind(std::make_unique<PixelShader>(renderer, "solid_pixel.cso"));

	addBind(std::make_unique<IndexBuffer>(renderer, model.indices));

	struct ConstantData
	{
		DirectX::XMFLOAT3 color = { 1.0f, 1.0f, 1.0f };
		float padding;
	} constData;
	addBind(std::make_unique<PixelConstantBuffer<ConstantData>>(renderer, constData));

	addBind(std::make_unique<InputLayout>(renderer, model.vertexBufferData.getLayout(), vertexShaderBytecode));
	addBind(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_unique<TransformCbuf>(renderer, *this));
}

void SolidSphere::setPos(DirectX::XMFLOAT3 pos) noexcept
{
	this->pos = pos;
}

DirectX::XMMATRIX SolidSphere::getTransform() const noexcept
{
	return DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}