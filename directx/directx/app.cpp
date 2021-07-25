#include <sstream>
#include <optional>

#include "app.h"

App::App() : window(100, 100, 800, 600, "Basic window")
{
}

int App::start()
{
	while (true)
	{
		if (const std::optional<int> exitCode = window.processMessage())
		{
			return *exitCode;
		};

		processFrame();
	}
}

void App::processFrame()
{
	if (window.keyboard.keyIsPressed(VK_SPACE))
	{
		MessageBox(nullptr, "Key pressed", "Pressed", MB_OK | MB_ICONEXCLAMATION);
	}

	while (!window.mouse.isEmpty())
	{
		const auto e = *window.mouse.read();
		if (e.getType() == Mouse::Event::Type::MOVE)
		{
			std::ostringstream oss;
			oss << "Mouse position : (" << e.getPositionX() << ", " << e.getPositionY() << ")";
			window.setTitle(oss.str());
		}
	}
}