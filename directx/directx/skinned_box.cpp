#include "skinned_box.h"
#include "constant_buffer.h"
#include "index_buffer.h"
#include "input_layout.h"
#include "pixel_shader.h"
#include "topology.h"
#include "transform_cbuf.h"
#include "vertex_buffer.h"
#include "vertex_shader.h"
#include "texture.h"
#include "sampler.h"
#include "surface.h"
#include "cube.h"

#include <sstream>

SkinnedBox::SkinnedBox(
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
				float u;
				float v;
			} tex;
		};
		auto model = Cube::makeSkinned<Vertex>();

		addStaticBind(std::make_unique<Texture>(renderer, Surface::fromFile("Images\\cube.png")));
		addStaticBind(std::make_unique<VertexBuffer>(renderer, model.vertices));
		addStaticBind(std::make_unique<Sampler>(renderer));

		auto vertexShader = std::make_unique<VertexShader>(renderer, L"texture_vertex.cso");
		auto vertexShaderBytecode = vertexShader->getBytecode();
		addStaticBind(std::move(vertexShader));
		addStaticBind(std::make_unique<PixelShader>(renderer, L"texture_pixel.cso"));

		addStaticIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> inputDescription =
		{
			{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
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

void SkinnedBox::update(float dt) noexcept
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}

DirectX::XMMATRIX SkinnedBox::getTransform() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(radius, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}