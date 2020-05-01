#include "Utils.h"
#include "Window.h"
#include "GUI.h"
#include <iostream>
#include <cmath>
#include <time.h>

Utils::Vector2 screen = { 1024, 600 };
SDL_Event e;
bool quit = false;
bool moving = false;

Utils::Vector2 cameraPos = { -screen.x / 2, -screen.y / 2 }; // Start in the middle of the cartesian plane
float cameraScale = 1;
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

	GUI::setup(window.renderer);
	
	//Vectors
	Vector test1 = Vector({ -6, 7 }, { 3, 3 });
	Vector test2 = Vector({ -2, -2 }, { 5, 10 });
	Vector test3 = Vector({ 11, 2 }, { 15, 1 });
	Vector test4 = Vector({ 2, 2 }, { -3, 8 });

	TTF_Font* robotoBig = TTF_OpenFont("fonts/Roboto/Roboto-Regular.ttf", 18);
	TTF_Font* roboto = TTF_OpenFont("fonts/Roboto/Roboto-Regular.ttf", 13);

	int seconds = 0;
	int fps = 0;

	while (!quit)
	{
		mainClock.tick();
		handleInput();

		window.clear();

		//Axes
		window.drawLine({ 0, -cameraPos.y }, { screen.x, -cameraPos.y }, 0, 0, 0, 0.2);
		window.drawLine({ -cameraPos.x, 0 }, { -cameraPos.x, screen.y }, 0, 0, 0, 0.2);

		test1.length += 0.1 * mainClock.delta;
		test1.arrowLength += M_PI/12 * mainClock.delta;
		test1.generate();

		window.drawVector(test1 * cameraScale - Utils::toCoords(cameraPos), 0, 255, 255);
		window.drawVector(test2 * cameraScale - Utils::toCoords(cameraPos), 155, 0, 55);
		window.drawVector(test3 * cameraScale - Utils::toCoords(cameraPos), 255, 0, 0);
		window.drawVector(test4 * cameraScale - Utils::toCoords(cameraPos), 255, 0, 255);

		fps = 1 / mainClock.delta;

		//Sample text rendering
		GUI::begin();

		if (GUI::button(GEN_ID, 10, 10, 70, 20, "Zoom In", roboto))
		{
			cameraScale *= 1.2;
		}

		if (GUI::button(GEN_ID, 10, 40, 70, 20, "Zoom Out", roboto))
		{
			cameraScale /= 1.2;
		}

		GUI::beginContextMenu(120, 2);

		if (GUI::contextMenuItem(GEN_ID, "Add Vector", roboto))
		{
			printf("Added Vector\n");
		}
		if (GUI::contextMenuItem(GEN_ID, "Add Pole", roboto))
		{
			printf("Added Pole\n");
		}

		GUI::endContextMenu();

		GUI::end();
		
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
		cameraPos.y -= roundf(cameraSpeed * mainClock.delta);
	}

	if (keystate[SDL_SCANCODE_DOWN])
	{
		cameraPos.y += roundf(cameraSpeed * mainClock.delta);
	}

	if (keystate[SDL_SCANCODE_LEFT])
	{
		cameraPos.x -= roundf(cameraSpeed * mainClock.delta);
	}

	if (keystate[SDL_SCANCODE_RIGHT])
	{
		cameraPos.x += roundf(cameraSpeed * mainClock.delta);
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
				lastCamera = cameraPos;
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
				cameraPos.x = -delta.x + lastCamera.x;
				cameraPos.y = -delta.y + lastCamera.y;
			}
			break;
		case SDL_WINDOWEVENT:
			switch (e.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				Utils::Vector2 newSize = { (float)e.window.data1, (float)e.window.data2 };
				cameraPos -= (newSize - screen) / 2;
				screen = newSize;
				break;
			}
		}

		GUI::handleInput(e);
	}
}