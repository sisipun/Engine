#include "point_light.h"
#include "imgui/imgui.h"

PointLight::PointLight(const Renderer& renderer, float radius): mesh(renderer, radius), constantBuffer(renderer)
{
}

void PointLight::spawnControlWindow() noexcept
{
	if (ImGui::Begin("Light"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &pos.x, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Y", &pos.y, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Z", &pos.z, -60.0f, 60.0f, "%.1f");
		if (ImGui::Button("Reset"))
		{
			reset();
		}
	}
	ImGui::End();
}

void PointLight::reset() noexcept
{
	pos = { 0.0f, 0.0f, 0.0f };
}

void PointLight::update(const Renderer& renderer) const noexcept
{
	mesh.setPos(pos);
	constantBuffer.update(renderer, ConstantData{ pos });
	constantBuffer.bind(renderer);
}

void PointLight::draw(const Renderer& renderer) const noexcept
{
	mesh.draw(renderer);
}