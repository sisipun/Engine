#include "imgui/imgui.h"

#include "test_cube.h"
#include "bindable_store.h"
#include "constant_buffer.h"
#include "index_buffer.h"
#include "input_layout.h"
#include "pixel_shader.h"
#include "topology.h"
#include "transform_cbuf.h"
#include "vertex_buffer.h"
#include "vertex_shader.h"
#include "texture.h"
#include "vertex.h"
#include "cube.h"

TestCube::TestCube(const Renderer& renderer, float size)
{
	auto model = Cube::makeTextured();
	model.transform(DirectX::XMMatrixScaling(size, size, size));
	model.setNormalsIndependentFlat();

	addBind(std::make_shared<VertexBuffer>(renderer, model.vertexBufferData));
	addBind(std::make_shared<IndexBuffer>(renderer, model.indices));
	addBind(BindableStore::resolve<Texture>(renderer, "images\\brickwall.jpg"));
	addBind(BindableStore::resolve<Texture>(renderer, "images\\brickwall_normal.jpg", 1));

	auto vertexShader = BindableStore::resolve<VertexShader>(renderer, "phong_vertex.cso");
	auto vertexShaderBytecode = vertexShader->getBytecode();
	addBind(std::move(vertexShader));
	addBind(BindableStore::resolve<PixelShader>(renderer, "phong_normal_pixel.cso"));

	addBind(std::make_shared<PixelConstantBuffer<ConstantData>>(renderer, constData));

	addBind(BindableStore::resolve<InputLayout>(renderer, model.vertexBufferData.getLayout(), vertexShaderBytecode));
	addBind(BindableStore::resolve<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	addBind(std::make_shared<TransformCbuf>(renderer, *this));
}

void TestCube::setPos(DirectX::XMFLOAT3 pos) noexcept
{
	this->pos = pos;
}

void TestCube::setRotation(float roll, float pitch, float yaw) noexcept
{
	this->roll = roll;
	this->pitch = pitch;
	this->yaw = yaw;
}

DirectX::XMMATRIX TestCube::getTransform() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}

void TestCube::spawnControlWindow(const Renderer& renderer) noexcept
{
	if (ImGui::Begin("Cube"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &pos.x, -80.0f, 80.0f, "%.1f");
		ImGui::SliderFloat("Y", &pos.y, -80.0f, 80.0f, "%.1f");
		ImGui::SliderFloat("Z", &pos.z, -80.0f, 80.0f, "%.1f");
		ImGui::Text("Orientation");
		ImGui::SliderAngle("Roll", &roll, -180.0f, 180.0f);
		ImGui::SliderAngle("Pitch", &pitch, -180.0f, 180.0f);
		ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
		ImGui::Text("Shading");
		bool changedSpecularIntensity = ImGui::SliderFloat("Spec. Int.", &constData.specularIntensity, 0.0f, 1.0f);
		bool changedSpecularPower = ImGui::SliderFloat("Spec. Power", &constData.specularPower, 0.0f, 100.0f);
		bool checkState = constData.normalMappingEnabled == TRUE;
		bool changedNormalMapping = ImGui::Checkbox("Enable Normal Map", &checkState);
		constData.normalMappingEnabled = checkState ? TRUE : FALSE;
		if (changedSpecularIntensity || changedSpecularPower || changedNormalMapping)
		{
			queryBindable<PixelConstantBuffer<ConstantData>>()->update(renderer, constData);
		}
	}
	ImGui::End();
}