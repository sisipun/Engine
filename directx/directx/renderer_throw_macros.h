#ifndef RENDERER_THROW_MACROS
#define RENDERER_THROW_MACROS

#define RENDERER_THROW_NOINFO(hResult, hResultCall) if (FAILED(hResult = hResultCall)) { if (hResult == DXGI_ERROR_DEVICE_REMOVED) { throw Renderer::DeviceRemovedException(__LINE__, __FILE__, hResult); } else { throw Renderer::HrException(__LINE__, __FILE__, hResult); }}

#ifndef NDEBUG
#define CHECK_INFO_MESSAGES(call) infoManager.set(); call; { auto v = infoManager.getMessages(); if (!v.empty()) { throw Renderer::InfoException(__LINE__, __FILE__, v); } }
#else
#define CHECK_INFO_MESSAGE(call) call;
#endif

#endif