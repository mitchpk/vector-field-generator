#include "Window.h"
#include <iostream>

Window::Window(int width, int height, const char* title) : _width(width), _height(height)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void Window::clear(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderClear(renderer);
}

void Window::drawPoint(int x, int y, Uint8 r, Uint8 g, Uint8 b, double opacity)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, opacity * 255);
	SDL_RenderDrawPoint(renderer, x, y);
};

void Window::drawLine(Utils::Vector2 point1, Utils::Vector2 point2, Uint8 r, Uint8 g, Uint8 b, double opacity)
{
	drawLine(point1.x, point1.y, point2.x, point2.y, r, g, b, opacity);
	//SDL_SetRenderDrawColor(renderer, r, g, b, opacity * 255);
	//SDL_RenderDrawLine(renderer, point1.x, point1.y, point2.x, point2.y);
}

void Window::drawVector(Vector vector, Uint8 r, Uint8 g, Uint8 b, double opacity)
{
	if (vector.isValid)
	{
		drawLine(Utils::toPixels(vector.head), Utils::toPixels(vector.tail), r, g, b, opacity);
		drawLine(Utils::toPixels(vector.arrowPoint1 + vector.head), Utils::toPixels(vector.head), r, g, b, opacity);
		drawLine(Utils::toPixels(vector.arrowPoint2 + vector.head), Utils::toPixels(vector.head), r, g, b, opacity);
	}
}

void Window::drawLine(double x0, double y0, double x1, double y1, Uint8 r, Uint8 g, Uint8 b, double opacity)
{
	bool steep = fabs(y1 - y0) > fabs(x1 - x0);

	if (steep)
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	double dx = x1 - x0;
	double dy = y1 - y0;

	double gradient = dx == 0.0 ? 1.0 : dy / dx;

	double xEnd = round(x0);
	double yEnd = y0 + gradient * (xEnd - x0);
	double xGap = rfPart(x0 + 0.5);
	double xPixel1 = xEnd;
	double yPixel1 = floor(yEnd);

	if (steep)
	{
		drawPoint(yPixel1, xPixel1, r, g, b, rfPart(yEnd) * xGap * opacity);
		drawPoint(yPixel1 + 1, xPixel1, r, g, b, fPart(yEnd) * xGap * opacity);
	}

	else
	{
		drawPoint(xPixel1, yPixel1, r, g, b, rfPart(yEnd) * xGap * opacity);
		drawPoint(xPixel1, yPixel1 + 1, r, g, b, fPart(yEnd) * xGap * opacity);
	}

	double yIntersection = yEnd + gradient;

	xEnd = round(x1);
	yEnd = y1 + gradient * (xEnd - x1);
	xGap = fPart(x1 + 0.5);
	double xPixel2 = xEnd;
	double yPixel2 = floor(yEnd);

	if (steep)
	{
		drawPoint(yPixel2, xPixel2, r, g, b, rfPart(yEnd) * xGap * opacity);
		drawPoint(yPixel2 + 1, xPixel2, r, g, b, fPart(yEnd) * xGap * opacity);

		for (int x = xPixel1 + 1; x <= (xPixel2 - 1); x++)
		{
			drawPoint(yIntersection, x, r, g, b, rfPart(yIntersection) * opacity);
			drawPoint(yIntersection + 1, x, r, g, b, fPart(yIntersection) * opacity);
			yIntersection += gradient;
		}
	}

	else
	{
		drawPoint(xPixel2, yPixel2, r, g, b, rfPart(yEnd) * xGap * opacity);
		drawPoint(xPixel2, yPixel2 + 1, r, g, b, fPart(yEnd) * xGap * opacity);

		for (int x = xPixel1 + 1; x <= (xPixel2 - 1); x++)
		{
			drawPoint(x, yIntersection, r, g, b, rfPart(yIntersection) * opacity);
			drawPoint(x, yIntersection + 1, r, g, b, fPart(yIntersection) * opacity);
			yIntersection += gradient;
		}
	}
}

void Window::render()
{
	SDL_RenderPresent(renderer);
}