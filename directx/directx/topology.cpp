#include "topology.h"

Topology::Topology(const Renderer& renderer, D3D11_PRIMITIVE_TOPOLOGY type) : type(type)
{

}

void Topology::bind(const Renderer& renderer) noexcept
{
	renderer.getContext()->IASetPrimitiveTopology(type);
}

std::string Topology::getUid(D3D11_PRIMITIVE_TOPOLOGY type) noexcept
{
	return typeid(Topology).name() + std::string("#") + std::to_string(type);
}