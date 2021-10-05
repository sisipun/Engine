#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "suzanne.h"
#include "constant_buffer.h"
#include "index_buffer.h"
#include "input_layout.h"
#include "pixel_shader.h"
#include "topology.h"
#include "transform_cbuf.h"
#include "vertex_buffer.h"
#include "vertex_shader.h"
#include "vertex_layout.h"


Suzanne::Suzanne(
	const Renderer& renderer,
	std::mt19937& range,
	std::uniform_real_distribution<float>& radiusDist,
	std::uniform_real_distribution<float>& anglesDist,
	std::uniform_real_distribution<float>& deltaAnglesDist,
	std::uniform_real_distribution<float>& deltaOrientationDist,
	DirectX::XMFLOAT3 materialColor,
	float scale
) : DefaultDrawableBase(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist)
{
	if (!isStaticInitialized())
	{
		VertexBufferData vertexBufferData(std::move(VertexLayout().append(VertexLayout::POSITION3D).append(VertexLayout::NORMAL)));
		Assimp::Importer importer;
		const auto model = importer.ReadFile("models\\suzanne.obj", aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
		const auto mesh = model->mMeshes[0];

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			vertexBufferData.emplaceBack(
				DirectX::XMFLOAT3{ mesh->mVertices[i].x * scale, mesh->mVertices[i].y * scale, mesh->mVertices[i].z * scale },
				*reinterpret_cast<DirectX::XMFLOAT3*>(&mesh->mNormals[i])
			);
		}

		std::vector<unsigned short> indices;
		indices.reserve(mesh->mNumFaces * 3);
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			const auto& face = mesh->mFaces[i];
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}

		addStaticBind(std::make_unique<VertexBuffer>(renderer, vertexBufferData));

		auto vertexShader = std::make_unique<VertexShader>(renderer, L"phong_vertex.cso");
		auto vertexShaderBytecode = vertexShader->getBytecode();
		addStaticBind(std::move(vertexShader));

		addStaticBind(std::make_unique<PixelShader>(renderer, L"phong_pixel.cso"));

		addStaticIndexBuffer(std::make_unique<IndexBuffer>(renderer, indices));

		addStaticBind(std::make_unique<InputLayout>(renderer, vertexBufferData.getLayout().getDescLayout(), vertexShaderBytecode));

		addStaticBind(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		struct ConstantData
		{
			DirectX::XMFLOAT3 materialColor;
			float specularIntensity = 0.6f;
			float specularPower = 30.0f;
			float padding[3];
		} constData;
		constData.materialColor = materialColor;
		addStaticBind(std::make_unique<PixelConstantBuffer<ConstantData>>(renderer, constData, 2));
	}
	else
	{
		setIndexFromStatic();
	}

	addBind(std::make_unique<TransformCbuf>(renderer, *this));
}