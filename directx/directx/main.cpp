#include "window.h"
#include "base_exception.h"

#include <sstream>

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	try
	{
		Window w(100, 100, 500, 500, "Hello");

		MSG msg = {};
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (w.keyboard.keyIsPressed(VK_SPACE)) {
				MessageBox(nullptr, "Key pressed", "Pressed", MB_OK | MB_ICONEXCLAMATION);
			}

			while (!w.mouse.isEmpty())
			{
				const auto e = *w.mouse.read();
				if (e.getType() == Mouse::Event::Type::MOVE) {
					std::ostringstream oss;
					oss << "Mouse position : (" << e.getPositionX() << ", " << e.getPositionY() << ")";
					w.setTitle(oss.str());
				}
			}
		}

		if (gResult == -1)
		{
			return -1;
		}
		else
		{
			return msg.wParam;
		}
	}
	catch (const BaseException& e)
	{
		MessageBox(nullptr, e.what(), e.getType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{

		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}