#include <sstream>

#include "window.h"


Window::WindowClass Window::WindowClass::wndClass;

Window::Exception::Exception(int line, const char* file, HRESULT hResult) noexcept : BaseException(line, file), hResult(hResult)
{
}

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << getType() << std::endl << "[Error code] " << getErrorCode() << std::endl << "[Description] " << getErrorString() << std::endl << getOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::Exception::getType() const noexcept
{
	return "Window Exception";
}

std::string Window::Exception::translateErrorCode(HRESULT hResult) noexcept
{
	char* msgBuf = nullptr;
	DWORD msgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		hResult,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&msgBuf),
		0,
		nullptr
	);
	if (msgLen == 0)
	{
		return "Undefined error code";
	}
	std::string errorString = msgBuf;
	LocalFree(msgBuf);
	return errorString;
}

HRESULT Window::Exception::getErrorCode() const noexcept
{
	return hResult;
}

std::string Window::Exception::getErrorString() const noexcept
{
	return translateErrorCode(hResult);
}

Window::Window(int x, int y, int width, int height, const char* name) : width(width), height(height)
{
	RECT wr;
	wr.left = x;
	wr.right = wr.left + width;
	wr.top = y;
	wr.bottom = wr.top + height;
	if (!AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE))
	{
		throw WND_LAST_EXCEPT();
	}

	hWnd = CreateWindow(
		WindowClass::getName(),
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		x,
		y,
		wr.right - wr.left,
		wr.bottom - wr.top,
		nullptr,
		nullptr,
		WindowClass::getInstance(),
		this
	);

	if (hWnd == nullptr)
	{
		throw WND_LAST_EXCEPT();
	}

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

void Window::setTitle(const std::string& title)
{
	if (!SetWindowText(hWnd, title.c_str()))
	{
		throw WND_LAST_EXCEPT();
	}
}

std::optional<int> Window::processMessage() noexcept
{
	MSG message;
	while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
	{
		if (message.message == WM_QUIT)
		{
			return message.wParam;
		}

		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return std::nullopt;
}

Window::WindowClass::WindowClass() noexcept
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = handleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = getInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = getName();
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass() noexcept
{
	UnregisterClass(getName(), getInstance());
}

const char* Window::WindowClass::getName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::getInstance() noexcept
{
	return wndClass.hInstance;
}

LRESULT CALLBACK Window::handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCT* const pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::handleMsgProxy));

		return pWnd->handleMsg(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::handleMsgProxy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->handleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_KILLFOCUS:
		keyboard.clearState();
		break;


	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (!(lParam & 0x40000000) || keyboard.autorepeatIsEnabled())
		{
			keyboard.onKeyPressed(wParam);
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		keyboard.onKeyReleased(wParam);
		break;
	case WM_CHAR:
		keyboard.onChar(wParam);
		break;


	case WM_MOUSEMOVE:
	{
		const POINTS point = MAKEPOINTS(lParam);
		if (point.x >= 0 && point.x < width && point.y >= 0 && point.y < height)
		{
			mouse.onMouseMove(point.x, point.y);
			if (!mouse.isInWindow())
			{
				SetCapture(hWnd);
				mouse.onMouseEnter();
			}
		}
		else
		{
			if (wParam & (MK_LBUTTON | MK_RBUTTON))
			{

				mouse.onMouseMove(point.x, point.y);
			}
			else
			{
				ReleaseCapture();
				mouse.onMouseLeave();
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		const POINTS point = MAKEPOINTS(lParam);
		mouse.onLeftPressed(point.x, point.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		const POINTS point = MAKEPOINTS(lParam);
		mouse.onRightPressed(point.x, point.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS point = MAKEPOINTS(lParam);
		mouse.onLeftReleased(point.x, point.y);

		if (point.x < 0 || point.x >= width || point.y < 0 || point.y >= height)
		{
			ReleaseCapture();
			mouse.onMouseLeave();
		}
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS point = MAKEPOINTS(lParam);
		mouse.onRightReleased(point.x, point.y);

		if (point.x < 0 || point.x >= width || point.y < 0 || point.y >= height)
		{
			ReleaseCapture();
			mouse.onMouseLeave();
		}
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const POINTS point = MAKEPOINTS(lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		mouse.onWheelDelta(point.x, point.y, delta);
		break;
	}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}