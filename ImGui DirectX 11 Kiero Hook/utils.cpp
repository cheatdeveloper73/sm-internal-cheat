#include "utils.h"
#include "globals.h"

CUtils utils;

void CUtils::unloadcheat()
{
	kiero::shutdown();
	FreeLibraryAndExitThread(globals.cheat_module, 1);
	return;
}