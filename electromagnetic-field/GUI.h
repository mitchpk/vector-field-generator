#pragma once
#include <SDL.h>

#ifdef IMGUI_SRC_ID
#define GEN_ID ((IMGUI_SRC_ID) + (__LINE__))
#else
#define GEN_ID (__LINE__)
#endif

namespace GUI
{
	SDL_Renderer* renderer;

	namespace Colours
	{
		SDL_Color BORDER = { 36, 38, 39, 255 };
		SDL_Color BACKGROUND = { 86, 88, 89, 255 };
		SDL_Color BACKGROUND_HOT = { 100, 100, 100, 255 };
		SDL_Color BACKGROUND_ACTIVE = { 80, 80, 80, 255 };
		SDL_Color BACKGROUND_DARK = { 40, 40, 40, 255 };
		SDL_Color FOREGROUND = { 220, 220, 220, 255 };
		SDL_Color FOREGROUND_HOT = { 255, 255, 255, 255 };
		SDL_Color FOREGROUND_ACTIVE = { 255, 255, 255, 255 };
	}

	struct UIState
	{
		int mouseX;
		int mouseY;
		bool leftMouseDown;
		bool rightMouseDown;
		bool lastRightMouse;

		int hotControl;
		int activeControl;
		bool contextMenu;

		int contextMenuX;
		int contextMenuY;
		int contextMenuWidth;
		int contextMenuHeight;
		int contextMenuItemHeight;
		int contextMenuLevel;
	}
	uiState;

	enum SliderType
	{
		Horizontal,
		Vertical
	};

