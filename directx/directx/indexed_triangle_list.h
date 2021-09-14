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

	std::vector<T> vertices;
	std::vector<unsigned short> indices;
};

#endif
