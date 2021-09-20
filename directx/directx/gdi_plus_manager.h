#ifndef GDI_MANAGER
#define GDI_MANAGER

#include "win_api.h"

class GDIPlusManager
{
public:
	GDIPlusManager();
	~GDIPlusManager();
private:
	static ULONG_PTR token;
	static int referenceCount;
};

#endif