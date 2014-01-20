/*
 * Tetris
 *
 * Sprite.cpp
 *
 */

#include "Sprite.h"

#include <iostream>
using std::cerr;
using std::endl;

Sprite::Sprite(const char * filename, SDL_Rect src)
	: Resource(filename)
{
	this->src = src;
	load();
}

Sprite::~Sprite()
{
	release();
}

int Sprite::load()
{
	if ( (this->sprite = SDL_LoadBMP(resource)) == NULL ) {
		cerr << "Couldn't load resource '" << resource << "': " << SDL_GetError() << endl;
		return 1;
	}
	
	return 0;
}

void Sprite::release()
{
	SDL_FreeSurface(sprite);
}

void Sprite::draw(SDL_Surface * surface, SDL_Rect dst)
{
	SDL_BlitSurface(sprite, &src, surface, &dst);
}

