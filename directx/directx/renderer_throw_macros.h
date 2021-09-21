#ifndef RENDERER_THROW_MACROS
#define RENDERER_THROW_MACROS

#define RENDERER_THROW_NOINFO(hResult, call) if (FAILED(hResult = call)) { if (hResult == DXGI_ERROR_DEVICE_REMOVED) { throw Renderer::DeviceRemovedException(__LINE__, __FILE__, hResult); } else { throw Renderer::HrException(__LINE__, __FILE__, hResult); }}

#ifndef NDEBUG
#define INFOMAN(renderer) DxgiInfoManager& infoManager = renderer.getInfoManager();
#define CHECK_INFO_MESSAGES(call) infoManager.set(); call; { auto v = infoManager.getMessages(); if (!v.empty()) { throw Renderer::InfoException(__LINE__, __FILE__, v); } }
#else
#define INFOMAN(renderer);
#define CHECK_INFO_MESSAGES(call) call;
#endif

#endif