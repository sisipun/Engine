#include <sstream>
#include <optional>
#include <algorithm>

#include "imgui/imgui.h"
#include "app.h"
#include "math.h"
#include "gdi_plus_manager.h"
#include "vertex.h"

GDIPlusManager gdipm;

App::App() :
	window(100, 100, 1280, 720, "Basic window"),
	light(window.getRenderer()),
	camera(window.getRenderer()),
	nano(window.getRenderer(), "models\\nano_textured\\nanosuit.obj"),
	plane(window.getRenderer(), 3.0f)
{
	plane.setPos({ 1.0f,17.0f,-1.0f });
	window.getRenderer().setProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 40.0f));
}

App::~App()
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
	auto dt = timer.mark() * speed_factor;
	window.getRenderer().beginFrame(0.07f, 0.0f, 0.12f);
	window.getRenderer().setCamera(camera.getMatrix());

	camera.update(window.getRenderer());
	light.update(window.getRenderer());

	nano.draw(window.getRenderer());
	plane.draw(window.getRenderer());
	light.draw(window.getRenderer());

	nano.spawnControlWindow();
	plane.spawnControlWindow(window.getRenderer());
	light.spawnControlWindow();
	camera.spawnControlWindow();

	window.getRenderer().endFrame();

	while (const auto event = window.keyboard.readKey())
	{
		if (!event->isPress())
		{
			continue;
		}

		switch (event->getCode())
		{
		case VK_ESCAPE:
			if (window.isCursorEnabled())
			{
				window.disableCursor();
				window.mouse.enableRaw();
			}
			else
			{
				window.enableCursor();
				window.mouse.disableRaw();
			}
			break;
		}
	}

	if (!window.isCursorEnabled())
	{
		if (window.keyboard.keyIsPressed('W'))
		{
			camera.translate({ 0.0f, 0.0f, dt * travelSpeed });
		}
		if (window.keyboard.keyIsPressed('A'))
		{
			camera.translate({ -dt * travelSpeed, 0.0f, 0.0f });
		}
		if (window.keyboard.keyIsPressed('S'))
		{
			camera.translate({ 0.0f, 0.0f, -dt * travelSpeed });
		}
		if (window.keyboard.keyIsPressed('D'))
		{
			camera.translate({ dt * travelSpeed, 0.0f, 0.0f });
		}
		if (window.keyboard.keyIsPressed('R'))
		{
			camera.translate({ 0.0f, dt * travelSpeed, 0.0f });
		}
		if (window.keyboard.keyIsPressed('F'))
		{
			camera.translate({ 0.0f, -dt * travelSpeed, 0.0f });
		}
	}

	while (const auto delta = window.mouse.readRawDelta())
	{
		if (!window.isCursorEnabled())
		{
			camera.rotate((float)delta->x, (float)delta->y);
		}
	}

	while (!window.mouse.isEmpty())
	{
		const auto e = *window.mouse.read();
		if (e.getType() == Mouse::Event::Type::MOVE)
		{
			std::ostringstream oss;
			oss << "Mouse position : (" << e.getPositionX() << ", " << e.getPositionY() << ")";
			//window.setTitle(oss.str());
		}
	}
}