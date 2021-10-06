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
	virtual void update(float dt) noexcept {};
	virtual ~Drawable() = default;
protected:
	void addBind(std::unique_ptr<Bindable> bind) noexcept;
	void addIndexBuffer(std::unique_ptr<class IndexBuffer> indexBuffer) noexcept;
	const IndexBuffer* indexBuffer = nullptr;
private:
	virtual const std::vector<std::unique_ptr<Bindable>>& getStaticBinds() const noexcept = 0;
	std::vector<std::unique_ptr<Bindable>> binds;
};

#endif 
