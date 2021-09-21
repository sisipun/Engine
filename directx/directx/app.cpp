#include <sstream>
#include <optional>
#include <algorithm>

#include "app.h"
#include "box.h"
#include "melon.h"
#include "pyramid.h"
#include "sheet.h"
#include "math.h"
#include "gdi_plus_manager.h"

GDIPlusManager gdipm;

App::App() : window(100, 100, 800, 600, "Basic window")
{
	class Factory
	{
	public:
		Factory(const Renderer& renderer) : renderer(renderer)
		{
		}

		std::unique_ptr<Drawable> operator()()
		{
			switch (typeDist(range))
			{
			case 0:
				return std::make_unique<Pyramid>(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist);
			case 1:
				return std::make_unique<Box>(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist, sizeDist);
			case 2:
				return std::make_unique<Melon>(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist, longDist, latDist);
			case 3:
				return std::make_unique<Sheet>(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist);
			default:
				return {};
			}
		}
	private:
		const Renderer& renderer;
		std::mt19937 range{ std::random_device{}() };
		std::uniform_real_distribution<float> radiusDist{ 6.0f, 20.0f };
		std::uniform_real_distribution<float> anglesDist{ 0.0f, PI * 2.0f };
		std::uniform_real_distribution<float> deltaAnglesDist{ 0.0f, PI * 0.08f };
		std::uniform_real_distribution<float> deltaOrientationDist{ 0.0f, PI * 0.5f };
		std::uniform_real_distribution<float> sizeDist{ 0.4f, 3.0f };
		std::uniform_int_distribution<int> longDist{ 5, 20 };
		std::uniform_int_distribution<int> latDist{ 10, 40 };
		std::uniform_int_distribution<int> typeDist{ 0, 3 };
	};

	Factory factory(window.getRenderer());
	drawables.reserve(drawableCount);
	std::generate_n(std::back_inserter(drawables), drawableCount, factory);

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
	for (auto& drawable : drawables)
	{
		drawable->update(window.keyboard.keyIsPressed(VK_SPACE) ? 0.0f : dt);
		drawable->draw(window.getRenderer());
	}
	window.getRenderer().endFrame();
	
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