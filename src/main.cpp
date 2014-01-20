/*
 * main.cpp - Tetris
 *
 * The main program file.
 */

#include <iostream>

#include "Game.h"

int main(int argc, char * argv[]) {
	
	Game game = Game();
	return game.run();
}
