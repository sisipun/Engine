#ifndef APP_H
#define APP_H

#include "window.h"
#include "timer.h"

class App
{
public:
	App();

	int start();

private:
	void processFrame();

	Window window;
	Timer timer;
};

#endif 