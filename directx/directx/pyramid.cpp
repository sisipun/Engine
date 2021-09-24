#include "pyramid.h"
#include "constant_buffer.h"
#include "index_buffer.h"
#include "input_layout.h"
#include "pixel_shader.h"
#include "topology.h"
#include "transform_cbuf.h"
#include "vertex_buffer.h"
#include "vertex_shader.h"
#include "cone.h"

Pyramid::Pyramid(
	const Renderer& renderer,
	std::mt19937& range,
	std::uniform_real_distribution<float>& radiusDist,
	std::uniform_real_distribution<float>& anglesDist,
	std::uniform_real_distribution<float>& deltaAnglesDist,
	std::uniform_real_distribution<float>& deltaOrientationDist
) :
	radius(radiusDist(range)),
	droll(deltaOrientationDist(range)),
	dpitch(deltaOrientationDist(range)),
	dyaw(deltaOrientationDist(range)),
	dtheta(deltaAnglesDist(range)),
	dphi(deltaAnglesDist(range)),
	dchi(deltaAnglesDist(range)),
	theta(anglesDist(range)),
	phi(anglesDist(range)),
	chi(anglesDist(range))
{
	if (!isStaticInitialized())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			struct
			{
				unsigned char r;
				unsigned char g;
				unsigned char b;
				unsigned char a;
			} color;
		};
		auto model = Cone::make<Vertex>(4);

		model.vertices[0].color = { 255, 255, 0 };
		model.vertices[1].color = { 255, 255, 0 };
		model.vertices[2].color = { 255, 255, 0 };
		model.vertices[3].color = { 255, 255, 0 };
		model.vertices[4].color = { 255, 255, 80 };
		model.vertices[5].color = { 255, 10, 0 };

		model.transform(DirectX::XMMatrixScaling(1.0f, 1.0f, 0.7f));

		addStaticBind(std::make_unique<VertexBuffer>(renderer, model.vertices));

		auto vertexShader = std::make_unique<VertexShader>(renderer, L"color_blend_vertex.cso");
		auto vertexShaderBytecode = vertexShader->getBytecode();
		addStaticBind(std::move(vertexShader));

		addStaticBind(std::make_unique<PixelShader>(renderer, L"color_blend_pixel.cso"));

		addStaticIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> inputDesription =
		{
			{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		addStaticBind(std::make_unique<InputLayout>(renderer, inputDesription, vertexShaderBytecode));

		addStaticBind(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		setIndexFromStatic();
	}

	addBind(std::make_unique<TransformCbuf>(renderer, *this));
}

void Pyramid::update(float dt) noexcept
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}

DirectX::XMMATRIX Pyramid::getTransform() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(radius, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi);
}