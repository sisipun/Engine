#ifndef INDEXED_TRIANGLE_LIST
#define INDEXED_TRIANGLE_LIST

#include <vector>
#include <DirectXMath.h>

template<typename T>
class IndexedTriangleList
{
public:
	IndexedTriangleList() = default;
	IndexedTriangleList(std::vector<T> vertices, std::vector<unsigned short> indices) : vertices(std::move(vertices)), indices(std::move(indices))
	{
	}

	void transform(DirectX::FXMMATRIX matrix)
	{
		for (auto& vertex : vertices)
		{
			const DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&vertex.pos);
			DirectX::XMStoreFloat3(
				&vertex.pos,
				DirectX::XMVector3Transform(position, matrix)
			);
		}
	}

	void setNormalsIndependentFlat() noexcept
	{
		using namespace DirectX;
		for (size_t i = 0; i < indices.size(); i += 3)
		{
			auto& v0 = vertices[indices[i]];
			auto& v1 = vertices[indices[i + 1]];
			auto& v2 = vertices[indices[i + 2]];
			const auto p0 = DirectX::XMLoadFloat3(&v0.pos);
			const auto p1 = DirectX::XMLoadFloat3(&v1.pos);
			const auto p2 = DirectX::XMLoadFloat3(&v2.pos);

			const auto n = DirectX::XMVector3Normalize(DirectX::XMVector3Cross((p1 - p0), (p2 - p0)));

			DirectX::XMStoreFloat3(&v0.norm, n);
			DirectX::XMStoreFloat3(&v1.norm, n);
			DirectX::XMStoreFloat3(&v2.norm, n);
		}
	}

	std::vector<T> vertices;
	std::vector<unsigned short> indices;
};

#endif
