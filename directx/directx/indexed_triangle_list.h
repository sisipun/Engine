#ifndef INDEXED_TRIANGLE_LIST_H
#define INDEXED_TRIANGLE_LIST_H

#include <vector>
#include <DirectXMath.h>

#include "vertex.h"

class IndexedTriangleList
{
public:
	IndexedTriangleList() = default;
	IndexedTriangleList(VertexBufferData bufferData, std::vector<unsigned short> indices) : vertexBufferData(std::move(bufferData)), indices(std::move(indices))
	{
	}

	void transform(DirectX::FXMMATRIX matrix) noexcept
	{
		for (unsigned int i = 0; i < vertexBufferData.size(); i++)
		{
			auto& position = vertexBufferData[i].attr<VertexLayout::ElementType::POSITION3D>();
			DirectX::XMStoreFloat3(
				&position,
				DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&position), matrix)
			);
		}
	}

	void setNormalsIndependentFlat() noexcept
	{
		for (size_t i = 0; i < indices.size(); i += 3)
		{
			auto v0 = vertexBufferData[indices[i]];
			auto v1 = vertexBufferData[indices[i + 1]];
			auto v2 = vertexBufferData[indices[i + 2]];
			const auto p0 = DirectX::XMLoadFloat3(&v0.attr<VertexLayout::ElementType::POSITION3D>());
			const auto p1 = DirectX::XMLoadFloat3(&v1.attr<VertexLayout::ElementType::POSITION3D>());
			const auto p2 = DirectX::XMLoadFloat3(&v2.attr<VertexLayout::ElementType::POSITION3D>());

			const auto n = DirectX::XMVector3Normalize(DirectX::XMVector3Cross((DirectX::operator-(p1, p0)), DirectX::operator-(p2, p0)));

			DirectX::XMStoreFloat3(&v0.attr<VertexLayout::ElementType::NORMAL>(), n);
			DirectX::XMStoreFloat3(&v1.attr<VertexLayout::ElementType::NORMAL>(), n);
			DirectX::XMStoreFloat3(&v2.attr<VertexLayout::ElementType::NORMAL>(), n);
		}
	}

	VertexBufferData vertexBufferData;
	std::vector<unsigned short> indices;
};

#endif
