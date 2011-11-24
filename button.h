#pragma once
#include "SDL/SDL.h"
#include <vector>
class button
{
public:
	button(int, int);
	void handle_events(SDL_Event);
	void set_clips();
	void show(SDL_Surface*);
	~button(void);
	std::vector<SDL_Rect> clips;
	bool clicked;
private:
	const int WIDTH, HEIGHT, MOUSECLIPOVER, MOUSECLIPOUT, MOUSECLIPDOWN, MOUSECLIPUP;
	SDL_Rect box;
	SDL_Surface* buttonSheet;
	SDL_Rect* clip;
};

