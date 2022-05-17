#define FULL_WINTARD

#include <algorithm>

#include "win_api.h"
#include "gdi_plus_manager.h"

namespace Gdiplus
{
using std::min;
using std::max;
}
#include <gdiplus.h>

ULONG_PTR GDIPlusManager::token = 0;
int GDIPlusManager::referenceCount = 0;

GDIPlusManager::GDIPlusManager()
{
	if (referenceCount++ == 0)
	{
		Gdiplus::GdiplusStartupInput input;
		input.GdiplusVersion = 1;
		input.DebugEventCallback = nullptr;
		input.SuppressBackgroundThread = false;
		Gdiplus::GdiplusStartup(&token, &input, nullptr);
	}
}

GDIPlusManager::~GDIPlusManager()
{
	if (--referenceCount == 0)
	{
		Gdiplus::GdiplusShutdown(token);
	}
}