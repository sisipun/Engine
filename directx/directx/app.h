#ifndef APP_H
#define APP_H

#include "window.h"
#include "timer.h"
#include "imgui_manager.h"
#include "camera.h"
#include "point_light.h"
#include "mesh.h"

class App
{
public:
	App();
	~App();

	int start();

private:
	void processFrame();

	ImguiManager imguiManager;
	Window window;
	Timer timer;
	Camera camera;
	PointLight light;
	float speed_factor = 1.0f;
	Model nano{ window.getRenderer(), "models\\nano_hierarchy.gltf" };

	static constexpr float travelSpeed = 6.0f;
};

#endif 