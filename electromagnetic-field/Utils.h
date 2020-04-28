#pragma once
#include <SDL.h>

namespace Utils
{
	SDL_Renderer* createWindow(int width = 1024, int height = 720, const char* title = "title");
}
