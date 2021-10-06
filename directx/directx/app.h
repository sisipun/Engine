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
	void showModelWindow();

	ImguiManager imguiManager;
	Window window;
	Timer timer;
	Camera camera;
	PointLight light;
	float speed_factor = 1.0f;
	Model nano{ window.getRenderer(), "models\\nanosuit.obj" };
	struct
	{
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	} position;
};

#endif 