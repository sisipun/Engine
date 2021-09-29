#ifndef PRISM_H
#define PRISM_H

#include "indexed_triangle_list.h"
#include "math.h"

class Prism
{
public:
	template<typename V>
	static IndexedTriangleList<V> make(int longDiv) noexcept
	{
		const auto base = DirectX::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
		const auto offset = DirectX::XMVectorSet(0.0f, 0.0f, 2.0f, 0.0f);
		const float longitudeAngle = 2.0f * PI / longDiv;

		std::vector<V> vertices;
		vertices.emplace_back();
		vertices.back().pos = { 0.0f,0.0f,-1.0f };
		const auto centerNearIndex = (unsigned short)(vertices.size() - 1);

		vertices.emplace_back();
		vertices.back().pos = { 0.0f,0.0f,1.0f };
		const auto centerFarIndex = (unsigned short)(vertices.size() - 1);

		for (int i = 0; i < longDiv; i++)
		{
			vertices.emplace_back();
			auto positionNear = DirectX::XMVector3Transform(
				base,
				DirectX::XMMatrixRotationZ(longitudeAngle * i)
			);
			DirectX::XMStoreFloat3(&vertices.back().pos, positionNear);

			vertices.emplace_back();
			auto positionFar = DirectX::XMVector3Transform(
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
	static IndexedTriangleList<V> makeTesselatedIndependentCapNormals(int longDiv) noexcept
	{
		assert(longDiv >= 3);
		const auto base = DirectX::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
		const auto offset = DirectX::XMVectorSet(0.0f, 0.0f, 2.0f, 0.0f);
		const float longitudeAngle = 2.0f * PI / longDiv;
		std::vector<V> vertices;

		const auto centerNear = (unsigned short)vertices.size();
		vertices.emplace_back();
		vertices.back().pos = { 0.0f,0.0f,-1.0f };
		vertices.back().norm = { 0.0f,0.0f,-1.0f };

		const auto baseNear = (unsigned short)vertices.size();
		for (int i = 0; i < longDiv; i++)
		{
			vertices.emplace_back();
			auto v = DirectX::XMVector3Transform(
				base,
				DirectX::XMMatrixRotationZ(longitudeAngle * i)
			);
			DirectX::XMStoreFloat3(&vertices.back().pos, v);
			vertices.back().norm = { 0.0f,0.0f,-1.0f };
		}

		const auto centerFar = (unsigned short)vertices.size();
		vertices.emplace_back();
		vertices.back().pos = { 0.0f,0.0f,1.0f };
		vertices.back().norm = { 0.0f,0.0f,1.0f };

		const auto baseFar = (unsigned short)vertices.size();
		for (int i = 0; i < longDiv; i++)
		{
			vertices.emplace_back();
			auto v = DirectX::XMVector3Transform(
				base,
				DirectX::XMMatrixRotationZ(longitudeAngle * i)
			);
			v = DirectX::XMVectorAdd(v, offset);
			DirectX::XMStoreFloat3(&vertices.back().pos, v);
			vertices.back().norm = { 0.0f, 0.0f, 1.0f };
		}

		const auto fusilage = (unsigned short)vertices.size();
		for (int i = 0; i < longDiv; i++)
		{
			vertices.emplace_back();
			auto v = DirectX::XMVector3Transform(
				base,
				DirectX::XMMatrixRotationZ(longitudeAngle * i)
			);
			DirectX::XMStoreFloat3(&vertices.back().pos, v);
			vertices.back().norm = { vertices.back().pos.x,vertices.back().pos.y,0.0f };

			vertices.emplace_back();
			v = DirectX::XMVector3Transform(
				base,
				DirectX::XMMatrixRotationZ(longitudeAngle * i)
			);
			v = DirectX::XMVectorAdd(v, offset);
			DirectX::XMStoreFloat3(&vertices.back().pos, v);
			vertices.back().norm = { vertices.back().pos.x, vertices.back().pos.y, 0.0f };
		}
		std::vector<unsigned short> indices;

		for (unsigned short i = 0; i < longDiv; i++)
		{
			const auto mod = longDiv;

			indices.push_back(i + baseNear);
			indices.push_back(centerNear);
			indices.push_back((i + 1) % mod + baseNear);
		}

		for (unsigned short i = 0; i < longDiv; i++)
		{
			const auto mod = longDiv;
			indices.push_back(centerFar);
			indices.push_back(i + baseFar);
			indices.push_back((i + 1) % mod + baseFar);
		}

		for (unsigned short i = 0; i < longDiv; i++)
		{
			const auto j = i * 2;
			const auto mod = longDiv * 2;
			indices.push_back(j + fusilage);
			indices.push_back((j + 2) % mod + fusilage);
			indices.push_back(j + 1 + fusilage);
			indices.push_back((j + 2) % mod + fusilage);
			indices.push_back((j + 3) % mod + fusilage);
			indices.push_back(j + 1 + fusilage);
		}
		return { std::move(vertices), std::move(indices) };
	}

	template<typename V>
	static IndexedTriangleList<V> make() noexcept
	{
		return make(24);
	}
};

#endif 
