#include "Utils.h"
#include "Window.h"
#include "GUI.h"
#include "InputRecognition.h"
#include <iostream>
#include <cmath>
#include <vector>

Utils::Vector2 screen = { 1024, 600 };
SDL_Event e;
bool quit = false;
bool moving = false;

Utils::Vector2 cameraPos = { -screen.x / 2, -screen.y / 2 }; // Start in the middle of the cartesian plane
float cameraScale = 1;
float cameraSpeed = 500; // in pixels per second
Utils::Clock mainClock;

Window window;

void handleInput();

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window.create(screen.x, screen.y, "Vector Field");

	GUI::setup(window.renderer);
	
	//Vectors
	//Vector test1 = Vector({ -6, 7 }, { 3, 3 });
	//Vector test2 = Vector({ -2, -2 }, { 5, 10 });
	//Vector test3 = Vector({ 11, 2 }, { 15, 1 });
	//Vector test4 = Vector({ 0, 0 }, { 3, 4 });
	//Vector test5 = Vector({ -5, -4 }, { -1, -1 }, 10);


	std::vector<Vector> field = {};
	std::vector<Variable> values = { Variable("pi", std::atan(1) * 4, true), Variable("e", std::exp(1), true), Variable("k", 1), Variable("x", -20), Variable("y", -20) };

	for (float i = -20; i < 21; i++)
	{
		values[3].value = i;
		for (float j = -20; j < 21; j++)
		{
			values[4].value = j;
			field.push_back(Vector({ i, j }, { (float)eval("1/x+x", values), (float)eval("1/y+y", values)}, 0.6, constrained, 0.1));
		}	
	}
	TTF_Font* robotoBig = TTF_OpenFont("fonts/Roboto/Roboto-Regular.ttf", 18);
	TTF_Font* roboto = TTF_OpenFont("fonts/Roboto/Roboto-Regular.ttf", 13);

	while (!quit)
	{
		mainClock.tick();
		handleInput();

		window.clear();

		//Axes
		window.drawLine({ 0, -cameraPos.y }, { screen.x, -cameraPos.y }, 0, 0, 0, 0.2);
		window.drawLine({ -cameraPos.x, 0 }, { -cameraPos.x, screen.y }, 0, 0, 0, 0.2);

		//test1.length += 0.1f * mainClock.delta;
		//test1.generate();

		//window.drawVector(test1 * cameraScale - Utils::toCoords(cameraPos), 0, 255, 255);
		//window.drawVector(test2 * cameraScale - Utils::toCoords(cameraPos), 155, 0, 55);
		//window.drawVector(test3 * cameraScale - Utils::toCoords(cameraPos), 255, 0, 0);
		//window.drawVector(test4 * cameraScale - Utils::toCoords(cameraPos), 255, 0, 255);
		//window.drawVector(test5 * cameraScale - Utils::toCoords(cameraPos), 255, 0, 0);

		for (int i = 0; i < field.size(); i++)
		{
			window.drawVector(field[i] * cameraScale - Utils::toCoords(cameraPos), 255, 0, 255);
		}

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
		GUI::handleInput(e);

		switch (e.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				if (!GUI::uiState.interacting)
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
				if (!GUI::uiState.interacting)
				{
					cameraPos.x -= e.motion.xrel;
					cameraPos.y -= e.motion.yrel;
				}
				else moving = false;
			}
			break;
		case SDL_MOUSEWHEEL:
			if (e.wheel.y > 0) // scroll up
			{
				cameraScale *= 1.2;
			}
			else if (e.wheel.y < 0) // scroll down
			{
				cameraScale /= 1.2;
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
	}
}