#ifndef PLANE_H
#define PLANE_H

#include <array>

#include "indexed_triangle_list.h"
#include "math.h"

class Plane
{
public:
	template<typename V>
	static IndexedTriangleList<V> make(int divisionsX, int divisionsY)
	{
		constexpr float width = 2.0f;
		constexpr float height = 2.0f;
		const int nVerticesX = divisionsX + 1;
		const int nVerticesY = divisionsY + 1;
		std::vector<V> vertices(nVerticesX * nVerticesY);

		const float sideX = width / 2.0f;
		const float sideY = height / 2.0f;
		const float divisionSizeX = width / float(divisionsX);
		const float divisionSizeY = height / float(divisionsY);
		const auto bottomLeft = DirectX::XMVectorSet(-sideX, -sideY, 0.0f, 0.0f);

		for (int y = 0, i = 0; y < nVerticesY; y++)
		{
			const float posY = float(y) * divisionSizeY;
			for (int x = 0; x < nVerticesX; x++, i++)
			{
				const auto position = DirectX::XMVectorAdd(
					bottomLeft,
					DirectX::XMVectorSet(float(x) * divisionSizeX, posY, 0.0f, 0.0f)
				);
				DirectX::XMStoreFloat3(&vertices[i].pos, position);
			}
		}

		std::vector<unsigned short> indices;
		indices.reserve(sq(divisionsX * divisionsY) * 6);
		{
			const auto vertexToIndex = [nVerticesX](size_t x, size_t y)
			{
				return (unsigned short)(y * nVerticesX + x);
			};
			for (size_t y = 0; y < divisionsY; y++)
			{
				for (size_t x = 0; x < divisionsX; x++)
				{
					const std::array<unsigned short, 4> indexArray = { vertexToIndex(x,y),vertexToIndex(x + 1,y),vertexToIndex(x,y + 1),vertexToIndex(x + 1,y + 1) };
					indices.push_back(indexArray[0]);
					indices.push_back(indexArray[2]);
					indices.push_back(indexArray[1]);
					indices.push_back(indexArray[1]);
					indices.push_back(indexArray[2]);
					indices.push_back(indexArray[3]);
				}
			}
		}

		return{ std::move(vertices),std::move(indices) };
	}

	template<typename V>
	static IndexedTriangleList<V> make()
	{
		return make<V>(1, 1);
	}
};

#endif