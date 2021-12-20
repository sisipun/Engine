#ifndef GDI_MANAGER_H
#define GDI_MANAGER_H

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