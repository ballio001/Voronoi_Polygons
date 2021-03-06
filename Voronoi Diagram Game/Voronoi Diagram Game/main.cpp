// Voronoi Diagram Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <SDL.h>
#include "MyBitmap.h"
#include "Voronoi.h"

//Screen dimension constants
const int SCREEN_WIDTH = 740;
const int SCREEN_HEIGHT = 550;

bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gImageSurface = NULL;

SDL_Rect sourceRect;
SDL_Rect destRect;
//InputHandler * handler = new InputHandler();

int m_count = 0;

bool init()
{
	//Initialization flag
	bool success = true;
	//where on the screen it is shown
	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = 0;
	sourceRect.y = 0;
	//how big the window is that the sprite is shown in
	destRect.x = 0;
	destRect.y = 0;
	destRect.w = 740;
	destRect.h = 550;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	gImageSurface = SDL_LoadBMP("v.bmp");
	if (gImageSurface == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded image
	SDL_FreeSurface(gImageSurface);
	gImageSurface = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

int main(int argc, char* args[])
{
	MyBitmap bmp;
	Voronoi v;

	srand(GetTickCount());

	bmp.Create(740, 550); //how big the bitmap is
	bmp.SetPenColor(0);
	v.Make(&bmp, 50);

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		// create the newbmp
		bmp.SaveBitmap("v.bmp");
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			SDL_Event e;
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_MOUSEBUTTONDOWN) {
						if (e.button.button == SDL_BUTTON_LEFT) {
							//bmp.~MyBitmap();
							cout << "left button pressed" << endl;
							v.GetPointsOnMousePosition();

							//adjusts the voronoi map
							bmp.SaveBitmap("v.bmp");
							gImageSurface = SDL_LoadBMP("v.bmp");
							cout << "points added!" << endl;
							isClicked = false;
						}
					}
				}
				//BitBlt(GetDC(GetConsoleWindow()), 20, 20, 512, 512, bmp.hdc(), 0, 0, SRCCOPY); //shows it in the cmd
				//Apply the image
				SDL_BlitSurface(gImageSurface, &destRect, gScreenSurface, &sourceRect);

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);

			}
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}