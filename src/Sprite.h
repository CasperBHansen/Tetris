/*
 * Tetris
 *
 * Sprite.h
 *
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL/SDL.h>

#include "Resource.h"

/*!
 * ...
 */
class Sprite : public Resource
{
public:
	//! Constructor.
	/*!
	 * Constructs an instance of the Sprite class.
	 */
	Sprite(const char * filename, SDL_Rect src);
	~Sprite();
	
	virtual int load();
	virtual void release();
	
	void draw(SDL_Surface * surface, SDL_Rect dst);

protected:
private:
	SDL_Surface * sprite;
	SDL_Rect src;
};

#endif // SPRITE_H

