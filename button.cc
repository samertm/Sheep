#include "button.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

button::button(int x, int y) : WIDTH(160), HEIGHT(120), MOUSECLIPOVER(0), MOUSECLIPOUT(1), MOUSECLIPDOWN(2), MOUSECLIPUP(3)
{
	box.x = x;
	box.y = y;
	box.w = WIDTH;
	box.h = HEIGHT;

	SDL_Surface* loadedImage = NULL;

	loadedImage = IMG_Load("button.png");

	if (loadedImage != NULL)
	{
		buttonSheet = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	button::set_clips();

	clicked = false;

	clip = &clips[MOUSECLIPOUT];
}

void button::set_clips()
{
	SDL_Rect out, over, down, up;
	out.x = 0;
	out.y = 0;
	out.w = 160;
	out.h = 120;

	over.x = 160;
	over.y = 0;
	over.w = 160;
	over.h = 120;

	down.x = 0;
	down.y = 120;
	down.w = 160;
	down.h = 120;

	up.x = 160;
	up.y = 120;
	up.w = 160;
	up.h = 120;

	clips.push_back(over);
	clips.push_back(out);
	clips.push_back(down);
	clips.push_back(up);
}

void button::handle_events(SDL_Event event)
{
	int x = 0; int y = 0;

	if (event.type == SDL_MOUSEMOTION)
	{
		x = event.motion.x;
		y = event.motion.y;

		if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
			clip = &clips[MOUSECLIPOVER];
		else
			clip = &clips[MOUSECLIPOUT];
	}

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			x = event.button.x;
			y = event.button.y;

			if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
				clip = &clips[MOUSECLIPDOWN];
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			x = event.button.x;
			y = event.button.y;

			if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
			{
				clip = &clips[MOUSECLIPUP];
				clicked = true;
			}
		}
	}
}

void button::show(SDL_Surface* screen)
{
	SDL_Rect offset;

	offset.x = box.x;
	offset.y = box.y;

	SDL_BlitSurface(buttonSheet, clip, screen, &offset);
}


button::~button(void)
{
}
