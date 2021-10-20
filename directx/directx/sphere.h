#ifndef SPHERE_H
#define SPHERE_H

#include <optional>

#include "indexed_triangle_list.h"
#include "math.h"
#include "vertex.h"

class Sphere
{
public:
	static IndexedTriangleList make(VertexLayout layout, int latDiv, int longDiv)
	{
		constexpr float radius = 1.0f;
		const auto base = DirectX::XMVectorSet(0.0f, 0.0f, radius, 0.0f);
		const float lattitudeAngle = PI / latDiv;
		const float longitudeAngle = 2.0f * PI / longDiv;

		VertexBufferData bufferData{ std::move(layout) };
		for (int latitude = 1; latitude < latDiv; latitude++)
		{
			const auto latBase = DirectX::XMVector3Transform(
				base,
				DirectX::XMMatrixRotationX(lattitudeAngle * latitude)
			);
			for (int longitude = 0; longitude < longDiv; longitude++)
			{
				DirectX::XMFLOAT3 calculatedPos;
				auto position = DirectX::XMVector3Transform(
					latBase,
					DirectX::XMMatrixRotationZ(longitudeAngle * longitude)
				);
				DirectX::XMStoreFloat3(&calculatedPos, position);
				bufferData.emplaceBack(calculatedPos);
			}
		}

		const auto northPoleIndex = (unsigned short) bufferData.size();
		DirectX::XMFLOAT3 northPos;
		DirectX::XMStoreFloat3(&northPos, base);
		bufferData.emplaceBack(northPos);

		const auto southPoleIndex = (unsigned short)bufferData.size();
		DirectX::XMFLOAT3 southPos;
		DirectX::XMStoreFloat3(&southPos, base);
		bufferData.emplaceBack(southPos);

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

		return { std::move(bufferData), std::move(indices) };
	}

	static IndexedTriangleList make(std::optional<VertexLayout> layout = std::nullopt) noexcept
	{
		if (!layout)
		{
			layout = VertexLayout().append(VertexLayout::ElementType::POSITION3D);
		}
		return make(std::move(*layout), 12, 24);
	}
};

#endif 
