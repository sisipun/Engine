#include "imgui/imgui.h"
#include "camera.h"
#include "math.h"

Camera::Camera(const Renderer& renderer) : constantBuffer(renderer, 2)
{
	reset();
}

DirectX::XMMATRIX Camera::getMatrix() const noexcept {
	const DirectX::XMVECTOR forwardBaseVector = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const auto lookVector = DirectX::XMVector3Transform(forwardBaseVector, DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f));

	const auto cameraPosition = DirectX::XMLoadFloat3(&position);
	const auto cameraTarget = DirectX::operator+(cameraPosition, lookVector);
	return DirectX::XMMatrixLookAtLH(cameraPosition, cameraTarget, DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
}

void Camera::spawnControlWindow() noexcept
{
	if (ImGui::Begin("Camera"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &position.x, -80.0f, 80.0f, "%.1f");
		ImGui::SliderFloat("Y", &position.y, -80.0f, 80.0f, "%.1f");
		ImGui::SliderFloat("Z", &position.z, -80.0f, 80.0f, "%.1f");
		ImGui::Text("Oritentattion");
		ImGui::SliderAngle("Pitch", &pitch, 0.95 * -90.0f, 0.95 * 90.0f);
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
	position = { 0.0f,0.0f,-10.0f };
	pitch = 0.0f;
	yaw = 0.0f;
}

void Camera::rotate(float dx, float dy) noexcept
{
	yaw = wrap_angle(yaw + dx * sensitivity);
	pitch = std::clamp(pitch + dy * sensitivity, 0.95f * -PI / 2.0f, 0.95f * PI / 2.0f);
}

void Camera::translate(DirectX::XMFLOAT3 translation) noexcept
{
	DirectX::XMStoreFloat3(&translation, DirectX::XMVector3Transform(
		DirectX::XMLoadFloat3(&translation),
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0)
	));
	position = {
		position.x + translation.x,
		position.y + translation.y,
		position.z + translation.z
	};
}

void Camera::update(const Renderer& renderer) const noexcept
{
	constantBuffer.update(renderer, { position });
	constantBuffer.bind(renderer);
}