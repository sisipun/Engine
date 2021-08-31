#include <sstream>
#include <optional>

#include "app.h"
#include "box.h"

App::App() : window(100, 100, 800, 600, "Basic window")
{
	std::mt19937 range(std::random_device{}());
	std::uniform_real_distribution<float> radiusDist(6.0f, 20.0f);
	std::uniform_real_distribution<float> anglesDist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> deltaAnglesDist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> deltaOrientationDist(0.0f, 3.1415f * 2.0f);

	for (unsigned int i = 0; i < 80; i++)
	{
		boxes.push_back(std::make_unique<Box>(window.getRenderer(), range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist));
	}

	window.getRenderer().setProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5, 40.0f));
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
	auto dt = timer.mark();
	window.getRenderer().clearBuffer(0.07f, 0.0f, 0.12f);
	for (auto& box : boxes)
	{
		box->update(dt);
		box->draw(window.getRenderer());
	}
	window.getRenderer().endFrame();
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