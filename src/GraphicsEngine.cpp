/*
 * Tetris
 *
 * GraphicsEngine.cpp
 *
 */

#include "GraphicsEngine.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

using std::vector;

const char * WIN_TITLE = "Tetris";


GraphicsEngine::GraphicsEngine(int width, int height)
{
	this->width  = width;
	this->height = height;
}

GraphicsEngine::~GraphicsEngine()
{
	for (vector<Sprite *>::iterator it = sprites.begin();
		 it != sprites.end(); ++it)
		delete (* it);
}

int GraphicsEngine::init()
{
	if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0 ) {
		cerr << "Unable to initialize SDL: " << SDL_GetError() << endl;
		return 1;
	}
	
	if ( (surface = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE|SDL_DOUBLEBUF)) == NULL) {
		cerr << "Unable to set video display mode: " << SDL_GetError() << endl;
		return 2;
	}
	
	SDL_WM_SetCaption(WIN_TITLE, 0);
	atexit( SDL_Quit );
	
	return 0;
}

void GraphicsEngine::drawSprite(int handle, SDL_Rect dst)
{
	// TOOD: optimize this
	for (vector<Sprite *>::iterator it = sprites.begin(); it != sprites.end(); ++it)
		if ( (*it)->getHandle() == handle )
			(* it)->draw(surface, dst);
}

void GraphicsEngine::swapBuffer()
{
	SDL_Flip(surface);
	SDL_FillRect(surface, NULL, 0x0);
}

int GraphicsEngine::addSprite(Sprite * sprite)
{
	sprites.push_back(sprite);
	cout << "Created sprite with handle " << sprite->getHandle() << '.' << endl;
	return sprite->getHandle();
}

void GraphicsEngine::removeSprite(int handle)
{
	for (vector<Sprite *>::iterator it = sprites.begin(); it != sprites.end(); ++it)
		if ( (*it)->getHandle() == handle ) {
			delete (* it);
			sprites.erase(it);
			break;
		}
}

