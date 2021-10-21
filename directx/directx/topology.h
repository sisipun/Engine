#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "bindable.h"

class Topology : public Bindable
{
public:
	Topology(const Renderer& renderer, D3D11_PRIMITIVE_TOPOLOGY type);

	void bind(const Renderer& renderer) noexcept override;
	std::string getUid() const noexcept override;
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
};

#endif 
