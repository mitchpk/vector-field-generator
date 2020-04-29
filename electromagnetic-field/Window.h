#pragma once
#include <SDL.h>
#include "Utils.h"
#include "Vector.h"

class Window
{
private:
	int _width, _height;

public:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Window(int width = 1024, int height = 720, const char* title = "title");

	//Drawing
	double inline fPart(double x) { return x - floor(x); }
	double inline rfPart(double x) { return 1 - fPart(x); }

	void clear(Uint8 r = 245, Uint8 g = 245, Uint8 b = 245);
	void drawPoint(int x, int y, Uint8 r, Uint8 g, Uint8 b, double opacity = 1);
	void drawLine(Utils::Vector2 point1, Utils::Vector2 point2, Uint8 r, Uint8 g, Uint8 b, double opacity = 1);
	void drawVector(Vector vector, Uint8 r, Uint8 g, Uint8 b, double opacity = 1);

	void render();
};