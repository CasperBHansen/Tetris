/*
 * Tetris
 *
 * Game.h
 *
 */

#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>

#include "GraphicsEngine.h"
#include "Board.h"

/*!
 * ...
 */
class Game
{
public:
	//! Constructor.
	/*!
	 * Constructs an instance of the Game class.
	 */
	Game();
	~Game();
	
	int run();

protected:
	void onEvent(SDL_Event * event);
	
	int onUpdate();
	int onRender();
	
private:
	bool running;
	bool drop;
	int speed;
	
	GraphicsEngine * gfxEngine;
	Board * board;
};

#endif // GAME_H

