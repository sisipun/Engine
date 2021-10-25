#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <type_traits>

#include "renderer.h"
#include "color.h"

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
		static constexpr const char* code = "P2";
	};

	template<>
	struct Map<POSITION3D>
	{
		using SysType = DirectX::XMFLOAT3;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
		static constexpr const char* semantic = "Position";
		static constexpr const char* code = "P3";
	};

	template<>
	struct Map<TEXTURE2D>
	{
		using SysType = DirectX::XMFLOAT2;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32_FLOAT;
		static constexpr const char* semantic = "TexCoord";
		static constexpr const char* code = "T2";
	};

	template<>
	struct Map<NORMAL>
	{
		using SysType = DirectX::XMFLOAT3;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
		static constexpr const char* semantic = "Normal";
		static constexpr const char* code = "N2";
	};

	template<>
	struct Map<FLOAT3_COLOR>
	{
		using SysType = DirectX::XMFLOAT3;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
		static constexpr const char* semantic = "Color";
		static constexpr const char* code = "C3";
	};

	template<>
	struct Map<FLOAT4_COLOR>
	{
		using SysType = DirectX::XMFLOAT4;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
		static constexpr const char* semantic = "Color";
		static constexpr const char* code = "C4";
	};

	template<>
	struct Map<RGBA_COLOR>
	{
		using SysType = RGBAColor;
		static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		static constexpr const char* semantic = "Color";
		static constexpr const char* code = "C8";
	};

	class Element
	{
	public:
		Element(ElementType type, size_t offset);

		size_t getOffsetAfter() const noexcept;
		size_t getOffset() const noexcept;
		size_t size() const noexcept;
		static constexpr size_t sizeOf(ElementType type) noexcept;
		ElementType getType() const noexcept;
		D3D11_INPUT_ELEMENT_DESC getDesc() const noexcept;
		const char* getCode() const noexcept;

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
	const VertexLayout::Element& resolve() const noexcept
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
	const Element& resolveByIndex(size_t i) const noexcept;
	VertexLayout& append(ElementType type) noexcept;
	size_t size() const noexcept;
	size_t getElementsCount() const noexcept;
	std::vector<D3D11_INPUT_ELEMENT_DESC> getDescLayout() const noexcept;
	std::string getCode() const noexcept;

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
	Vertex(char* data, const VertexLayout& layout) noexcept;

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
	ConstVertex(const Vertex& vertex) noexcept;

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
	VertexBufferData(VertexLayout layout, size_t size = 0) noexcept;

	const char* getData() const noexcept;
	const VertexLayout& getLayout() const noexcept;
	void resize(size_t newSize) noexcept;
	size_t size() const noexcept;
	size_t sizeBytes() const noexcept;

	template<typename ...Params>
	void emplaceBack(Params&&... params) noexcept
	{
		buffer.resize(buffer.size() + layout.size());
		back().setAttributeByIndex(0, std::forward<Params>(params)...);
	}

	Vertex back() noexcept;
	Vertex front() noexcept;
	Vertex operator[](size_t i) noexcept;
	ConstVertex back() const noexcept;
	ConstVertex front() const noexcept;
	ConstVertex operator[](size_t i) const noexcept;

private:
	std::vector<char> buffer;
	VertexLayout layout;
};

#endif