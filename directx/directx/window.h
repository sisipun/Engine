#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "win_api.h"

class Window
{
public:
	Window(int x, int y, int width, int height, const wchar_t* name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window operator=(const Window&) = delete;
private:
	class WindowClass
	{
	public:
		static const wchar_t* getName() noexcept;
		static HINSTANCE getInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass operator=(const WindowClass&) = delete;
		static WindowClass wndClass;
		static constexpr const wchar_t* wndClassName = L"WindowClass";
		HINSTANCE hInstance;
	};

	static LRESULT WINAPI handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT WINAPI handleMsgProxy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT WINAPI handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	HWND hWnd;
};

#endif