#include "Button.h"

Button::Button(Utils::Vector2 _pos, Utils::Vector2 _size, Anchor _anchor, Utils::Vector2 _customAlignment) : pos(_pos), size(_size), anchor(_anchor), customAlignment(_customAlignment)
{
	update();
}

void Button::update()
{
	button.w = size.x;
	button.h = size.y;

	switch (anchor)
	{
	case topleft:
		button.x = pos.x;
		button.y = pos.y;
		break;
	case top:
		button.x = (pos.x - size.x) / 2;
		button.y = pos.y;
		break;
	case topright:
		button.x = pos.x - size.x;
		button.y = pos.y;
		break;
	case left:
		button.x = pos.x;
		button.y = (pos.y - size.y) / 2;
		break;
	case centre:
		button.x = (pos.x - size.x) / 2;
		button.y = (pos.y - size.y) / 2;
		break;
	case right:
		button.x = pos.x - size.x;
		button.y = (pos.y - size.y) / 2;
		break;
	case bottomleft:
		button.x = pos.x;
		button.y = pos.y - size.y;
		break;
	case bottom:
		button.x = (pos.x - size.x) / 2;
		button.y = pos.y - size.y;
		break;
	case bottomright:
		button.x = pos.x - size.x;
		button.y = pos.y - size.y;
		break;
	case custom:
		button.x = pos.x - customAlignment.x;
		button.y = pos.y - customAlignment.y;
		break;
	}
}