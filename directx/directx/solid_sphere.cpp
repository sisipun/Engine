#include "solid_sphere.h"
#include "constant_buffer.h"
#include "index_buffer.h"
#include "input_layout.h"
#include "pixel_shader.h"
#include "topology.h"
#include "transform_cbuf.h"
#include "vertex_buffer.h"
#include "vertex_shader.h"
#include "sphere.h"

SolidSphere::SolidSphere(const Renderer& renderer, float radius)
{
	if (!isStaticInitialized())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
		};
		auto model = Sphere::make<Vertex>();
		model.transform(DirectX::XMMatrixScaling(radius, radius, radius));

		addStaticBind(std::make_unique<VertexBuffer>(renderer, model.vertices));

		auto vertexShader = std::make_unique<VertexShader>(renderer, L"solid_vertex.cso");
		auto vertexShaderBytecode = vertexShader->getBytecode();
		addStaticBind(std::move(vertexShader));
		addStaticBind(std::make_unique<PixelShader>(renderer, L"solid_pixel.cso"));

		addStaticIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));

		struct ConstantData
		{
			DirectX::XMFLOAT3 color = { 1.0f, 1.0f, 1.0f };
			float padding;
		} constData;
		addStaticBind(std::make_unique<PixelConstantBuffer<ConstantData>>(renderer, constData));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> inputDescription =
		{
			{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		addStaticBind(std::make_unique<InputLayout>(renderer, inputDescription, vertexShaderBytecode));
		addStaticBind(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		setIndexFromStatic();
	}

	addBind(std::make_unique<TransformCbuf>(renderer, *this));
}

void SolidSphere::update(float dt) noexcept
{
}

void SolidSphere::setPos(DirectX::XMFLOAT3 pos) noexcept
{
	this->pos = pos;
}

DirectX::XMMATRIX SolidSphere::getTransform() const noexcept
{
	return DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}