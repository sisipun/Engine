#include "camera.h"
#include "imgui/imgui.h"

DirectX::XMMATRIX Camera::getMatrix() const noexcept {
	const auto position = DirectX::XMVector3Transform(
		DirectX::XMVectorSet(0.0f, 0.0f, -radius, 0.0f),
		DirectX::XMMatrixRotationRollPitchYaw(phi, -theta, 0.0f)
	);

	return DirectX::XMMatrixLookAtLH(
		position,
		DirectX::XMVectorZero(),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	) * DirectX::XMMatrixRotationRollPitchYaw(pitch, -yaw, roll);
}

void Camera::spawnControlWindow() noexcept
{
	if (ImGui::Begin("Camera"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("Radius", &radius, 0.1f, 80.0f, "%.1f");
		ImGui::SliderAngle("Theta", &theta, -180.0f, 180.0f);
		ImGui::SliderAngle("Phi", &phi, -89.0f, 89.0f);
		ImGui::Text("Oritentattion");
		ImGui::SliderAngle("Roll", &roll, -180.0f, 180.0f);
		ImGui::SliderAngle("Pitch", &pitch, -180.0f, 180.0f);
		ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
		if (ImGui::Button("Reset"))
		{
			reset();
		}
	}
	ImGui::End();
}

void Camera::reset() noexcept
{
	radius = 20.0f; 
	theta = 0.0f;
	phi = 0.0f;
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
}