#include "solid_sphere.h"
#include "bindable_store.h"
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

	addBind(std::make_shared<VertexBuffer>(renderer, model.vertexBufferData));

	auto vertexShader = BindableStore::resolve<VertexShader>(renderer, "solid_vertex.cso");
	auto vertexShaderBytecode = vertexShader->getBytecode();
	addBind(std::move(vertexShader));
	addBind(BindableStore::resolve<PixelShader>(renderer, "solid_pixel.cso"));

	addBind(std::make_shared<IndexBuffer>(renderer, model.indices));

	struct ConstantData
	{
		DirectX::XMFLOAT3 color = { 1.0f, 1.0f, 1.0f };
		float padding;
	} constData;
	addBind(std::make_shared<PixelConstantBuffer<ConstantData>>(renderer, constData));

	addBind(BindableStore::resolve<InputLayout>(renderer, model.vertexBufferData.getLayout(), vertexShaderBytecode));
	addBind(BindableStore::resolve<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_shared<TransformCbuf>(renderer, *this));
}

void SolidSphere::setPos(DirectX::XMFLOAT3 pos) noexcept
{
	this->pos = pos;
}

DirectX::XMMATRIX SolidSphere::getTransform() const noexcept
{
	return DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}