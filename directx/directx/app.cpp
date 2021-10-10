#include <sstream>
#include <optional>
#include <algorithm>

#include "imgui/imgui.h"
#include "app.h"
#include "math.h"
#include "gdi_plus_manager.h"
#include "vertex.h"

GDIPlusManager gdipm;

App::App() : window(100, 100, 1280, 720, "Basic window"), light(window.getRenderer()), camera(window.getRenderer())
{
	window.getRenderer().setProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5, 40.0f));
	window.disableCursor();
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
	nano.spawnControlWindow();

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