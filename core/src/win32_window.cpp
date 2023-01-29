#include <pickle/win32_window.h>

#include <windows.h>
#include <tchar.h>

#include <pickle/metal_renderer.h>
#include <pickle/directx_renderer.h>
#include <pickle/logger.h>

pickle::Win32Window::Win32Window(int width, int height) : Window(width, height)
{
    MessageBox(NULL, _T("Text"), _T("Caption"), MB_OK);
    renderer = std::make_unique<pickle::renderer::DirectXRenderer>();
}

pickle::Win32Window::~Win32Window()
{
}

bool pickle::Win32Window::isClosed() const
{
    return false;
}