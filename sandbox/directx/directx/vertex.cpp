#include "vertex.h"

VertexLayout::Element::Element(ElementType type, size_t offset) : type(type), offset(offset)
{
}

size_t VertexLayout::Element::getOffsetAfter() const noexcept
{
	return offset + size();
}

size_t VertexLayout::Element::getOffset() const noexcept
{
	return offset;
}

size_t VertexLayout::Element::size() const noexcept
{
	return sizeOf(type);
}

constexpr size_t VertexLayout::Element::sizeOf(ElementType type) noexcept
{
	switch (type)
	{
	case ElementType::POSITION2D:
		return sizeof(Map<ElementType::POSITION2D>::SysType);
	case ElementType::POSITION3D:
		return sizeof(Map<ElementType::POSITION3D>::SysType);
	case ElementType::TEXTURE2D:
		return sizeof(Map<ElementType::TEXTURE2D>::SysType);
	case ElementType::NORMAL:
		return sizeof(Map<ElementType::NORMAL>::SysType);
	case ElementType::TANGENT:
		return sizeof(Map<ElementType::TANGENT>::SysType);
	case ElementType::BITANGENT:
		return sizeof(Map<ElementType::BITANGENT>::SysType);
	case ElementType::FLOAT3_COLOR:
		return sizeof(Map<ElementType::FLOAT3_COLOR>::SysType);
	case ElementType::FLOAT4_COLOR:
		return sizeof(Map<ElementType::FLOAT4_COLOR>::SysType);
	case ElementType::RGBA_COLOR:
		return sizeof(Map<ElementType::RGBA_COLOR>::SysType);
	}

	return 0;
}

VertexLayout::ElementType VertexLayout::Element::getType() const noexcept
{
	return type;
}

D3D11_INPUT_ELEMENT_DESC VertexLayout::Element::getDesc() const noexcept
{
	switch (type)
	{
	case ElementType::POSITION2D:
		return generateDesc<ElementType::POSITION2D>(getOffset());
	case ElementType::POSITION3D:
		return generateDesc<ElementType::POSITION3D>(getOffset());
	case ElementType::TEXTURE2D:
		return generateDesc<ElementType::TEXTURE2D>(getOffset());
	case ElementType::NORMAL:
		return generateDesc<ElementType::NORMAL>(getOffset());
	case ElementType::TANGENT:
		return generateDesc<ElementType::TANGENT>(getOffset());
	case ElementType::BITANGENT:
		return generateDesc<ElementType::BITANGENT>(getOffset());
	case ElementType::FLOAT3_COLOR:
		return generateDesc<ElementType::FLOAT3_COLOR>(getOffset());
	case ElementType::FLOAT4_COLOR:
		return generateDesc<ElementType::FLOAT4_COLOR>(getOffset());
	case ElementType::RGBA_COLOR:
		return generateDesc<ElementType::RGBA_COLOR>(getOffset());
	}

	return { "INVALID", 0, DXGI_FORMAT_UNKNOWN, 0, (UINT)offset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
}

const char* VertexLayout::Element::getCode() const noexcept
{
	switch (type)
	{
	case ElementType::POSITION2D:
		return Map<ElementType::POSITION2D>::code;
	case ElementType::POSITION3D:
		return Map<ElementType::POSITION3D>::code;
	case ElementType::TEXTURE2D:
		return Map<ElementType::TEXTURE2D>::code;
	case ElementType::NORMAL:
		return Map<ElementType::NORMAL>::code;
	case ElementType::TANGENT:
		return Map<ElementType::TANGENT>::code;
	case ElementType::BITANGENT:
		return Map<ElementType::BITANGENT>::code;
	case ElementType::FLOAT3_COLOR:
		return Map<ElementType::FLOAT3_COLOR>::code;
	case ElementType::FLOAT4_COLOR:
		return Map<ElementType::FLOAT4_COLOR>::code;
	case ElementType::RGBA_COLOR:
		return Map<ElementType::RGBA_COLOR>::code;
	}

	return "Invalid";
}

const VertexLayout::Element& VertexLayout::resolveByIndex(size_t i) const noexcept
{
	return elements[i];
}

VertexLayout& VertexLayout::append(ElementType type) noexcept
{
	elements.emplace_back(type, size());
	return *this;
}

size_t VertexLayout::size() const noexcept
{
	return elements.empty() ? 0 : elements.back().getOffsetAfter();
}

size_t VertexLayout::getElementsCount() const noexcept
{
	return elements.size();
}

std::vector<D3D11_INPUT_ELEMENT_DESC> VertexLayout::getDescLayout() const noexcept
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> descriptions;
	descriptions.reserve(getElementsCount());
	for (const auto& element : elements)
	{
		descriptions.push_back(element.getDesc());
	}
	return descriptions;
}

std::string VertexLayout::getCode() const noexcept
{
	std::string code;
	for (const auto& element : elements)
	{
		code += element.getCode();
	}
	return code;
}

Vertex::Vertex(char* data, const VertexLayout& layout) noexcept : data(data), layout(layout)
{
}

ConstVertex::ConstVertex(const Vertex& vertex) noexcept : vertex(vertex)
{
}

VertexBufferData::VertexBufferData(VertexLayout layout, size_t size) noexcept : layout(std::move(layout))
{
	resize(size);
}

const char* VertexBufferData::getData() const noexcept
{
	return buffer.data();
}

void VertexBufferData::resize(size_t newSize) noexcept
{
	const auto oldSize = size();
	if (oldSize < newSize)
	{
		buffer.resize(buffer.size() + layout.size() * (newSize - oldSize));
	}
}

const VertexLayout& VertexBufferData::getLayout() const noexcept
{
	return layout;
}

size_t VertexBufferData::size() const noexcept
{
	return buffer.size() / layout.size();
}

size_t VertexBufferData::sizeBytes() const noexcept
{
	return buffer.size();
}

Vertex VertexBufferData::back() noexcept
{
	return Vertex{ buffer.data() + buffer.size() - layout.size(), layout };
}

Vertex VertexBufferData::front() noexcept
{
	return Vertex{ buffer.data(), layout };
}

Vertex VertexBufferData::operator[](size_t i) noexcept
{
	return Vertex{ buffer.data() + layout.size() * i, layout };
}

ConstVertex VertexBufferData::back() const noexcept
{
	return const_cast<VertexBufferData*>(this)->back();
}

ConstVertex VertexBufferData::front() const noexcept
{
	return const_cast<VertexBufferData*>(this)->front();
}

ConstVertex VertexBufferData::operator[](size_t i) const noexcept
{
	return const_cast<VertexBufferData&>(*this)[i];
}