#ifndef SPHERE_H
#define SPHERE_H

#include "indexed_triangle_list.h"
#include "math.h"

class Sphere
{
public:
	template<typename V>
	static IndexedTriangleList<V> make(int latDiv, int longDiv) noexcept
	{
		constexpr float radius = 1.0f;
		const auto base = DirectX::XMVectorSet(0.0f, 0.0f, radius, 0.0f);
		const float lattitudeAngle = PI / latDiv;
		const float longitudeAngle = 2.0f * PI / longDiv;

		std::vector<V> vertices;
		for (int latitude = 1; latitude < latDiv; latitude++)
		{
			const auto latBase = DirectX::XMVector3Transform(
				base,
				DirectX::XMMatrixRotationX(lattitudeAngle * latitude)
			);
			for (int longitude = 0; longitude < longDiv; longitude++)
			{
				vertices.emplace_back();
				auto position = DirectX::XMVector3Transform(
					latBase,
					DirectX::XMMatrixRotationZ(longitudeAngle * longitude)
				);
				DirectX::XMStoreFloat3(&vertices.back().pos, position);
			}
		}

		const auto northPoleIndex = (unsigned short) vertices.size();
		vertices.emplace_back();
		DirectX::XMStoreFloat3(&vertices.back().pos, base);

		const auto southPoleIndex = (unsigned short) vertices.size();
		vertices.emplace_back();
		DirectX::XMStoreFloat3(&vertices.back().pos, DirectX::XMVectorNegate(base));

		const auto calculateIndex = [longDiv](unsigned short latitude, unsigned short longitude)
		{
			return latitude * longDiv + longitude;
		};
		std::vector<unsigned short> indices;
		for (unsigned short latitude = 0; latitude < latDiv - 2; latitude++)
		{
			for (unsigned short longitude = 0; longitude < longDiv - 1; longitude++)
			{
				indices.push_back(calculateIndex(latitude, longitude));
				indices.push_back(calculateIndex(latitude + 1, longitude));
				indices.push_back(calculateIndex(latitude, longitude + 1));
				indices.push_back(calculateIndex(latitude, longitude + 1));
				indices.push_back(calculateIndex(latitude + 1, longitude));
				indices.push_back(calculateIndex(latitude + 1, longitude + 1));
			}

			indices.push_back(calculateIndex(latitude, longDiv - 1));
			indices.push_back(calculateIndex(latitude + 1, longDiv - 1));
			indices.push_back(calculateIndex(latitude, 0));
			indices.push_back(calculateIndex(latitude, 0));
			indices.push_back(calculateIndex(latitude + 1, longDiv - 1));
			indices.push_back(calculateIndex(latitude + 1, 0));
		}

		for (unsigned short longitude = 0; longitude < longDiv - 1; longitude++)
		{
			indices.push_back(northPoleIndex);
			indices.push_back(calculateIndex(0, longitude));
			indices.push_back(calculateIndex(0, longitude + 1));
			indices.push_back(calculateIndex(latDiv - 2, longitude + 1));
			indices.push_back(calculateIndex(latDiv - 2, longitude));
			indices.push_back(southPoleIndex);
		}

		indices.push_back(northPoleIndex);
		indices.push_back(calculateIndex(0, longDiv - 1));
		indices.push_back(calculateIndex(0, 0));

		indices.push_back(calculateIndex(latDiv - 2, 0));
		indices.push_back(calculateIndex(latDiv - 2, longDiv - 1));
		indices.push_back(southPoleIndex);

		return { std::move(vertices), std::move(indices) };
	}

	template<typename V>
	static IndexedTriangleList<V> make() noexcept
	{
		return make<V>(12, 24);
	}
};

#endif 
