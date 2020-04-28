#include "Drawing.h"
#include <iostream>

namespace Drawing
{
	void clear(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderClear(renderer);
	}

	void point(SDL_Renderer* renderer, int x, int y, Uint8 r, Uint8 g, Uint8 b, double brightness)
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, brightness * 255);
		SDL_RenderDrawPoint(renderer, x, y);
	}

	void line(SDL_Renderer* renderer, double x0, double y0, double x1, double y1, Uint8 r, Uint8 g, Uint8 b, double brightness)
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
			point(renderer, yPixel1, xPixel1, r, g, b, rfPart(yEnd) * xGap * brightness);
			point(renderer, yPixel1 + 1, xPixel1, r, g, b, fPart(yEnd) * xGap * brightness);
		}

		else
		{
			point(renderer, xPixel1, yPixel1, r, g, b, rfPart(yEnd) * xGap * brightness);
			point(renderer, xPixel1, yPixel1 + 1, r, g, b, fPart(yEnd) * xGap * brightness);
		}

		double yIntersection = yEnd + gradient;

		xEnd = round(x1);
		yEnd = y1 + gradient * (xEnd - x1);
		xGap = fPart(x1 + 0.5);
		double xPixel2 = xEnd;
		double yPixel2 = floor(yEnd);

		if (steep)
		{
			point(renderer, yPixel2, xPixel2, r, g, b, rfPart(yEnd) * xGap * brightness);
			point(renderer, yPixel2 + 1, xPixel2, r, g, b, fPart(yEnd) * xGap * brightness);

			for (int x = xPixel1 + 1; x <= (xPixel2 - 1); x++)
			{
				point(renderer, yIntersection, x, r, g, b, rfPart(yIntersection) * brightness);
				point(renderer, yIntersection + 1, x, r, g, b, fPart(yIntersection) * brightness);
				yIntersection += gradient;
			}
		}

		else
		{
			point(renderer, xPixel2, yPixel2, r, g, b, rfPart(yEnd) * xGap * brightness);
			point(renderer, xPixel2, yPixel2 + 1, r, g, b, fPart(yEnd) * xGap * brightness);

			for (int x = xPixel1 + 1; x <= (xPixel2 - 1); x++)
			{
				point(renderer, x, yIntersection, r, g, b, rfPart(yIntersection) * brightness);
				point(renderer, x, yIntersection + 1, r, g, b, fPart(yIntersection) * brightness);
				yIntersection += gradient;
			}
		}
	}
}