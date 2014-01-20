/*
 * Tetris
 *
 * GraphicsEngine.h
 *
 */

#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include <SDL/SDL.h>

#include <vector>

#include "Sprite.h"

/*!
 * ...
 */
class GraphicsEngine
{
public:
	//! Constructor.
	/*!
	 * Constructs an instance of the GraphicsEngine class.
	 */
	GraphicsEngine(int width, int height);
	~GraphicsEngine();
	
	int init();
	
	void drawSprite(int handle, SDL_Rect dst);
	
	void swapBuffer();
	
	int addSprite(Sprite * sprite);
	void removeSprite(int handle);

protected:
private:
	int width, height;
	SDL_Surface * surface;
	
	std::vector<Sprite *> sprites;
};

#endif // GRAPHICSENGINE_H

