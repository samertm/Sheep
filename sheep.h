#pragma once
#include "SDL/SDL.h"
#include <string>
#include <list>
class sheep
{
public:
	sheep(void);
	sheep(int, int);
	void move();
	void place_image(int, int, SDL_Surface*);
	void show(SDL_Surface*);
	void showbox(SDL_Surface*);
	void handle_input(const SDL_Event&);
	void go(int, int);
	void think();
	~sheep(void);
	int x, y, xVel, yVel, xShow, yShow, hunger, love;
private:
	int basey, hops, goingX, goingY, foodX, foodY;
	const int HEIGHT, WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, BOX;
	SDL_Surface* image;
	SDL_Surface* boxy;
	SDL_Surface* goingbox;
	bool blitted, hopping, going, up, scared, hungry;
	std::string special;
};

