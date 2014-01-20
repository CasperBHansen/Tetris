/*
 * Tetris
 *
 * Board.cpp
 *
 */

#include "Board.h"

#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

#include "Blocks.h"

Board::Board(int width, int height, int tileSize)
{
	this->width    = width;
	this->height   = height;
	this->tileSize = tileSize;
	
	init();
}

Board::~Board()
{
	for (int x = 0; x < width; ++x)
		free(board[x]);
	free(board);
}

int Board::init()
{
	if (width < 0 || height < 0)
		return 1;
	
	board = (int **)malloc(sizeof(int *) * width);
	for (int x = 0; x < width; ++x) {
		board[x] = (int *)malloc(sizeof(int) * height);
		for (int y = 0; y < height; ++y)
			board[x][y] = 0;
	}
	
	newBlock();
	
	alive = true;
	score = 0;
	
	return 0;
}

int Board::getWidth() const
{
	return width;
}

int Board::getHeight() const
{
	return height;
}

int Board::getScore() const
{
	return score;
}

void Board::newBlock()
{
	srand(SDL_GetTicks());
	block.type     = rand() % 7;
	block.rotation = rand() % 4;
	block.color    = rand() % 4 + 1;
	
	switch (block.type) {
		
		case BLK_CUBE:
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					for (int k = 0; k < 4; ++k)
						 block.cells[i][j][k] = cube[i][j][k];
			break;
		
		case BLK_PIPE:
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					for (int k = 0; k < 4; ++k)
						 block.cells[i][j][k] = pipe[i][j][k];
			break;
		
		case BLK_L:
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					for (int k = 0; k < 4; ++k)
						 block.cells[i][j][k] = l[i][j][k];
			break;
		
		case BLK_L_INV:
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					for (int k = 0; k < 4; ++k)
						 block.cells[i][j][k] = l_inv[i][j][k];
			break;
		
		case BLK_STAIR:
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					for (int k = 0; k < 4; ++k)
						 block.cells[i][j][k] = stair[i][j][k];
			break;
		
		case BLK_STAIR_INV:
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					for (int k = 0; k < 4; ++k)
						 block.cells[i][j][k] = stair_inv[i][j][k];
			break;
		
		case BLK_T:
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					for (int k = 0; k < 4; ++k)
						 block.cells[i][j][k] = t[i][j][k];
			break;
		
		default:
			break;
	}
	
	block.position.x = (width / 2) - 2;
	block.position.y = 0;
	
	if (!isValid(block.rotation, 0, 0))
		alive = false;
}

void Board::putBlock()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (block.cells[block.rotation][i][j] != 0)
				board[block.position.x + i][block.position.y + j] = block.color;
	
	newBlock();
}

bool Board::moveBlock(Direction direction)
{
	switch (direction) {
		
		case DIR_LEFT:
			if (isValid(block.rotation, -1, 0)) {
				block.position.x -= 1;
				return true;
			}
			break;
		
		case DIR_RIGHT:
			if (isValid(block.rotation, 1, 0)) {
				block.position.x += 1;
				return true;
			}
			break;
		
		case DIR_DOWN:
			if (isValid(block.rotation, 0, 1)) {
				block.position.y += 1;
				return true;
			}
			
			putBlock();
			break;
		
		default:
			break;
	}
	
	
	return false;
}

bool Board::rotateBlock()
{
	int rotation = (block.rotation + 1) % 4;
	if (isValid(rotation, 0, 0)) {
		block.rotation = rotation;
		return true;
	}
	return false;
}

bool Board::update()
{
	if (!alive)
		return false;
	
	int points = 0;
	int multiplier = 0;
	
	for (int y = 0; y < height; ++y) {
		bool full = true;
		for (int x = 0; x < width; ++x) {
			full &= (board[x][y] != 0);
		}
		
		if (full) {
			points += removeRow(y);
			multiplier += 1;
		}
	}
	
	if (points) {
		score += points;
		cout << "Score: " << score << endl;
	}
	
	return true;
}

int Board::removeRow(int i)
{
	int points = 0;
	for (int y = i; y > 0; --y)
		for (int x = 0; x < width; ++x) {
			points += board[x][y];
			board[x][y] = board[x][y-1];
		}

	return points;
}

void Board::render(GraphicsEngine * gfx)
{
/*
	SDL_Rect bgRect;
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.w = width * tileSize;
	bgRect.h = height * tileSize;
*/	
	SDL_Rect dst;
	dst.w = tileSize;
	dst.h = tileSize;
	
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (block.cells[block.rotation][i][j] != 0) {
				dst.x = (block.position.x + i) * tileSize;
				dst.y = (block.position.y + j) * tileSize;
				gfx->drawSprite(block.color, dst);
			}
	
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x) {
			dst.x = x * tileSize;
			dst.y = y * tileSize;
			gfx->drawSprite(board[x][y], dst);
		}
}

bool Board::isEmpty(int x, int y)
{
	// outside board
	if (x < 0 || x >= width ||
		y < 0 || y >= height )
		return false;
	
	// collide with another tile
	if (board[x][y] != 0)
		return false;
	
	return true;
}

bool Board::isValid(int r, int x, int y)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (block.cells[r][i][j] != 0 &&
				!isEmpty(block.position.x + i + x, block.position.y + j + y))
				return false;

	return true;
}

