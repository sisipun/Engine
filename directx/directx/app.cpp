#include <sstream>
#include <optional>
#include <algorithm>

#include "imgui/imgui.h"
#include "app.h"
#include "suzanne.h"
#include "math.h"
#include "gdi_plus_manager.h"
#include "vertex.h"

GDIPlusManager gdipm;

App::App() : window(100, 100, 800, 600, "Basic window"), light(window.getRenderer()), camera(window.getRenderer())
{
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

	camera.update(window.getRenderer());
	light.update(window.getRenderer());
	
	const auto transform = DirectX::XMMatrixRotationRollPitchYaw(position.pitch, position.yaw, position.roll) *
		DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	nano.draw(window.getRenderer(), transform);

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
	showModelWindow();

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

void App::showModelWindow()
{
	if (ImGui::Begin("Model"))
	{
		ImGui::Text("Orientation");
		ImGui::SliderAngle("Roll", &position.roll, -180.0f, 180.0f);
		ImGui::SliderAngle("Pitch", &position.pitch, -180.0f, 180.0f);
		ImGui::SliderAngle("Yaw", &position.yaw, -180.0f, 180.0f);

		ImGui::Text("Position");
		ImGui::SliderFloat("X", &position.x, -20.0f, 20.0f);
		ImGui::SliderFloat("Y", &position.y, -20.0f, 20.0f);
		ImGui::SliderFloat("Z", &position.z, -20.0f, 20.0f);
	}
	ImGui::End();
}