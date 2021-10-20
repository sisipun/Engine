#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "bindable.h"
#include "index_buffer.h"

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable& drawable) = delete;
	virtual DirectX::XMMATRIX getTransform() const noexcept = 0;
	void draw(const Renderer& renderer) const;
	virtual ~Drawable() = default;
protected:
	void addBind(std::shared_ptr<Bindable> bind) noexcept;
	const IndexBuffer* indexBuffer = nullptr;
private:
	std::vector<std::shared_ptr<Bindable>> binds;
};

#endif 
