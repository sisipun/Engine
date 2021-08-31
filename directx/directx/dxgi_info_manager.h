#ifndef DXGI_INFO_MANAGER
#define DXGI_INFO_MANAGER

#include <string>
#include <vector>
#include <wrl.h>
#include <dxgidebug.h>

#include "win_api.h"

class DxgiInfoManager
{
public:
	DxgiInfoManager();
	~DxgiInfoManager() = default;
	DxgiInfoManager(const DxgiInfoManager&) = delete;
	DxgiInfoManager& operator=(const DxgiInfoManager&) = delete;
	void set() const noexcept;
	std::vector<std::string> getMessages() const;
private:
	mutable unsigned long long next = 0u;
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> dxgiInfoQueue;
};

#endif