#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include <memory>
#include <random>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>

#include "win_api.h"
#include "base_exception.h"
#include "base_hr_exception.h"
#include "dxgi_info_manager.h"

class Renderer
{
public:
	class InfoException : public BaseException
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMessages) noexcept;
		const char* what() const noexcept override;
		const char* getType() const noexcept override;
		std::string getErrorInfo() const noexcept;
	private:
		std::string info;
	};
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
	void drawIndexed(UINT count) const;

	ID3D11Device* getDevice() const noexcept;
	ID3D11DeviceContext* getContext() const noexcept;
	DirectX::XMMATRIX getProjection() const noexcept;
	void setProjection(DirectX::XMMATRIX projection) noexcept;

#ifndef NDEBUG
	DxgiInfoManager& getInfoManager() noexcept;
#endif

private:
	DirectX::XMMATRIX projection;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;

#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
};

#endif
