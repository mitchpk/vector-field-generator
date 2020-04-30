#include "Window.h"
#include <iostream>

void Window::create(int _width, int _height, const char* title)
{
	width = _width;
	height = _height;
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, SDL_VIDEO_RENDER_OGL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
	SDL_SetRenderDrawColor(renderer, r, g, b, opacity * 255);
	SDL_RenderDrawLine(renderer, point1.x, point1.y, point2.x, point2.y);
}

void Window::drawVector(Vector vector, Uint8 r, Uint8 g, Uint8 b, double opacity)
{
	if (vector.isValid)
	{
		drawLine(Utils::toPixels(vector.calculatedHead), Utils::toPixels(vector.tail), r, g, b, opacity);
		drawLine(Utils::toPixels(vector.arrowPoint1 + vector.calculatedHead), Utils::toPixels(vector.calculatedHead), r, g, b, opacity);
		drawLine(Utils::toPixels(vector.arrowPoint2 + vector.calculatedHead), Utils::toPixels(vector.calculatedHead), r, g, b, opacity);
	}
}

void Window::drawButton(Button button, Uint8 r, Uint8 g, Uint8 b, double opacity)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, opacity * 255);
	SDL_RenderFillRect(renderer, &button.button);
}

void Window::printText(std::string messageText, Utils::Vector2 pos, TTF_Font* font, SDL_Color color) {
	int texW = 0, texH = 0;
	SDL_Surface* surface = TTF_RenderText_Blended(font, messageText.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { pos.x, pos.y, texW, texH };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

void Window::render()
{
	SDL_RenderPresent(renderer);
}