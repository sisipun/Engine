#include <array>

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
	std::uniform_real_distribution<float>& deltaOrientationDist,
	std::uniform_real_distribution<float>& tesselationDist
) : DefaultDrawableBase(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist)
{
	if (!isStaticInitialized())
	{
		auto vertexShader = std::make_unique<VertexShader>(renderer, L"blended_phong_vertex.cso");
		auto vertexShaderBytecode = vertexShader->getBytecode();
		addStaticBind(std::move(vertexShader));

		addStaticBind(std::make_unique<PixelShader>(renderer, L"blended_phong_pixel.cso"));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> inputDesription =
		{
			{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		addStaticBind(std::make_unique<InputLayout>(renderer, inputDesription, vertexShaderBytecode));

		struct ConstantData
		{
			float specularIntensity = 0.6f;
			float specularPower = 30.0f;
			float padding[2];
		} constData;
		addStaticBind(std::make_unique<PixelConstantBuffer<ConstantData>>(renderer, constData, 2u));

		addStaticBind(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}

	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 norm;
		std::array<char, 4> color;
		char padding;
	};

	const auto tesselation = tesselationDist(range);
	auto model = Cone::makeTesselatedIndependentFaces<Vertex>(tesselation);
	for (auto& v : model.vertices)
	{
		v.color = { (char)10,(char)10,(char)255 };
	}
	for (int i = 0; i < tesselation; i++)
	{
		model.vertices[i * 3].color = { (char)255,(char)10,(char)10 };
	}

	model.transform(DirectX::XMMatrixScaling(1.0f, 1.0f, 0.7f));
	model.setNormalsIndependentFlat();

	addBind(std::make_unique<VertexBuffer>(renderer, model.vertices));
	addIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));

	addBind(std::make_unique<TransformCbuf>(renderer, *this));
}