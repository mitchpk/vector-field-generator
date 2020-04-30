#include "Utils.h"
#include "Window.h"
#include "Button.h"
#include <iostream>
#include <cmath>
#include <time.h>

Utils::Vector2 screen = { 1024, 600 };
SDL_Event e;
bool quit = false;
bool moving = false;

Utils::Vector2 camera = { -screen.x / 2, -screen.y / 2 }; // Start in the middle of the cartesian plane
float cameraSpeed = 500; // in pixels per second
Utils::Vector2 lastCamera;
Utils::Vector2 mouse;
Utils::Clock mainClock;

Window window;

void handleInput();

int main(int argc, char** argv)
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window.create(screen.x, screen.y, "Vector Field");
	
	//Vectors
	Vector test1 = Vector({ -6, 7 }, { 3, 3 });
	Vector test2 = Vector({ -2, -2 }, { 5, 10 });
	Vector test3 = Vector({ 11, 2 }, { 15, 1 });
	Vector test4 = Vector({ 2, 2 }, { -3, 8 });

	//Drawing a button
	Utils::Vector2 pos = { 10, 200 };
	Utils::Vector2 size = { 120, 60 };
	Button testbutton = Button(pos, size);

	while (!quit)
	{
		mainClock.tick();
		handleInput();

		window.clear();

		//Axes
		window.drawLine({ 0, -camera.y }, { screen.x, -camera.y }, 0, 0, 0, 0.2);
		window.drawLine({ -camera.x, 0 }, { -camera.x, screen.y }, 0, 0, 0, 0.2);

		test1.length += 0.1 * mainClock.delta;
		test1.arrowLength += M_PI/12 * mainClock.delta;
		test1.generate();

		window.drawVector(test1 - Utils::toCoords(camera), 0, 255, 255);
		window.drawVector(test2 - Utils::toCoords(camera), 155, 0, 55);
		window.drawVector(test3 - Utils::toCoords(camera), 255, 0, 0);
		window.drawVector(test4 - Utils::toCoords(camera), 255, 0, 255);

		//Sample text rendering
		TTF_Font* lato = TTF_OpenFont("fonts/Lato/Lato-Regular.ttf", 18);
		window.printText("Hello", { 10, 10 }, lato, { 50, 50, 50 });
		window.drawButton(testbutton, 50, 50, 50);
		window.render();
	}

	SDL_Quit();

	return 0;
}

void handleInput()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_UP])
	{
		camera.y -= roundf(cameraSpeed * mainClock.delta);
	}

	if (keystate[SDL_SCANCODE_DOWN])
	{
		camera.y += roundf(cameraSpeed * mainClock.delta);
	}

	if (keystate[SDL_SCANCODE_LEFT])
	{
		camera.x -= roundf(cameraSpeed * mainClock.delta);
	}

	if (keystate[SDL_SCANCODE_RIGHT])
	{
		camera.x += roundf(cameraSpeed * mainClock.delta);
	}

	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouse = Utils::getMousePos();
				lastCamera = camera;
				moving = true;
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				moving = false;
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			if (moving)
			{
				Utils::Vector2 delta = Utils::getMousePos() - mouse;
				camera.x = -delta.x + lastCamera.x;
				camera.y = -delta.y + lastCamera.y;
			}
			break;
		case SDL_WINDOWEVENT:
			switch (e.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				Utils::Vector2 newSize = { (float)e.window.data1, (float)e.window.data2 };
				camera -= (newSize - screen) / 2;
				screen = newSize;
				break;
			}
		}
	}
}