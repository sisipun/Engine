#include "app.h"
#include "base_exception.h"

#include <sstream>

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	try
	{
		App().start();
	}
	catch (const BaseException& e)
	{
		MessageBox(nullptr, e.what(), e.getType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{

		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}