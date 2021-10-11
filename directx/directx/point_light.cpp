#include "point_light.h"
#include "imgui/imgui.h"

PointLight::PointLight(const Renderer& renderer, float radius) : mesh(renderer, radius), constantBuffer(renderer)
{
	reset();
}

void PointLight::spawnControlWindow() noexcept
{
	if (ImGui::Begin("Light"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &constData.lightPos.x, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Y", &constData.lightPos.y, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Z", &constData.lightPos.z, -60.0f, 60.0f, "%.1f");

		ImGui::Text("Intensity/Color");
		ImGui::SliderFloat("Intensity", &constData.diffuseIntensity, 0.01f, 2.0f, "%.2f", 2);
		ImGui::ColorEdit3("Ambient Light", &constData.ambientLight.x);
		ImGui::ColorEdit3("Diffuse Color", &constData.diffuseColor.x);

		ImGui::Text("Attenuation");
		ImGui::SliderFloat("Constant", &constData.attConst, 0.05f, 10.0f, "%.2f", 4);
		ImGui::SliderFloat("Linear", &constData.attLinear, 0.0001f, 4.0f, "%.4f", 8);
		ImGui::SliderFloat("Quadratic", &constData.attQuadratic, 0.0000001f, 10.0f, "%.7f", 10);

		if (ImGui::Button("Reset"))
		{
			reset();
		}
	}
	ImGui::End();
}

void PointLight::reset() noexcept
{
	constData = {
		{ 1.5f,14.0f,-4.5f },
		{ 0.05f,0.05f,0.05f },
		{ 1.0f,1.0f,1.0f },
		1.0f,
		1.0f,
		0.045f,
		0.0075f,
	};
}

void PointLight::update(const Renderer& renderer) const noexcept
{
	mesh.setPos(constData.lightPos);
	constantBuffer.update(renderer, constData);
	constantBuffer.bind(renderer);
}

void PointLight::draw(const Renderer& renderer) const noexcept
{
	mesh.draw(renderer);
}