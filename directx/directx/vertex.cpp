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

VertexLayout::ElementType VertexLayout::Element::getType() const noexcept
{
	return type;
}

D3D11_INPUT_ELEMENT_DESC VertexLayout::Element::getDesc() const noexcept
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

Vertex::Vertex(char* data, const VertexLayout& layout) noexcept : data(data), layout(layout)
{
}

ConstVertex::ConstVertex(const Vertex& vertex) noexcept : vertex(vertex)
{
}

VertexBufferData::VertexBufferData(VertexLayout layout) noexcept : layout(std::move(layout))
{
}

const char* VertexBufferData::getData() const noexcept
{
	return buffer.data();
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