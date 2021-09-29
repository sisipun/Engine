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
) : DefaultDrawableBase(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist)
{
	if (!isStaticInitialized())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 norm;
			DirectX::XMFLOAT2 texCoord;
		};
		auto model = Cube::makeIndependentTextured<Vertex>();
		model.setNormalsIndependentFlat();

		addStaticBind(std::make_unique<Texture>(renderer, Surface::fromFile("Images\\kappa50.png")));
		addStaticBind(std::make_unique<VertexBuffer>(renderer, model.vertices));
		addStaticBind(std::make_unique<Sampler>(renderer));

		auto vertexShader = std::make_unique<VertexShader>(renderer, L"textured_phong_vertex.cso");
		auto vertexShaderBytecode = vertexShader->getBytecode();
		addStaticBind(std::move(vertexShader));
		addStaticBind(std::make_unique<PixelShader>(renderer, L"textured_phong_pixel.cso"));

		addStaticIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> inputDescription =
		{
			{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		addStaticBind(std::make_unique<InputLayout>(renderer, inputDescription, vertexShaderBytecode));

		struct ConstantData
		{
			float specularIntensity = 0.6f;
			float specularPower = 30.0f;
			float padding[2];
		} constData;
		addStaticBind(std::make_unique<PixelConstantBuffer<ConstantData>>(renderer, constData, 2u));

		addStaticBind(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		setIndexFromStatic();
	}

	addBind(std::make_unique<TransformCbuf>(renderer, *this));
}