#ifndef APP_H
#define APP_H

#include "window.h"
#include "timer.h"
#include "imgui_manager.h"
#include "camera.h"
#include "point_light.h"

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
	std::vector<std::unique_ptr<class Drawable>> drawables;
	float speed_factor = 1.0f;
	static constexpr size_t drawableCount = 180;
};

#endif 