	void handleInput(SDL_Event& e)
	{
		switch (e.type)
		{
		case SDL_MOUSEMOTION:
			uiState.mouseX = e.motion.x;
			uiState.mouseY = e.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				uiState.leftMouseDown = true;
				break;
			case SDL_BUTTON_RIGHT:
				uiState.rightMouseDown = true;
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				uiState.leftMouseDown = false;
				break;
			case SDL_BUTTON_RIGHT:
				uiState.rightMouseDown = false;
				break;
			}
			break;
		}
	}

	bool regionHit(int x, int y, int w, int h)
	{
		if (uiState.mouseX < x ||
			uiState.mouseY < y ||
			uiState.mouseX >= x + w ||
			uiState.mouseY >= y + h)
			return false;

		return true;
	}

	void drawRect(int x, int y, int w, int h, SDL_Color colour)
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
		SDL_RenderDrawRect(renderer, &rect);
	}

	void drawFilledRect(int x, int y, int w, int h, SDL_Color colour)
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
		SDL_RenderFillRect(renderer, &rect);
	}

	void text(int x, int y, const char* text = "", TTF_Font* font = nullptr)
	{
		if (text != "" && font != nullptr)
		{
			SDL_Surface* surface = TTF_RenderText_Blended(font, text, Colours::FOREGROUND);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_Rect dstrect = { x, y, surface->w, surface->h };
			//SDL_RenderDrawRect(renderer, &dstrect);
			SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		}
	}

	bool button(int id, int x, int y, int w, int h, const char* text = "", TTF_Font* font = nullptr)
	{
		bool hasText = false;
		SDL_Color textColour;

		if (text != "" && font != nullptr)
			hasText = true;

		if (regionHit(x, y, w, h))
		{
			uiState.hotControl = id;
			if (uiState.activeControl == 0 && uiState.leftMouseDown)
				uiState.activeControl = id;
		}

		if (uiState.activeControl == id)
		{
			drawFilledRect(x + 1, y + 1, w - 2, h - 2, Colours::BACKGROUND_ACTIVE);
			drawRect(x, y, w, h, Colours::BORDER);

			if (hasText)
				textColour = Colours::FOREGROUND_ACTIVE;
		}
		else if (uiState.hotControl == id)
		{
			drawFilledRect(x + 1, y + 1, w - 2, h - 2, Colours::BACKGROUND_HOT);
			drawRect(x, y, w, h, Colours::BORDER);

			if (hasText)
				textColour = Colours::FOREGROUND_HOT;
		}
		else
		{
			drawFilledRect(x + 1, y + 1, w - 2, h - 2, Colours::BACKGROUND);
			drawRect(x, y, w, h, Colours::BORDER);

			if (hasText)
				textColour = Colours::FOREGROUND;
		}

		if (hasText)
		{
			SDL_Surface* surface = TTF_RenderText_Blended(font, text, textColour);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_Rect dstrect = { x + w / 2 - surface->w / 2, y + h / 2 - surface->h / 2, surface->w, surface->h };
			SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		}

		if (uiState.leftMouseDown == false &&
			uiState.hotControl == id &&
			uiState.activeControl == id)
			return true;

		return false;
	}

	bool slider(int id, int x, int y, int width, int height, int max, int& value, SliderType type = Vertical)
	{
		if (regionHit(x, y, width, height))
		{
			uiState.hotControl = id;
			if (uiState.activeControl == 0 && uiState.leftMouseDown)
				uiState.activeControl = id;
		}

		if (type == Vertical)
		{
			int boxHeight = (height - 2) / 8;
			int h = height - boxHeight;

			int yPos = (h - 2) * value / max;

			drawFilledRect(x + 1, y + 1, width - 2, height - 2, Colours::BACKGROUND_DARK);
			drawRect(x, y, width, height, Colours::BORDER);

			if (uiState.activeControl == id)
			{
				drawFilledRect(x + 1, y + 1 + yPos, width - 2, boxHeight, Colours::BACKGROUND_ACTIVE);
			}
			else if (uiState.hotControl == id)
			{
				drawFilledRect(x + 1, y + 1 + yPos, width - 2, boxHeight, Colours::BACKGROUND_HOT);
			}
			else
			{
				drawFilledRect(x + 1, y + 1 + yPos, width - 2, boxHeight, Colours::BACKGROUND);
			}

			if (uiState.activeControl == id)
			{
				int mousePos = uiState.mouseY - (y + boxHeight / 2);
				if (mousePos < 0) mousePos = 0;
				if (mousePos > h) mousePos = h;
				int v = roundf((float)mousePos * max / h);
				if (v != value)
				{
					value = v;
					return true;
				}
			}

			return false;
		}
		else
		{
			int boxWidth = (width - 2) / 8;
			int w = width - boxWidth;

			int xPos = (w - 2) * value / max;

			drawFilledRect(x + 1, y + 1, width - 2, height - 2, Colours::BACKGROUND_DARK);
			drawRect(x, y, width, height, Colours::BORDER);

			if (uiState.activeControl == id)
			{
				drawFilledRect(x + 1 + xPos, y + 1, boxWidth, height - 2, Colours::BACKGROUND_ACTIVE);
			}
			else if (uiState.hotControl == id)
			{
				drawFilledRect(x + 1 + xPos, y + 1, boxWidth, height - 2, Colours::BACKGROUND_HOT);
			}
			else
			{
				drawFilledRect(x + 1 + xPos, y + 1, boxWidth, height - 2, Colours::BACKGROUND);
			}

			if (uiState.activeControl == id)
			{
				int mousePos = uiState.mouseX - (x + boxWidth / 2);
				if (mousePos < 0) mousePos = 0;
				if (mousePos > w) mousePos = w;
				int v = roundf((float)mousePos * max / w);
				if (v != value)
				{
					value = v;
					return true;
				}
			}

			return false;
		}
	}

	bool slider(int id, int x, int y, int width, int height, int max, float& value, SliderType type = Vertical)
	{
		if (regionHit(x, y, width, height))
		{
			uiState.hotControl = id;
			if (uiState.activeControl == 0 && uiState.leftMouseDown)
				uiState.activeControl = id;
		}

		if (type == Vertical)
		{
			int boxHeight = (height - 2) / 8;
			int h = height - boxHeight;

			int yPos = (h - 2) * value / max;

			drawFilledRect(x + 1, y + 1, width - 2, height - 2, Colours::BACKGROUND_DARK);
			drawRect(x, y, width, height, Colours::BORDER);

			if (uiState.activeControl == id)
			{
				drawFilledRect(x + 1, y + 1 + yPos, width - 2, boxHeight, Colours::BACKGROUND_ACTIVE);
			}
			else if (uiState.hotControl == id)
			{
				drawFilledRect(x + 1, y + 1 + yPos, width - 2, boxHeight, Colours::BACKGROUND_HOT);
			}
			else
			{
				drawFilledRect(x + 1, y + 1 + yPos, width - 2, boxHeight, Colours::BACKGROUND);
			}

			if (uiState.activeControl == id)
			{
				int mousePos = uiState.mouseY - (y + boxHeight / 2);
				if (mousePos < 0) mousePos = 0;
				if (mousePos > h) mousePos = h;
				float v = (float)mousePos * max / h;
				if (v != value)
				{
					value = v;
					return true;
				}
			}

			return false;
		}
		else
		{
			int boxWidth = (width - 2) / 8;
			int w = width - boxWidth;

			int xPos = (w - 2) * value / max;

			drawFilledRect(x + 1, y + 1, width - 2, height - 2, Colours::BACKGROUND_DARK);
			drawRect(x, y, width, height, Colours::BORDER);

			if (uiState.activeControl == id)
			{
				drawFilledRect(x + 1 + xPos, y + 1, boxWidth, height - 2, Colours::BACKGROUND_ACTIVE);
			}
			else if (uiState.hotControl == id)
			{
				drawFilledRect(x + 1 + xPos, y + 1, boxWidth, height - 2, Colours::BACKGROUND_HOT);
			}
			else
			{
				drawFilledRect(x + 1 + xPos, y + 1, boxWidth, height - 2, Colours::BACKGROUND);
			}

			if (uiState.activeControl == id)
			{
				int mousePos = uiState.mouseX - (x + boxWidth / 2);
				if (mousePos < 0) mousePos = 0;
				if (mousePos > w) mousePos = w;
				float v = (float)mousePos * max / w;
				if (v != value)
				{
					value = v;
					return true;
				}
			}

			return false;
		}
	}

	void beginContextMenu(int width, int numOfItems, int itemHeight = 22)
	{
		uiState.contextMenuWidth = width;
		uiState.contextMenuHeight = numOfItems * itemHeight + 2;
		uiState.contextMenuItemHeight = itemHeight;

		if (uiState.lastRightMouse && !uiState.rightMouseDown && uiState.hotControl == 0 && uiState.activeControl == 0)
		{
			uiState.contextMenu = true;
			uiState.contextMenuX = uiState.mouseX;
			uiState.contextMenuY = uiState.mouseY;
		}
		else if (uiState.leftMouseDown && uiState.contextMenu && !regionHit(uiState.contextMenuX, uiState.contextMenuY, uiState.contextMenuWidth, uiState.contextMenuHeight) && uiState.activeControl == 0)
		{
			uiState.contextMenu = false;
		}

		if (uiState.contextMenu)
		{
			drawRect(uiState.contextMenuX, uiState.contextMenuY, uiState.contextMenuWidth, uiState.contextMenuHeight, Colours::BORDER);
			drawFilledRect(uiState.contextMenuX + 1, uiState.contextMenuY + 1, uiState.contextMenuWidth - 2, uiState.contextMenuHeight - 2, Colours::BACKGROUND);
		}
	}

	void endContextMenu()
	{
		uiState.contextMenuLevel = 0;
	}

	bool contextMenuItem(int id, const char* text = "", TTF_Font* font = nullptr)
	{
		if (uiState.contextMenu)
		{
			bool hasText = false;
			SDL_Color textColour;

			if (text != "" && font != nullptr)
				hasText = true;

			if (regionHit(uiState.contextMenuX + 1, uiState.contextMenuY + 1 + uiState.contextMenuLevel * uiState.contextMenuItemHeight, uiState.contextMenuWidth - 2, uiState.contextMenuItemHeight))
			{
				uiState.hotControl = id;
				if (uiState.activeControl == 0 && uiState.leftMouseDown)
					uiState.activeControl = id;
			}

			if (uiState.activeControl == id)
			{
				drawFilledRect(uiState.contextMenuX + 1, uiState.contextMenuY + 1 + uiState.contextMenuLevel * uiState.contextMenuItemHeight, uiState.contextMenuWidth - 2, uiState.contextMenuItemHeight, Colours::BACKGROUND_ACTIVE);

				if (hasText)
					textColour = Colours::FOREGROUND_ACTIVE;
			}
			else if (uiState.hotControl == id)
			{
				drawFilledRect(uiState.contextMenuX + 1, uiState.contextMenuY + 1 + uiState.contextMenuLevel * uiState.contextMenuItemHeight, uiState.contextMenuWidth - 2, uiState.contextMenuItemHeight, Colours::BACKGROUND_HOT);

				if (hasText)
					textColour = Colours::FOREGROUND_HOT;
			}
			else
			{
				drawFilledRect(uiState.contextMenuX + 1, uiState.contextMenuY + 1 + uiState.contextMenuLevel * uiState.contextMenuItemHeight, uiState.contextMenuWidth - 2, uiState.contextMenuItemHeight, Colours::BACKGROUND);

				if (hasText)
					textColour = Colours::FOREGROUND;
			}

			if (hasText)
			{
				SDL_Surface* surface = TTF_RenderText_Blended(font, text, textColour);
				SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_Rect dstrect = { uiState.contextMenuX + 5, uiState.contextMenuY + 1 + uiState.contextMenuLevel * uiState.contextMenuItemHeight + uiState.contextMenuItemHeight / 2 - surface->h / 2, surface->w, surface->h };
				SDL_RenderCopy(renderer, texture, NULL, &dstrect);
			}

			uiState.contextMenuLevel++;

			if (uiState.leftMouseDown == false &&
				uiState.hotControl == id &&
				uiState.activeControl == id)
			{
				uiState.contextMenu = false;
				return true;
			}

			return false;
		}
		return false;
	}

	void begin()
	{
		uiState.hotControl = 0;
	}

	void end()
	{
		uiState.lastRightMouse = uiState.rightMouseDown;

		if (!uiState.leftMouseDown)
		{
			uiState.activeControl = 0;
		}
		else
		{
			if (uiState.activeControl == 0)
				uiState.activeControl = -1;
		}
	}

	void setup(SDL_Renderer* _renderer)
	{
		renderer = _renderer;
	}
};

