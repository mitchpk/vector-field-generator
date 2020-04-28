#pragma once
#include <SDL.h>

namespace Drawing
{
	double inline fPart(double x) { return x - floor(x); }
	double inline rfPart(double x) { return 1 - fPart(x); }

	void clear(SDL_Renderer* renderer, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);
	void point(SDL_Renderer* renderer, int x, int y, Uint8 r, Uint8 g, Uint8 b, double brightness = 1);
	void line(SDL_Renderer* renderer, double x0, double y0, double x1, double y1, Uint8 r, Uint8 g, Uint8 b, double brightness = 1);
};

