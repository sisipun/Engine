#ifndef RENDERER_H
#define RENDERER_H

#include <d3d11.h>

#include "win_api.h"
#include "base_hr_exception.h"

class Renderer
{
public:
	class HrException : public BaseHrException
	{
		using BaseHrException::BaseHrException;
	public:
		const char* getType() const noexcept override;
	};
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* getType() const noexcept override;
	};

	Renderer(HWND hWnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer();
	void endFrame();
	void clearBuffer(float red, float green, float blue)
	{
		const float color[] = { red, green, blue };
		deviceContext->ClearRenderTargetView(renderTarget, color);
	}
private:
	ID3D11Device* device = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	ID3D11RenderTargetView* renderTarget = nullptr;
};

#endif
