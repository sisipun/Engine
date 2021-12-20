#ifndef CUBE_H
#define CUBE_H

#include <array>
#include <DirectXMath.h>
#include "indexed_triangle_list.h"
#include "vertex.h"
#include "math.h"

class Cube
{
public:
	static IndexedTriangleList make(VertexLayout layout) noexcept
	{
		constexpr float side = 1.0f / 2.0f;

		VertexBufferData vertexBufferData(std::move(layout), 24);
		vertexBufferData[0].attr<VertexLayout::ElementType::POSITION3D>() = { -side,-side,-side };
		vertexBufferData[1].attr<VertexLayout::ElementType::POSITION3D>() = { side,-side,-side };
		vertexBufferData[2].attr<VertexLayout::ElementType::POSITION3D>() = { -side,side,-side };
		vertexBufferData[3].attr<VertexLayout::ElementType::POSITION3D>() = { side,side,-side };
		vertexBufferData[4].attr<VertexLayout::ElementType::POSITION3D>() = { -side,-side,side };
		vertexBufferData[5].attr<VertexLayout::ElementType::POSITION3D>() = { side,-side,side };
		vertexBufferData[6].attr<VertexLayout::ElementType::POSITION3D>() = { -side,side,side };
		vertexBufferData[7].attr<VertexLayout::ElementType::POSITION3D>() = { side,side,side };
		vertexBufferData[8].attr<VertexLayout::ElementType::POSITION3D>() = { -side,-side,-side };
		vertexBufferData[9].attr<VertexLayout::ElementType::POSITION3D>() = { -side,side,-side };
		vertexBufferData[10].attr<VertexLayout::ElementType::POSITION3D>() = { -side,-side,side };
		vertexBufferData[11].attr<VertexLayout::ElementType::POSITION3D>() = { -side,side,side };
		vertexBufferData[12].attr<VertexLayout::ElementType::POSITION3D>() = { side,-side,-side };
		vertexBufferData[13].attr<VertexLayout::ElementType::POSITION3D>() = { side,side,-side };
		vertexBufferData[14].attr<VertexLayout::ElementType::POSITION3D>() = { side,-side,side };
		vertexBufferData[15].attr<VertexLayout::ElementType::POSITION3D>() = { side,side,side };
		vertexBufferData[16].attr<VertexLayout::ElementType::POSITION3D>() = { -side,-side,-side };
		vertexBufferData[17].attr<VertexLayout::ElementType::POSITION3D>() = { side,-side,-side };
		vertexBufferData[18].attr<VertexLayout::ElementType::POSITION3D>() = { -side,-side,side };
		vertexBufferData[19].attr<VertexLayout::ElementType::POSITION3D>() = { side,-side,side };
		vertexBufferData[20].attr<VertexLayout::ElementType::POSITION3D>() = { -side,side,-side };
		vertexBufferData[21].attr<VertexLayout::ElementType::POSITION3D>() = { side,side,-side };
		vertexBufferData[22].attr<VertexLayout::ElementType::POSITION3D>() = { -side,side,side };
		vertexBufferData[23].attr<VertexLayout::ElementType::POSITION3D>() = { side,side,side };

		return{
			std::move(vertexBufferData),{
				0,2, 1,    2,3,1,
				4,5, 7,    4,7,6,
				8,10, 9,  10,11,9,
				12,13,15, 12,15,14,
				16,17,18, 18,17,19,
				20,23,21, 20,22,23
			}
		};
	}

	static IndexedTriangleList makeTextured() noexcept
	{
		auto list = make(std::move(VertexLayout()
			.append(VertexLayout::ElementType::POSITION3D)
			.append(VertexLayout::ElementType::NORMAL)
			.append(VertexLayout::ElementType::TEXTURE2D)));

		list.vertexBufferData[0].attr<VertexLayout::ElementType::TEXTURE2D>() = { 0.0f,0.0f };
		list.vertexBufferData[1].attr<VertexLayout::ElementType::TEXTURE2D>() = { 1.0f,0.0f };
		list.vertexBufferData[2].attr<VertexLayout::ElementType::TEXTURE2D>() = { 0.0f,1.0f };
		list.vertexBufferData[3].attr<VertexLayout::ElementType::TEXTURE2D>() = { 1.0f,1.0f };
		list.vertexBufferData[4].attr<VertexLayout::ElementType::TEXTURE2D>() = { 0.0f,0.0f };
		list.vertexBufferData[5].attr<VertexLayout::ElementType::TEXTURE2D>() = { 1.0f,0.0f };
		list.vertexBufferData[6].attr<VertexLayout::ElementType::TEXTURE2D>() = { 0.0f,1.0f };
		list.vertexBufferData[7].attr<VertexLayout::ElementType::TEXTURE2D>() = { 1.0f,1.0f };
		list.vertexBufferData[8].attr<VertexLayout::ElementType::TEXTURE2D>() = { 0.0f,0.0f };
		list.vertexBufferData[9].attr<VertexLayout::ElementType::TEXTURE2D>() = { 1.0f,0.0f };
		list.vertexBufferData[10].attr<VertexLayout::ElementType::TEXTURE2D>() = { 0.0f,1.0f };
		list.vertexBufferData[11].attr<VertexLayout::ElementType::TEXTURE2D>() = { 1.0f,1.0f };
		list.vertexBufferData[12].attr<VertexLayout::ElementType::TEXTURE2D>() = { 0.0f,0.0f };
		list.vertexBufferData[13].attr<VertexLayout::ElementType::TEXTURE2D>() = { 1.0f,0.0f };
		list.vertexBufferData[14].attr<VertexLayout::ElementType::TEXTURE2D>() = { 0.0f,1.0f };
		list.vertexBufferData[15].attr<VertexLayout::ElementType::TEXTURE2D>() = { 1.0f,1.0f };
		list.vertexBufferData[16].attr<VertexLayout::ElementType::TEXTURE2D>() = { 0.0f,0.0f };
		list.vertexBufferData[17].attr<VertexLayout::ElementType::TEXTURE2D>() = { 1.0f,0.0f };
		list.vertexBufferData[18].attr<VertexLayout::ElementType::TEXTURE2D>() = { 0.0f,1.0f };
		list.vertexBufferData[19].attr<VertexLayout::ElementType::TEXTURE2D>() = { 1.0f,1.0f };
		list.vertexBufferData[20].attr<VertexLayout::ElementType::TEXTURE2D>() = { 0.0f,0.0f };
		list.vertexBufferData[21].attr<VertexLayout::ElementType::TEXTURE2D>() = { 1.0f,0.0f };
		list.vertexBufferData[22].attr<VertexLayout::ElementType::TEXTURE2D>() = { 0.0f,1.0f };
		list.vertexBufferData[23].attr<VertexLayout::ElementType::TEXTURE2D>() = { 1.0f,1.0f };

		return list;
	}
};

#endif
