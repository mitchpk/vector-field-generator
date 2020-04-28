#include "Utils.h"
namespace Utils
{
	SDL_Renderer* createWindow(int width, int height, const char* title)
	{
		SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
		return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
}