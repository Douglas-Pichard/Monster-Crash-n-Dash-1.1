#pragma once
#include <SDL.h>
//Everything neccessary to make the animation side of the sprites function
class Animation
{
public:
	int numberOfFrames;
	int frameWidth, frameHeight;
	float frameDuration;
	SDL_Texture* spriteSheet;
	SDL_Renderer* renderer;


	int currentFrame;
	float frameTimer;


	Animation(SDL_Texture* spriteSheet, SDL_Renderer* renderer, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration);

	void update(float dt);
	void draw(int x, int y);
	void draw(int x, int y, float scale);
	void draw(int x, int y, bool flip);
};

