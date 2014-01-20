/*
 * Tetris
 *
 * Game.cpp
 *
 */

#include "Game.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

int WIN_WIDTH  = 800;
int WIN_HEIGHT = 600;

Game::Game()
{
	running = true;
	speed = 1000;
	
	gfxEngine = new GraphicsEngine(WIN_WIDTH, WIN_HEIGHT);
	
	SDL_Rect src;
	src.x = 0; src.w = 32;
	src.y = 0; src.h = 32;
	
	Sprite * yellowTile = new Sprite("resources/yellow_tile.bmp", src);
	Sprite * greenTile = new Sprite("resources/green_tile.bmp", src);
	Sprite * blueTile = new Sprite("resources/blue_tile.bmp", src);
	Sprite * redTile = new Sprite("resources/red_tile.bmp", src);
	gfxEngine->addSprite(yellowTile);
	gfxEngine->addSprite(greenTile);
	gfxEngine->addSprite(blueTile);
	gfxEngine->addSprite(redTile);
}

Game::~Game()
{
	delete gfxEngine;
}

int Game::run()
{
	if ( gfxEngine->init() != 0 )
		return 1;
	
	board = new Board(10, 16, 32);
	
	while ( running ) {
		
		SDL_Event event;
		while ( SDL_PollEvent(&event) ) {
			onEvent(&event);
		}
		
		onUpdate();
		onRender();
	}
	
	cout << "Game over!" << endl;
	cout << "Score: " << board->getScore() << endl;
	
	delete board;
	
	return 0;
}

int Game::onUpdate()
{
	static int tick = 0;
	static int last = 0;
	
	tick = SDL_GetTicks();
	
	if (!board->update())
		running = false;
	
	if ( (tick - last) > (drop ? speed/100 : speed) ) {
		if (drop)
			drop = board->moveBlock(DIR_DOWN);
		else
			if (!board->moveBlock(DIR_DOWN))
				speed -= 1;
		
		last = tick;
	}
	
	return 0;
}

int Game::onRender()
{
	board->render(gfxEngine);
	gfxEngine->swapBuffer();
	
	return 0;
}

void Game::onEvent(SDL_Event * event)
{
	switch (event->type) {
		
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
				
				case SDLK_LEFT:
					board->moveBlock(DIR_LEFT);
					break;
				
				case SDLK_RIGHT:
					board->moveBlock(DIR_RIGHT);
					break;
				
				case SDLK_UP:
					board->rotateBlock();
					break;
				
				case SDLK_DOWN:
					board->moveBlock(DIR_DOWN);
					break;
				
				case SDLK_SPACE:
					drop = true;
					break;
				
				case SDLK_ESCAPE:
					running = false;
					break;
				
				default:
					break;
			}
			break;
		
		case SDL_QUIT:
			running = false;
			break;
		
		default:
			break;
	}
}

