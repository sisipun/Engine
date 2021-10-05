#ifndef VERTEX_LAYOUT_H
#define VERTEX_LAYOUT_H

#include <vector>
#include <type_traits>
#include <DirectXMath.h>

struct RGBAColor
{
	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class VertexLayout
{
public:
	enum ElementType
	{
		POSITION2D,
		POSITION3D,
		TEXTURE2D,
		NORMAL,
		FLOAT3_COLOR,
		FLOAT4_COLOR,
		RGBA_COLOR
	};

	template<ElementType T>
	struct Map;

	template<>
	struct Map<POSITION2D>
	{
		using SysType = DirectX::XMFLOAT2;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32_FLOAT;
		static constexpr const char* semantic = "Position";
	};

	template<>
	struct Map<POSITION3D>
	{
		using SysType = DirectX::XMFLOAT3;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
		static constexpr const char* semantic = "Position";
	};

	template<>
	struct Map<TEXTURE2D>
	{
		using SysType = DirectX::XMFLOAT2;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32_FLOAT;
		static constexpr const char* semantic = "TexCoord";
	};

	template<>
	struct Map<NORMAL>
	{
		using SysType = DirectX::XMFLOAT3;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
		static constexpr const char* semantic = "Normal";
	};

	template<>
	struct Map<FLOAT3_COLOR>
	{
		using SysType = DirectX::XMFLOAT3;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
		static constexpr const char* semantic = "Color";
	};

	template<>
	struct Map<FLOAT4_COLOR>
	{
		using SysType = DirectX::XMFLOAT4;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
		static constexpr const char* semantic = "Color";
	};

	template<>
	struct Map<RGBA_COLOR>
	{
		using SysType = RGBAColor;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		static constexpr const char* semantic = "Color";
	};

	class Element
	{
	public:
		Element(ElementType type, size_t offset) : type(type), offset(offset)
		{
		}

		size_t getOffsetAfter() const noexcept
		{
			return offset + size();
		}

		size_t getOffset() const noexcept
		{
			return offset;
		}

		size_t size() const noexcept
		{
			return sizeOf(type);
		}

		static constexpr size_t sizeOf(ElementType type) noexcept
		{
			switch (type)
			{
			case POSITION2D:
				return sizeof(Map<POSITION2D>::SysType);
			case POSITION3D:
				return sizeof(Map<POSITION3D>::SysType);
			case TEXTURE2D:
				return sizeof(Map<TEXTURE2D>::SysType);
			case NORMAL:
				return sizeof(Map<NORMAL>::SysType);
			case FLOAT3_COLOR:
				return sizeof(Map<FLOAT3_COLOR>::SysType);
			case FLOAT4_COLOR:
				return sizeof(Map<FLOAT4_COLOR>::SysType);
			case RGBA_COLOR:
				return sizeof(Map<RGBA_COLOR>::SysType);
			}

			return 0;
		}

		ElementType getType() const noexcept
		{
			return type;
		}

		D3D11_INPUT_ELEMENT_DESC getDesc() const noexcept
		{
			switch (type)
			{
			case POSITION2D:
				return generateDesc<POSITION2D>(getOffset());
			case POSITION3D:
				return generateDesc<POSITION3D>(getOffset());
			case TEXTURE2D:
				return generateDesc<TEXTURE2D>(getOffset());
			case NORMAL:
				return generateDesc<NORMAL>(getOffset());
			case FLOAT3_COLOR:
				return generateDesc<FLOAT3_COLOR>(getOffset());
			case FLOAT4_COLOR:
				return generateDesc<FLOAT4_COLOR>(getOffset());
			case RGBA_COLOR:
				return generateDesc<RGBA_COLOR>(getOffset());
			}

			return { "INVALID", 0, DXGI_FORMAT_UNKNOWN, 0, (UINT)offset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		}

	private:
		template<ElementType T>
		static constexpr D3D11_INPUT_ELEMENT_DESC generateDesc(size_t offset) noexcept
		{
			return { Map<T>::semantic, 0, Map<T>::dxgiFormat, 0, (UINT)offset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		}

		ElementType type;
		size_t offset;
	};

	template<ElementType T>
	const Element& resolve() const noexcept
	{
		for (auto& element : elements)
		{
			if (element.getType() == T)
			{
				return element;
			}
		}

		return elements.front();
	}

	const Element& resolveByIndex(size_t i) const noexcept
	{
		return elements[i];
	}

	VertexLayout& append(ElementType type) noexcept
	{
		elements.emplace_back(type, size());
		return *this;
	}

	size_t size() const noexcept
	{
		return elements.empty() ? 0 : elements.back().getOffsetAfter();
	}

	size_t getElementsCount() const noexcept
	{
		return elements.size();
	}

	std::vector<D3D11_INPUT_ELEMENT_DESC> getDescLayout() const noexcept
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> descriptions;
		descriptions.reserve(getElementsCount());
		for (const auto& element : elements)
		{
			descriptions.push_back(element.getDesc());
		}
		return descriptions;
	}

private:
	std::vector<Element> elements;
};

class Vertex
{
	friend class VertexBufferData;
public:
	template<VertexLayout::ElementType T>
	auto& attr() noexcept
	{
		auto attribute = data + layout.resolve<T>().getOffset();
		return *reinterpret_cast<typename VertexLayout::Map<T>::SysType*>(attribute);
	}

	template<typename T>
	void setAttributeByIndex(size_t index, T&& value) noexcept
	{
		const auto& element = layout.resolveByIndex(index);
		auto attribute = data + element.getOffset();
		switch (element.getType())
		{
		case VertexLayout::POSITION2D:
			setAttribute<VertexLayout::POSITION2D>(attribute, std::forward<T>(value));
			break;
		case VertexLayout::POSITION3D:
			setAttribute<VertexLayout::POSITION3D>(attribute, std::forward<T>(value));
			break;
		case VertexLayout::TEXTURE2D:
			setAttribute<VertexLayout::TEXTURE2D>(attribute, std::forward<T>(value));
			break;
		case VertexLayout::NORMAL:
			setAttribute<VertexLayout::NORMAL>(attribute, std::forward<T>(value));
			break;
		case VertexLayout::FLOAT3_COLOR:
			setAttribute<VertexLayout::FLOAT3_COLOR>(attribute, std::forward<T>(value));
			break;
		case VertexLayout::FLOAT4_COLOR:
			setAttribute<VertexLayout::FLOAT4_COLOR>(attribute, std::forward<T>(value));
			break;
		case VertexLayout::RGBA_COLOR:
			setAttribute<VertexLayout::RGBA_COLOR>(attribute, std::forward<T>(value));
			break;
		}
	}
protected:
	Vertex(char* data, const VertexLayout& layout) noexcept : data(data), layout(layout)
	{
	}

private:
	template<typename First, typename ...Rest>
	void setAttributeByIndex(size_t i, First&& first, Rest&&... rest) noexcept
	{
		setAttributeByIndex(i, std::forward<First>(first));
		setAttributeByIndex(i + 1, std::forward<Rest>(rest)...);
	}

	template<VertexLayout::ElementType DestElementType, typename Src>
	void setAttribute(char* attribute, Src&& val) noexcept
	{
		using Dest = typename VertexLayout::Map<DestElementType>::SysType;
		if constexpr (std::is_assignable<Dest, Src>::value)
		{
			*reinterpret_cast<Dest*>(attribute) = val;
		}
	}

	char* data = nullptr;
	const VertexLayout& layout;
};

class ConstVertex
{
public:
	ConstVertex(const Vertex& vertex) noexcept : vertex(vertex)
	{
	}

	template<VertexLayout::ElementType T>
	const auto& attr() const noexcept
	{
		return const_cast<Vertex&>(vertex).attr<T>();
	}

private:
	Vertex vertex;
};

class VertexBufferData
{
public:
	VertexBufferData(VertexLayout layout) noexcept : layout(std::move(layout))
	{
	}

	const char* getData() const noexcept
	{
		return buffer.data();
	}

	const VertexLayout& getLayout() const noexcept
	{
		return layout;
	}

	size_t size() const noexcept
	{
		return buffer.size() / layout.size();
	}

	size_t sizeBytes() const noexcept
	{
		return buffer.size();
	}

	template<typename ...Params>
	void emplaceBack(Params&&... params) noexcept
	{
		buffer.resize(buffer.size() + layout.size());
		back().setAttributeByIndex(0, std::forward<Params>(params)...);
	}

	Vertex back() noexcept
	{
		return Vertex{ buffer.data() + buffer.size() - layout.size(), layout };
	}

	Vertex front() noexcept
	{
		return Vertex{ buffer.data(), layout };
	}

	Vertex operator[](size_t i) noexcept
	{
		return Vertex{ buffer.data() + layout.size() * i, layout };
	}

	ConstVertex back() const noexcept
	{
		return const_cast<VertexBufferData*>(this)->back();
	}

	ConstVertex front() const noexcept
	{
		return const_cast<VertexBufferData*>(this)->front();
	}

	ConstVertex operator[](size_t i) const noexcept
	{
		return const_cast<VertexBufferData&>(*this)[i];
	}

private:
	std::vector<char> buffer;
	VertexLayout layout;
};

#endif