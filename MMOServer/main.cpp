#include "Windows.h"
#include "WindowManager.h"
#include <SDL/SDL.h>
#include <iostream>
#include "Engine.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	AllocConsole();
	FILE* file = new FILE();
	freopen_s(&file, "CONOUT$", "w", stdout);

	Engine engine;

	if (engine.init())
	{
		return engine.run();
	}
	else
	{
		return 1;
	}
}