#include "box.h"
#include "constant_buffer.h"
#include "index_buffer.h"
#include "input_layout.h"
#include "pixel_shader.h"
#include "topology.h"
#include "transform_cbuf.h"
#include "vertex_buffer.h"
#include "vertex_shader.h"
#include "cube.h"


Box::Box(
	const Renderer& renderer,
	std::mt19937& range,
	std::uniform_real_distribution<float>& radiusDist,
	std::uniform_real_distribution<float>& anglesDist,
	std::uniform_real_distribution<float>& deltaAnglesDist,
	std::uniform_real_distribution<float>& deltaOrientationDist,
	std::uniform_real_distribution<float>& sizeDist,
	DirectX::XMFLOAT3 materialColor
) : DefaultDrawableBase(range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist)
{
	if (!isStaticInitialized())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 norm;
		};

		auto model = Cube::makeIndependent<Vertex>();
		model.setNormalsIndependentFlat();

		addStaticBind(std::make_unique<VertexBuffer>(renderer, model.vertices));

		auto vertexShader = std::make_unique<VertexShader>(renderer, L"phong_vertex.cso");
		auto vertexShaderBytecode = vertexShader->getBytecode();
		addStaticBind(std::move(vertexShader));

		addStaticBind(std::make_unique<PixelShader>(renderer, L"phong_pixel.cso"));

		addStaticIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		addStaticBind(std::make_unique<InputLayout>(renderer, inputElementDesc, vertexShaderBytecode));

		addStaticBind(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		setIndexFromStatic();
	}

	addBind(std::make_unique<TransformCbuf>(renderer, *this));

	struct ConstantData
	{
		alignas(16) DirectX::XMFLOAT3 materialColor;
		float specularIntensity = 0.6f;
		float specularPower = 30.0f;
		float padding[2];
	} constData;
	constData.materialColor = materialColor;
	addBind(std::make_unique<PixelConstantBuffer<ConstantData>>(renderer, constData, 2));

	DirectX::XMStoreFloat3x3(
		&model,
		DirectX::XMMatrixScaling(1.0f, 1.0f, sizeDist(range))
	);
}

DirectX::XMMATRIX Box::getTransform() const noexcept
{
	return DirectX::XMLoadFloat3x3(&model) * DefaultDrawableBase::getTransform();
}