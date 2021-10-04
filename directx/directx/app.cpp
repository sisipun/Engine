#include <sstream>
#include <optional>
#include <algorithm>

#include "app.h"
#include "box.h"
#include "cylinder.h"
#include "pyramid.h"
#include "skinned_box.h"
#include "suzanne.h"
#include "math.h"
#include "gdi_plus_manager.h"
#include "imgui/imgui.h"
#include "vertex_layout.h"

GDIPlusManager gdipm;

void test()
{
	VertexBuffer vb(std::move(
		VertexLayout{}
		.append<VertexLayout::POSITION3D>()
		.append<VertexLayout::NORMAL>()
		.append<VertexLayout::TEXTURE2D>()
	));
	vb.emplaceBack(
		DirectX::XMFLOAT3{ 1.0f,1.0f,5.0f },
		DirectX::XMFLOAT3{ 2.0f,1.0f,4.0f },
		DirectX::XMFLOAT2{ 6.0f,9.0f }
	);
	vb.emplaceBack(
		DirectX::XMFLOAT3{ 6.0f,9.0f,6.0f },
		DirectX::XMFLOAT3{ 9.0f,6.0f,9.0f },
		DirectX::XMFLOAT2{ 4.2f,0.0f }
	);
	auto pos = vb[0].attr<VertexLayout::POSITION3D>();
	auto nor = vb[0].attr<VertexLayout::NORMAL>();
	auto tex = vb[1].attr<VertexLayout::TEXTURE2D>();
	vb.back().attr<VertexLayout::POSITION3D>().z = 420.0f;
	pos = vb.back().attr<VertexLayout::POSITION3D>();

	const auto& cvb = vb;
	pos = cvb[1].attr<VertexLayout::POSITION3D>();
}

App::App() : window(100, 100, 800, 600, "Basic window"), light(window.getRenderer()), camera(window.getRenderer())
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

			switch (typeDist(range))
			{
			case 0:
				return std::make_unique<Box>(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist, sizeDist, materialColor);
			case 1:
				return std::make_unique<Cylinder>(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist, tesselationDist);
			case 2:
				return std::make_unique<Pyramid>(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist, tesselationDist);
			case 3:
				return std::make_unique<SkinnedBox>(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist);
			case 4:
				return std::make_unique<Suzanne>(renderer, range, radiusDist, anglesDist, deltaAnglesDist, deltaOrientationDist, materialColor, 1.5f);
			default:
				return {};
			}
		}
	private:
		const Renderer& renderer;
		std::mt19937 range{ std::random_device{}() };
		std::uniform_int_distribution<int> typeDist{ 0, 4 };
		std::uniform_real_distribution<float> radiusDist{ 6.0f, 20.0f };
		std::uniform_real_distribution<float> anglesDist{ 0.0f, PI * 2.0f };
		std::uniform_real_distribution<float> deltaAnglesDist{ 0.0f, PI * 0.08f };
		std::uniform_real_distribution<float> deltaOrientationDist{ 0.0f, PI * 0.5f };
		std::uniform_real_distribution<float> sizeDist{ 0.4f, 3.0f };
		std::uniform_real_distribution<float> colorDist{ 0.0f, 1.0f };
		std::uniform_real_distribution<float> tesselationDist{ 3, 30 };
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

	camera.update(window.getRenderer());
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