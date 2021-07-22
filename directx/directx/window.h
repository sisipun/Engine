#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "win_api.h"
#include "base_exception.h"
#include "keyboard.h"


class Window
{
public:
	class Exception : public BaseException
	{
	public:
		Exception(int line, const char* file, HRESULT hResult) noexcept;
		const char* what() const noexcept override;
		virtual const char* getType() const noexcept override;
		static std::string translateErrorCode(HRESULT hResult) noexcept;
		HRESULT getErrorCode() const noexcept;
		std::string getErrorString() const noexcept;

	private:
		HRESULT hResult;
	};

	Window(int x, int y, int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window operator=(const Window&) = delete;

	Keyboard keyboard;
private:
	class WindowClass
	{
	public:
		static const char* getName() noexcept;
		static HINSTANCE getInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass operator=(const WindowClass&) = delete;
		static WindowClass wndClass;
		static constexpr const char* wndClassName = "WindowClass";
		HINSTANCE hInstance;
	};

	static LRESULT WINAPI handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT WINAPI handleMsgProxy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT WINAPI handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	HWND hWnd;
};

#define WND_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr)
#define WND_LAST_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, GetLastError())

#endif