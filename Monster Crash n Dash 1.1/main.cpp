#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "Animation.h"

using namespace std;

int main(int argc, char **argv)
{
	//initialise SDL and its subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "ERROR: " << SDL_GetError() << endl;
		system("pause");
		return -1;
	}
	else
	{
		cout << "SDL initialised!!!" << endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)))
	{

		cout << "SDL IMAGE ERROR: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	if (TTF_Init() != 0)
	{

		cout << "TTF FAILED: " << TTF_GetError() << endl;
		system("pause");
		SDL_Quit();
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Monster Crash n Dash!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1000, 600, SDL_WINDOW_SHOWN);//Decided to make the window a little smaller for now

	if (window != NULL) {
		cout << "window created!" << endl;
	}
	else
	{
		cout << "ERROR: " << SDL_GetError() << endl;
		system("pause");
		SDL_Quit();
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL) {
		cout << "ERROR: " << SDL_GetError() << endl;
		system("pause");
		SDL_Quit();
		return -1;
	}



	//Used these to include three seprate sprite sheets
	SDL_Texture* eyeSpriteSheet = IMG_LoadTexture(renderer, "assets/eye.png");
	SDL_Texture* essieSpriteSheet = IMG_LoadTexture(renderer, "assets/essie.png");
	SDL_Texture* snekSpriteSheet = IMG_LoadTexture(renderer, "assets/snek.png");
	//Used these to display sprites frames, how much of the sprite is being drawn and how fast they move
	Animation anim1(eyeSpriteSheet, renderer, 2, 65, 70, 0.2);
	Animation anim2(essieSpriteSheet, renderer, 2, 70, 70, 0.2);
	Animation anim3(snekSpriteSheet, renderer, 2, 65, 60, 0.2);


	//Used this to load up font file (used Vermin from class since it just looks awesome) and set it to 70 size
	TTF_Font* font1 = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 70);
	SDL_Color textColour = { 123, 0, 34, 0 };//keeping it dark red (good monster colour)
											 //The rest is to convert surface to texture and clean it up
	SDL_Surface* textSurface = TTF_RenderText_Blended(font1, "Monster Crash n Dash!", textColour);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	//Now setting its location on screen
	SDL_Rect textDest;
	textDest.x = 150;
	textDest.y = 40;
	SDL_QueryTexture(textTexture, NULL, NULL, &textDest.w, &textDest.h);

	SDL_Surface* textSurface1 = TTF_RenderText_Blended(font1, "Press Start", textColour);
	SDL_Texture* textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
	SDL_FreeSurface(textSurface1);
	//Now setting its location on screen
	SDL_Rect textDest1;
	textDest1.x = 300;
	textDest1.y = 400;
	SDL_QueryTexture(textTexture1, NULL, NULL, &textDest1.w, &textDest1.h);


	//NOTE::Couldn't figure out how to make more then one text on screen at the same time yet.
	//Will adjust for version 2.

	//Need this to manage everything time related
	Uint32 lastUpdate = SDL_GetTicks();
	bool loop = true;
	while (loop) {
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		float DT = timeDiff / 1000.0;
		lastUpdate = SDL_GetTicks();

		//Setting background colour to white as it makes the shadows under the monsters 'Pop' out a bit	
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		//Used this to position monsters on screen and space them out. Snek needed a slight scale up
		//to match the other two. Might replace him in a later version pending
		anim1.update(DT);
		anim2.update(DT);
		anim3.update(DT);
		anim1.draw(50, 200, 2.0f);
		anim2.draw(400, 200, 2.0f);
		anim3.draw(750, 200, 3.5f);


		//Used this to stop the game window from locking up and can now exit by just pressing escape
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) {
				loop = false;
			}
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					loop = false;
				}
			}
		}
		//These make sure the text actually shows up
		SDL_RenderCopy(renderer, textTexture, NULL, &textDest);
		SDL_RenderCopy(renderer, textTexture1, NULL, &textDest1);

		SDL_RenderPresent(renderer);


	}
	//Finally destroy everything!
	TTF_CloseFont(font1);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(textTexture1);
	SDL_DestroyTexture(eyeSpriteSheet);
	SDL_DestroyTexture(essieSpriteSheet);
	SDL_DestroyTexture(snekSpriteSheet);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	system("pause");
	return 0;

	//The end for now!
}