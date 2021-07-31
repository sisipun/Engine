#ifndef RENDERER_H
#define RENDERER_H

#include <d3d11.h>
#include <wrl.h>

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
	~Renderer() = default;
	void endFrame();
	void clearBuffer(float red, float green, float blue) noexcept;
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget;
};

#endif
