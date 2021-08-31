#include "box.h"
#include "constant_buffer.h"
#include "index_buffer.h"
#include "input_layout.h"
#include "pixel_shader.h"
#include "topology.h"
#include "transform_cbuf.h"
#include "vertex_buffer.h"
#include "vertex_shader.h"


Box::Box(
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
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;
	};

	const std::vector<Vertex> vertices = {
		{ -1.0f,-1.0f,-1.0f },
		{ 1.0f,-1.0f,-1.0f },
		{ -1.0f,1.0f,-1.0f },
		{ 1.0f,1.0f,-1.0f },
		{ -1.0f,-1.0f,1.0f },
		{ 1.0f,-1.0f,1.0f },
		{ -1.0f,1.0f,1.0f },
		{ 1.0f,1.0f,1.0f },
	};

	addBind(std::make_unique<VertexBuffer>(renderer, vertices));

	auto vertexShader = std::make_unique<VertexShader>(renderer, L"vertex.cso");
	auto vertexShaderBytecode = vertexShader->getBytecode();
	addBind(std::move(vertexShader));

	addBind(std::make_unique<PixelShader>(renderer, L"pixel.cso"));

	const std::vector<unsigned short> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};
	addIndexBuffer(std::make_unique<IndexBuffer>(renderer, indices));

	struct ConstantBuffer
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colors[6];
	};
	const ConstantBuffer constantBuffer =
	{
		{
			{ 1.0f, 0.0f, 1.0f },
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f },
			{ 1.0f, 1.0f, 0.0f },
			{ 0.0f, 1.0f, 1.0f },
		}
	};
	addBind(std::make_unique<PixelConstantBuffer<ConstantBuffer>>(renderer, constantBuffer));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc =
	{
		{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	addBind(std::make_unique<InputLayout>(renderer, inputElementDesc, vertexShaderBytecode));

	addBind(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_unique<TransformCbuf>(renderer, *this));
}

void Box::update(float dt) noexcept
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}

DirectX::XMMATRIX Box::getTransform() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(radius, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}