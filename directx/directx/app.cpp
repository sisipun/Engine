#include <sstream>
#include <optional>
#include <algorithm>

#include "app.h"
#include "box.h"
#include "pyramid.h"
#include "sheet.h"
#include "skinned_box.h"
#include "math.h"
#include "gdi_plus_manager.h"
#include "imgui/imgui.h"

GDIPlusManager gdipm;

App::App() : window(100, 100, 800, 600, "Basic window"), light(window.getRenderer())
{
	class Factory
	{
	public:
		Factory(const Renderer& renderer) : renderer(renderer)
		{
		}

		std::unique_ptr<Drawable> operator()()
		{
			const DirectX::XMFLOAT3 materialColor = { colorDist(range), colorDist(range), colorDist(range) };
			return std::make_unique<Box>(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist, sizeDist, materialColor);
		}
	private:
		const Renderer& renderer;
		std::mt19937 range{ std::random_device{}() };
		std::uniform_real_distribution<float> radiusDist{ 6.0f, 20.0f };
		std::uniform_real_distribution<float> anglesDist{ 0.0f, PI * 2.0f };
		std::uniform_real_distribution<float> deltaAnglesDist{ 0.0f, PI * 0.08f };
		std::uniform_real_distribution<float> deltaOrientationDist{ 0.0f, PI * 0.5f };
		std::uniform_real_distribution<float> sizeDist{ 0.4f, 3.0f };
		std::uniform_real_distribution<float> colorDist{ 0.0f, 1.0f };
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
	auto dt = timer.mark() * speed_factor;
	window.getRenderer().beginFrame(0.07f, 0.0f, 0.12f);
	window.getRenderer().setCamera(camera.getMatrix());

	light.update(window.getRenderer());

	for (auto& drawable : drawables)
	{
		drawable->update(window.keyboard.keyIsPressed(VK_SPACE) ? 0.0f : dt);
		drawable->draw(window.getRenderer());
	}

	light.draw(window.getRenderer());

	if (ImGui::Begin("Simulation Speed"))
	{
		ImGui::SliderFloat("Speed Factor", &speed_factor, 0.0f, 4.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Status: %s", window.keyboard.keyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING");
	}
	ImGui::End();

	camera.spawnControlWindow();
	light.spawnControlWindow();

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