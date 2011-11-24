#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "sheep.h"
#include "timer.h"
#include <string>
#include <list>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "button.h"
#include "point.h"

const int kNumLambs = 30;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int FRAMES_PER_SECOND = 20;

SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

//std::list<point<int>> food;

SDL_Event event;

TTF_Font *font = NULL;

SDL_Color textColor = { 255, 255, 255 };

using std::vector;			using std::list;

SDL_Surface *load_image(std::string filename)
{
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;
	
	loadedImage = IMG_Load(filename.c_str());

	if (loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, destination, &offset);
}

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if (screen == NULL)
	{
		return false;
	}

	if (TTF_Init() == -1)
	{
		return false;
	}

	SDL_WM_SetCaption("Moving Sheep", NULL);
	
	return true;
}

bool load_files()
{
	background = load_image("background.png");

	font = TTF_OpenFont("OCRAExt.TTF", 28);

	if (background == NULL)
	{
		return false;
	}

	if (font == NULL)
	{
		return false;
	}

	return true;
}

void clean_up()
{
	SDL_FreeSurface( background );
	SDL_FreeSurface( message);

	TTF_CloseFont(font);

	TTF_Quit();

	SDL_Quit();
}




int main( int argc, char* args[] )
{
	bool quit = false;
	srand((unsigned)time(0));

	if (init() == false)
	{
		return 1;
	}

	if (load_files() == false)
	{
		return 2;
	}



	sheep lambs[kNumLambs];

	for (int i = 0; i != kNumLambs; i++)
		lambs[i].place_image(rand()%640, rand()%480, screen);
	
	apply_surface(0, 0, background, screen);

	timer fps;

	message = TTF_RenderText_Solid(font, "Welcome to Sheep Fields", textColor);
	
	button start(200, 200);
	

	while (quit == false)
	{
		fps.start();
		
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = true;

			start.handle_events(event);
			for (int i = 0; i != kNumLambs; i++)
				lambs[i].handle_input(event);
		}

		apply_surface(0, 0, background, screen);

		if (!start.clicked)
		{
			apply_surface(150, 150, message, screen);

			start.show(screen);
		} else {

			for (int i = 0; i != kNumLambs; i++)
				lambs[i].think();

			for (int i = 0; i != kNumLambs; i++)
				lambs[i].move();

			for (int i = 0; i != kNumLambs; i++)
				lambs[i].show(screen);
		}

		if (SDL_Flip(screen) == -1)
			return 1;

		        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
	}
	

	clean_up();

    return 0;    
}
