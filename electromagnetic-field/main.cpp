#include "Utils.h"
#include "Drawing.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 720;

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Renderer* renderer = Utils::createWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Electromagnetic Vector Field");
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_Event e;
	bool quit = false;
	while (!quit && SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}

		Drawing::clear(renderer);

		Drawing::line(renderer, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 4 * 3, 255, 0, 0, 0.5);
		Drawing::line(renderer, SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 * 3, 0, 0, 255, 0.5);

		SDL_RenderPresent(renderer);
	}

	SDL_Quit();

	return 0;
}