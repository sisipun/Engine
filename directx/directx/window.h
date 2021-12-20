#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <memory>

#include "win_api.h"
#include "base_hr_exception.h"
#include "base_exception.h"
#include "keyboard.h"
#include "mouse.h"
#include "renderer.h"


class Window
{
public:
	class HrException : public BaseHrException
	{
		using BaseHrException::BaseHrException;
	public:
		virtual const char* getType() const noexcept override;
	};
	class NoRendererException : public BaseException
	{
		using BaseException::BaseException;
	public:
		virtual const char* getType() const noexcept override;
	};

	Window(int x, int y, int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window operator=(const Window&) = delete;
	void setTitle(const std::string& title);
	void enableCursor() noexcept;
	void disableCursor() noexcept;
	static std::optional<int> processMessage() noexcept;
	Renderer& getRenderer() const;

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	bool isCursorEnabled()
	{
		return cursorEnabled;
	}

	Keyboard keyboard;
	Mouse mouse;

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
		WindowClass& operator=(const WindowClass&) = delete;
		static WindowClass wndClass;
		static constexpr const char* wndClassName = "WindowClass";
		HINSTANCE hInstance;
	};

	void confineCursor() noexcept;
	void freeCursor() noexcept;
	void showCursor() noexcept;
	void hideCursor() noexcept;
	void enableImGuiCursor() noexcept;
	void disableImGuiCursor() noexcept;
	static LRESULT WINAPI handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT WINAPI handleMsgProxy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT WINAPI handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	bool cursorEnabled = true;
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Renderer> renderer;
	std::vector<BYTE> rawBuffer;
};

#endif