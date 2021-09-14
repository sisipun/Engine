#include "melon.h"
#include "constant_buffer.h"
#include "index_buffer.h"
#include "input_layout.h"
#include "pixel_shader.h"
#include "topology.h"
#include "transform_cbuf.h"
#include "vertex_buffer.h"
#include "vertex_shader.h"
#include "sphere.h"

Melon::Melon(
	const Renderer& renderer,
	std::mt19937& range,
	std::uniform_real_distribution<float>& radiusDist,
	std::uniform_real_distribution<float>& anglesDist,
	std::uniform_real_distribution<float>& deltaAnglesDist,
	std::uniform_real_distribution<float>& deltaOrientationDist,
	std::uniform_int_distribution<int>& longDist,
	std::uniform_int_distribution<int>& latDist
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
		auto vertexShader = std::make_unique<VertexShader>(renderer, L"color_index_vertex.cso");
		auto vertexShaderBytecode = vertexShader->getBytecode();
		addStaticBind(std::move(vertexShader));

		addStaticBind(std::make_unique<PixelShader>(renderer, L"color_index_pixel.cso"));

		struct ConstantBuffer
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			} face_colors[8];
		};
		const ConstantBuffer constantBuffer =
		{
			{
				{ 1.0f, 1.0f, 1.0f },
				{ 1.0f, 0.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f },
				{ 1.0f, 1.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f },
				{ 1.0f, 0.0f, 1.0f },
				{ 0.0f, 1.0f, 1.0f },
				{ 0.0f, 0.0f, 0.0f },
			}
		};
		addStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer>>(renderer, constantBuffer));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		addStaticBind(std::make_unique<InputLayout>(renderer, inputElementDesc, vertexShaderBytecode));

		addStaticBind(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}

	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
	};
	auto model = Sphere::make<Vertex>(latDist(range), longDist(range));
	model.transform(DirectX::XMMatrixScaling(1.0f, 1.0f, 1.2f));

	addBind(std::make_unique<VertexBuffer>(renderer, model.vertices));

	addIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));

	addBind(std::make_unique<TransformCbuf>(renderer, *this));
}

void Melon::update(float dt) noexcept
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}

DirectX::XMMATRIX Melon::getTransform() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(radius, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}