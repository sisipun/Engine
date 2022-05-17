#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "bindable.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(const Renderer& renderer, const std::vector<unsigned short>& indices);

	void bind(const Renderer& renderer) noexcept override;
	UINT getCount() const noexcept;
protected:
	UINT count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
};

#endif 