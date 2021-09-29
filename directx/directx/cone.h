#ifndef CONE_H
#define CONE_H

#include "indexed_triangle_list.h"
#include "math.h"

class Cone
{
public:
	template<typename V>
	static IndexedTriangleList<V> make(int longDiv) noexcept
	{
		const auto base = DirectX::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
		const float longitudeAngle = 2.0f * PI / longDiv;

		std::vector<V> vertices;
		for (int i = 0; i < longDiv; i++)
		{
			vertices.emplace_back();
			auto position = DirectX::XMVector3Transform(
				base,
				DirectX::XMMatrixRotationZ(longitudeAngle * i)
			);
			DirectX::XMStoreFloat3(&vertices.back().pos, position);
		}

		vertices.emplace_back();
		vertices.back().pos = { 0.0f, 0.0f, -1.0f };
		const auto centerIndex = (unsigned short)(vertices.size() - 1);
		
		vertices.emplace_back();
		vertices.back().pos = { 0.0f, 0.0f, 1.0f };
		const auto tipIndex = (unsigned short)(vertices.size() - 1);

		std::vector<unsigned short> indices;
		for (unsigned short i = 0; i < longDiv; i++)
		{
			indices.push_back(centerIndex);
			indices.push_back((i + 1) % longDiv);
			indices.push_back(i);
		}

		for (unsigned short i = 0; i < longDiv; i++)
		{
			indices.push_back(i);
			indices.push_back((i + 1) % longDiv);
			indices.push_back(tipIndex);
		}

		return { std::move(vertices), std::move(indices) };
	}

	template<typename V>
	static IndexedTriangleList<V> makeTesselatedIndependentFaces(int longDiv) noexcept
	{
		const auto base = DirectX::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
		const float longitudeAngle = 2.0f * PI / longDiv;

		std::vector<V> vertices;

		const auto cone = (unsigned short) vertices.size();
		for (int i = 0; i < longDiv; i++)
		{
			const float thetas[] = {
				longitudeAngle * i,
				longitudeAngle * (((i + 1) == longDiv) ? 0 : (i + 1))
			};
			vertices.emplace_back();
			vertices.back().pos = { 0.0f,0.0f,1.0f };
			for (auto theta : thetas)
			{
				vertices.emplace_back();
				const auto v = DirectX::XMVector3Transform(
					base,
					DirectX::XMMatrixRotationZ(theta)
				);
				DirectX::XMStoreFloat3(&vertices.back().pos, v);
			}
		}

		const auto baseCenter = (unsigned short) vertices.size();
		vertices.emplace_back();
		vertices.back().pos = { 0.0f,0.0f,-1.0f };
		const auto baseEdge = (unsigned short) vertices.size();
		for (int i = 0; i < longDiv; i++)
		{
			vertices.emplace_back();
			auto v = DirectX::XMVector3Transform(
				base,
				DirectX::XMMatrixRotationZ(longitudeAngle * i)
			);
			DirectX::XMStoreFloat3(&vertices.back().pos, v);
		}

		std::vector<unsigned short> indices;

		for (unsigned short i = 0; i < longDiv * 3; i++)
		{
			indices.push_back(i + cone);
		}

		for (unsigned short i = 0; i < longDiv; i++)
		{
			indices.push_back(baseCenter);
			indices.push_back((i + 1) % longDiv + baseEdge);
			indices.push_back(i + baseEdge);
		}

		return { std::move(vertices),std::move(indices) };
	}

	template<typename V>
	static IndexedTriangleList<V> make() noexcept
	{
		return make<V>(24);
	}
};

#endif