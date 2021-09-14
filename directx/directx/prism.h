#ifndef PRISM_H
#define PRISM_H

#include "indexed_triangle_list.h"
#include "math.h"

class Prism
{
public:
	template<typename V>
	static IndexedTriangleList<V> make(int longDiv)
	{
		const auto base = DirectX::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
		const auto offset = DirectX::XMVectorSet(0.0f, 0.0f, 2.0f, 0.0f);
		const float longitudeAngle = 2.0f * PI / longDiv;

		std::vector<V> vertices;
		vertices.emplace_back();
		vertices.back().pos = { 0.0f,0.0f,-1.0f };
		const auto centerNearIdex = (unsigned short)(vertices.size() - 1);

		vertices.emplace_back();
		vertices.back().pos = { 0.0f,0.0f,1.0f };
		const auto centerFarIndex = (unsigned short)(vertices.size() - 1);

		for (int i = 0; i < longDiv; i++)
		{
			vertices.emplace_back();
			auto positionNear = DirectX::XMVector3Transform(
				base,
				dx::XMMatrixRotationZ(longitudeAngle * i)
			);
			DirectX::XMStoreFloat3(&vertices.back().pos, positionNear);

			vertices.emplace_back();
			auto positionFar = dx::XMVector3Transform(
				base,
				DirectX::XMMatrixRotationZ(longitudeAngle * i)
			);
			positionFar = DirectX::XMVectorAdd(positionFar, offset);
			DirectX::XMStoreFloat3(&vertices.back().pos, positionFar);
		}

		std::vector<unsigned short> indices;
		for (unsigned short i = 0; i < longDiv; i++)
		{
			const auto index = i * 2;
			const auto mod = longDiv * 2;
			indices.push_back(index + 2);
			indices.push_back((index + 2) % mod + 2);
			indices.push_back(index + 1 + 2);
			indices.push_back((index + 2) % mod + 2);
			indices.push_back((index + 3) % mod + 2);
			indices.push_back(index + 1 + 2);
		}

		for (unsigned short i = 0; i < longDiv; i++)
		{
			const auto index = i * 2;
			const auto mod = longDiv * 2;
			indices.push_back(index + 2);
			indices.push_back(centerNearIndex);
			indices.push_back((index + 2) % mod + 2);
			indices.push_back(centerFarIndex);
			indices.push_back(index + 1 + 2);
			indices.push_back((index + 3) % mod + 2);
		}

		return { std::move(vertices), std::move(indices) };
	}

	template<typename V>
	static IndexedTriangleList<V> make()
	{
		return make(24);
	}
};

#endif 
