#ifndef APP_H
#define APP_H

#include "window.h"
#include "timer.h"

class App
{
public:
	App();
	~App();

	int start();

private:
	void processFrame();

	Window window;
	Timer timer;
	std::vector<std::unique_ptr<class Box>> boxes;
};

#endif 