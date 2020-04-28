#include "Utils.h"
#include "Window.h"
#include <iostream>
#include <cmath>
#include <time.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 600;
SDL_Event e;
bool quit = false;

Utils::Vector2 camera = { -SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2 }; // Start in the middle of the cartesian plane
Utils::Clock mainClock;

Window window;

void handleInput();

int main(int argc, char** argv)
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	window = Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Vector Field");

	while (!quit)
	{
		mainClock.tick();
		handleInput();

		window.clear();

		window.drawLine(window.toPixels({ 0, -100 }) - camera, window.toPixels({ 0, 100 }) - camera, 0, 0, 0);
		window.drawLine(window.toPixels({ -100, 0 }) - camera, window.toPixels({ 100, 0 }) - camera, 0, 0, 0);

		Vector test1 = Vector({ -6, 7 }, { 3, 3 });
		Vector test2 = Vector({ -2, -2 }, { 5, 10 });
		Vector test3 = Vector({ 11, 2 }, { 15, 1 });
		Vector test4 = Vector({ 2, 2 }, { 2, 5 });

		test1.head -= window.toCoords(camera);
		test1.tail -= window.toCoords(camera);
		test2.head -= window.toCoords(camera);
		test2.tail -= window.toCoords(camera);
		test3.head -= window.toCoords(camera);
		test3.tail -= window.toCoords(camera);
		test4.head -= window.toCoords(camera);
		test4.tail -= window.toCoords(camera);

		window.drawVector(test1, 0, 255, 255);
		window.drawVector(test2, 155, 0, 55, 0.5);
		window.drawVector(test3, 0, 255, 255, 0.21);
		window.drawVector(test4, 255, 0, 255, 0.75);
		
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
		camera.y -= 500 * mainClock.delta;
	}

	if (keystate[SDL_SCANCODE_DOWN])
	{
		camera.y += 500 * mainClock.delta;
	}

	if (keystate[SDL_SCANCODE_LEFT])
	{
		camera.x -= 500 * mainClock.delta;
	}

	if (keystate[SDL_SCANCODE_RIGHT])
	{
		camera.x += 500 * mainClock.delta;
	}

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
	}
}