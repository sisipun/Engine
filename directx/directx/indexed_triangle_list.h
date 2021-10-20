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

	VertexBufferData vertexBufferData;
	std::vector<unsigned short> indices;
};

#endif
