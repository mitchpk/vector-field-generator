#pragma once
#include "Utils.h"

enum Anchor
{
	topleft,
	top,
	topright,
	left,
	centre,
	right,
	bottomleft,
	bottom,
	bottomright,
	custom
};

struct Button
{
	Utils::Vector2 pos, size, customAlignment;
	SDL_Rect button;
	Anchor anchor;
	Button(Utils::Vector2 pos, Utils::Vector2 size, Anchor anchor = Anchor::topleft, Utils::Vector2 customAlignment = { 0, 0 });
	void update();
};