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
				return sizeof(DirectX::XMFLOAT2);
			case POSITION3D:
				return sizeof(DirectX::XMFLOAT3);
			case TEXTURE2D:
				return sizeof(DirectX::XMFLOAT2);
			case NORMAL:
				return sizeof(DirectX::XMFLOAT3);
			case FLOAT3_COLOR:
				return sizeof(DirectX::XMFLOAT3);
			case FLOAT4_COLOR:
				return sizeof(DirectX::XMFLOAT4);
			case RGBA_COLOR:
				return sizeof(RGBAColor);
			}

			return 0;
		}

		ElementType getType() const noexcept
		{
			return type;
		}

	private:
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

	template<ElementType T>
	VertexLayout& append() noexcept
	{
		elements.emplace_back(T, size());
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

private:
	std::vector<Element> elements;
};

class Vertex
{
	friend class VertexBuffer;
public:
	template<VertexLayout::ElementType T>
	auto& attr() noexcept
	{
		const auto& element = layout.resolve<T>();
		auto attribute = data + element.getOffset();
		if constexpr (T == VertexLayout::POSITION2D)
		{
			return *reinterpret_cast<DirectX::XMFLOAT2*>(attribute);
		}
		else if constexpr (T == VertexLayout::POSITION3D)
		{
			return *reinterpret_cast<DirectX::XMFLOAT3*>(attribute);
		}
		else if constexpr (T == VertexLayout::TEXTURE2D)
		{
			return *reinterpret_cast<DirectX::XMFLOAT2*>(attribute);
		}
		else if constexpr (T == VertexLayout::NORMAL)
		{
			return *reinterpret_cast<DirectX::XMFLOAT3*>(attribute);
		}
		else if constexpr (T == VertexLayout::FLOAT3_COLOR)
		{
			return *reinterpret_cast<DirectX::XMFLOAT3*>(attribute);
		}
		else if constexpr (T == VertexLayout::FLOAT4_COLOR)
		{
			return *reinterpret_cast<DirectX::XMFLOAT4*>(attribute);
		}
		else if constexpr (T == VertexLayout::RGBA_COLOR)
		{
			return *reinterpret_cast<RGBAColor*>(attribute);
		}
		else
		{
			return *reinterpret_cast<char*>(attribute);
		}
	}

	template<typename T>
	void setAttributeByIndex(size_t index, T&& value) noexcept
	{
		const auto& element = layout.resolveByIndex(index);
		auto attribute = data + element.getOffset();
		switch (element.getType())
		{
		case VertexLayout::POSITION2D:
			setAttribute<DirectX::XMFLOAT2>(attribute, std::forward<T>(value));
			break;
		case VertexLayout::POSITION3D:
			setAttribute<DirectX::XMFLOAT3>(attribute, std::forward<T>(value));
			break;
		case VertexLayout::TEXTURE2D:
			setAttribute<DirectX::XMFLOAT2>(attribute, std::forward<T>(value));
			break;
		case VertexLayout::NORMAL:
			setAttribute<DirectX::XMFLOAT3>(attribute, std::forward<T>(value));
			break;
		case VertexLayout::FLOAT3_COLOR:
			setAttribute<DirectX::XMFLOAT3>(attribute, std::forward<T>(value));
			break;
		case VertexLayout::FLOAT4_COLOR:
			setAttribute<DirectX::XMFLOAT4>(attribute, std::forward<T>(value));
			break;
		case VertexLayout::RGBA_COLOR:
			setAttribute<RGBAColor>(attribute, std::forward<T>(value));
			break;
		}
	}
protected:
	Vertex(char* data, const VertexLayout layout) noexcept : data(data), layout(layout)
	{
	}

private:
	template<typename First, typename ...Rest>
	void setAttributeByIndex(size_t i, First&& first, Rest&&... rest) noexcept
	{
		setAttributeByIndex(i, std::forward<First>(first));
		setAttributeByIndex(i + 1, std::forward<Rest>(rest)...);
	}

	template<typename Dest, typename Src>
	void setAttribute(char* attribute, Src&& val) noexcept
	{
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

class VertexBuffer
{
public:
	VertexBuffer(VertexLayout layout) noexcept : layout(std::move(layout))
	{
	}

	const VertexLayout& getLayout() const noexcept
	{
		return layout;
	}

	size_t size() const noexcept
	{
		return buffer.size() / layout.size();
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
		return const_cast<VertexBuffer*>(this)->back();
	}

	ConstVertex front() const noexcept
	{
		return const_cast<VertexBuffer*>(this)->front();
	}

	ConstVertex operator[](size_t i) const noexcept
	{
		return const_cast<VertexBuffer&>(*this)[i];
	}

private:
	std::vector<char> buffer;
	VertexLayout layout;
};

#endif