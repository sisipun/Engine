#include <pickle/win32_window.h>

#include <tchar.h>
#include <windows.h>

#include <pickle/logger.h>

LRESULT CALLBACK windowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

const char* pickle::Win32Window::BASE_WINNDOW_CLASS = "BASE_WINDOW";

pickle::Win32Window::Win32Window(int width, int height) : Window(width, height)
{
    HINSTANCE hInstance = GetModuleHandle(0);

    WNDCLASSEX windowClass;
    ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

    RECT wr = {0, 0, width, height};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = windowProc;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = _T(BASE_WINNDOW_CLASS);

    RegisterClassEx(&windowClass);
    hWindow = CreateWindowEx(NULL,
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
}

pickle::Win32Window::~Win32Window()
{
}

HWND pickle::Win32Window::getWindow() const
{
    return hWindow;
}

void pickle::Win32Window::show()
{
    ShowWindow(hWindow, 1);
}

void pickle::Win32Window::update()
{
    MSG message;
    if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);

        if (message.message == WM_QUIT)
        {
            closed = true;
        }
    }
}

LRESULT CALLBACK windowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWindow, message, wParam, lParam);
}