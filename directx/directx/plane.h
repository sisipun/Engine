#ifndef PLANE_H
#define PLANE_H

#include <array>

#include <DirectXMath.h>

#include "vertex.h"
#include "indexed_triangle_list.h"
#include "math.h"

class Plane
{
public:
	static IndexedTriangleList make(VertexLayout layout, int divisionsX, int divisionsY)
	{
		constexpr float width = 1.0f;
		constexpr float height = 1.0f;
		const int nVerticesX = divisionsX + 1;
		const int nVerticesY = divisionsY + 1;
		VertexBufferData vertexData(std::move(layout));

		const float sideS = width / 2.0f;
		const float sideY = height / 2.0f;
		const float divisionSizeX = width / float(divisionsX);
		const float divisionSizeY = height / float(divisionsY);
		const float divisionSizeXTexCoord = 1.0f / float(divisionsX);
		const float divisionSizeYTexCoord = 1.0f / float(divisionsY);

		for (int y = 0, i = 0; y < nVerticesY; y++)
		{
			const float yPos = float(y) * divisionSizeY - 1.0f;
			const float yPosTexCoord = 1.0f - float(y) * divisionSizeYTexCoord;
			for (int x = 0; x < nVerticesX; x++, i++)
			{
				const float xPos = float(x) * divisionSizeX - 1.0f;
				const float xPosTexCoord = float(x) * divisionSizeXTexCoord;
				vertexData.emplaceBack(
					DirectX::XMFLOAT3{ xPos,yPos,0.0f },
					DirectX::XMFLOAT3{ 0.0f,0.0f,-1.0f },
					DirectX::XMFLOAT2{ xPosTexCoord,yPosTexCoord }
				);
			}
		}

		std::vector<unsigned short> indices;
		indices.reserve(sq(divisionsX * divisionsY) * 6);
		const auto divistionsToIndex = [nVerticesX](size_t x, size_t y)
		{
			return (unsigned short)(y * nVerticesX + x);
		};
		for (size_t y = 0; y < divisionsY; y++)
		{
			for (size_t x = 0; x < divisionsX; x++)
			{
				const std::array<unsigned short, 4> indexArray =
				{ 
					divistionsToIndex(x,y),
					divistionsToIndex(x + 1,y),
					divistionsToIndex(x,y + 1),
					divistionsToIndex(x + 1,y + 1) 
				};
				indices.push_back(indexArray[0]);
				indices.push_back(indexArray[2]);
				indices.push_back(indexArray[1]);
				indices.push_back(indexArray[1]);
				indices.push_back(indexArray[2]);
				indices.push_back(indexArray[3]);
			}
		}

		return{ std::move(vertexData),std::move(indices) };
	}

	static IndexedTriangleList make()
	{
		VertexLayout layout;
		layout.append(VertexLayout::POSITION3D);
		layout.append(VertexLayout::NORMAL);
		layout.append(VertexLayout::TEXTURE2D);

		return make(std::move(layout), 1, 1);
	}
};

#endif