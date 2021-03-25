#include "Globals.h"

void CreateGlobals()
{
	Singleton<ResourceManager>::CreateInstance();
}

void DestroyGlobals()
{
	Singleton<ResourceManager>::DestroyInstance();
}
