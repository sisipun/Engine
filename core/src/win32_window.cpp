#include <pickle/win32_window.h>

#include <tchar.h>
#include <windows.h>

#include <pickle/directx_renderer.h>
#include <pickle/logger.h>
#include <pickle/metal_renderer.h>

LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

const char* pickle::Win32Window::BASE_WINNDOW_CLASS = "BASE_WINDOW";

pickle::Win32Window::Win32Window(int width, int height) : Window(width, height)
{
    HINSTANCE hInstance = GetModuleHandle(0);

    HWND hWnd;
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    RECT wr = {0, 0, 500, 400};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = windowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T(BASE_WINNDOW_CLASS);

    RegisterClassEx(&wc);
    hWnd = CreateWindowEx(NULL,
                          _T(BASE_WINNDOW_CLASS),
                          _T("Description"),
                          WS_OVERLAPPEDWINDOW,
                          300,
                          300,
                          wr.right - wr.left,
                          wr.bottom - wr.top,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    renderer = std::make_unique<pickle::renderer::DirectXRenderer>();
    ShowWindow(hWnd, 1);
}

pickle::Win32Window::~Win32Window()
{
}

void pickle::Win32Window::update()
{
    MSG msg;
    if (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    else
    {
        closed = true;
    }
}

LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}