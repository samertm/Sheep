#include "sheep.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <cmath>
#include <list>
#include <limits>
#include <cstdlib>

sheep::sheep(void) : HEIGHT(64), WIDTH(64), SCREEN_HEIGHT(480), SCREEN_WIDTH(640), BOX(10)
{
	xShow = yShow = yVel = xVel = x = y = 0;
	
	SDL_Surface* loadedImage = NULL;
	
	loadedImage = IMG_Load("sheep.png");

	if (loadedImage != NULL)
	{
		image = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	//loadedImage = IMG_Load("xy.png");

	//	if (loadedImage != NULL)
	//{
	//	boxy = SDL_DisplayFormat(loadedImage);
	//	SDL_FreeSurface(loadedImage);
	//}

	//loadedImage = IMG_Load("goingbox.png");

	//if (loadedImage != NULL)
	//{
	//	goingbox = SDL_DisplayFormatAlpha(loadedImage);
	//	SDL_FreeSurface(loadedImage);
	//}
	hungry = scared = hopping = going = blitted = false;
	love = 50;
	hunger = 0;
	special = "";
}

sheep::sheep(int xx, int yy) : HEIGHT(64), WIDTH(64), SCREEN_HEIGHT(480), SCREEN_WIDTH(640), BOX(10)
{
	xShow = x = xx;
	yShow = y = yy;
	
	SDL_Surface* loadedImage = NULL;
	
	loadedImage = IMG_Load("sheep.png");

	if (loadedImage != NULL)
	{
		image = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	//loadedImage = IMG_Load("xy.png");

	//if (loadedImage != NULL)
	//{
	//	boxy = SDL_DisplayFormat(loadedImage);
	//	SDL_FreeSurface(loadedImage);
	//}

	//loadedImage = IMG_Load("goingbox.png");

	//if (loadedImage != NULL)
	//{
	//	goingbox = SDL_DisplayFormat(loadedImage);
	//	SDL_FreeSurface(loadedImage);
	//}

	hungry = scared = hopping = going = blitted = false;
	special = "";
}



void sheep::handle_input(const SDL_Event& event)
{
	int mousex = 0;
	int mousey = 0;
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			mousex = event.button.x;
			mousey = event.button.y;
			if ((mousex > x) && (mousex < x + 38) && (mousey > y) && (mousey < y + 40))
				hungry = scared = scared ? false : true;
			else
			{
				foodX = mousex;
				foodY = mousey;
			}
		}
	}
}


void sheep::place_image(int x, int y, SDL_Surface* screen)
{
	xShow = sheep::x = x;
	yShow = sheep::y = y;
	
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(image, NULL, screen, &offset);
	blitted = true;
}

void sheep::show(SDL_Surface* screen)
{
	xShow = xShow >= 0 ? xShow : 0;
	yShow = yShow >= 0 ? yShow : 0;

	xShow = xShow <= (SCREEN_WIDTH - 38) ? xShow : (SCREEN_WIDTH - 38) ;
	yShow = yShow <= (SCREEN_HEIGHT - 40) ? yShow : (SCREEN_HEIGHT - 40) ;
	
	SDL_Rect offset;

	offset.x = xShow;
	offset.y = yShow;
	
	//SDL_Rect boxooo;
	//boxooo.x = x;
	//boxooo.y = y;

	//SDL_Rect going;
	//going.x = goingX;
	//going.y = goingY;

	SDL_BlitSurface(image, NULL, screen, &offset);
	//SDL_BlitSurface(boxy, NULL, screen, &boxooo);
	//SDL_BlitSurface(goingbox, NULL, screen, &going);
	
	
	blitted = true;
}

void sheep::think()
{
	//if (hunger < 25)
	//	hungry = true;

	//if (hungry)
	//{
	//	scared = true;
	//	if (foodcoords.size() != 0) // only works if there is food
	//	{
	//		std::list<point<int> >::const_iterator indexitr = foodcoords.begin();
	//		double distance = INT_MAX;
	//		
	//		// finds closest food to sheep
	//		for (std::list<point<int> >::const_iterator i = foodcoords.begin(); i != foodcoords.end(); i++)
	//		{
	//			int x = i->x;
	//			int y = i->y;
	//			double dis = sqrt(pow((x - sheep::x), 2.0) + pow((y - sheep::y), 2.0)); //distance formula
	//			if (dis < distance)
	//			{
	//				distance = dis;
	//				indexitr = i;
	//			}
	//		}

	//		foodX = indexitr->x;
	//		foodY = indexitr->y;
	//		sheep::go(foodX, foodY); // goes to food
	//	}
	//}
	//else
	{
		// one in random_int chance of moving
		int random_int = (rand()%100);

		if (random_int == 15)
		{
			int potential_x;
			int potential_y;

			//50% chance of adding or subtracting from coordinatees
			if (rand()%2)
			{
				potential_x = x + rand()%50;
				potential_y = y + rand()%50;
			} else {
				potential_x = x - rand()%50;
				potential_y = y - rand()%50;
			}

			//makes sure that the lamb isn't walking into oblivion
			int rand_x = potential_x > 0 && potential_x < SCREEN_WIDTH - 38? potential_x : x; // implementation specific to SCREEN_WIDTH
			int rand_y = potential_y > 0 && potential_y < SCREEN_HEIGHT - 40? potential_y : y; // implementation specific to SCREEN_HEIGHT
		
			//checks corner/wall cases (so they dont' get stuck)
			if (rand_x < 20)
				rand_x += 30;
			if (rand_x > SCREEN_WIDTH - 60)
				rand_x -= 30;
			if (rand_y < 20)
				rand_y += 30;
			if (rand_y > SCREEN_HEIGHT - 60) // TODO doesn't work for some reason
				rand_y -= 30;
		
			sheep::go(rand_x, rand_y);
			xShow = x;
			yShow = y;
		}
	}

	// randomly makes sheep hungry
	int random_hunger = rand()%8;
	if (random_hunger == false)
		hunger -= 1;
}

void sheep::move()
{
	if (going)
	{
		if (x > goingX && x > goingX) //gives x a range of values to hit, range is goingX plus or minus xVel
			xShow = x -= xVel;
		if (x < goingX && x < goingX)
			xShow = x += xVel;
		if (y > goingY && y > goingY)
			y -= yVel;
		if (y < goingY && y < goingY )
			y += yVel;
		if (x >= goingX && x <= goingX + BOX && y >= goingY && y <= goingY + BOX) // if all the previous values are true
		{
			going = false;
			x = xShow;
			y = yShow;
		}


		if (yShow <= y)
			up = true;
		if (yShow > y + 4)
			up = false;

		if (up)
			yShow += yVel;
		else
			yShow -= yVel;
	} else if (scared)
	{

		yVel = 3;
		if (yShow <= y)
			up = true;
		if (yShow > y + 4)
			up = false;

		if (up)
			yShow += yVel;
		else
			yShow -= yVel;
	}
}

void sheep::go(int goX, int goY)
{
	goingX = goX;
	goingY = goY;
	yVel = 3;
	xVel = 3;
	going = true;
}


sheep::~sheep(void)
{
	SDL_FreeSurface(image);
}
