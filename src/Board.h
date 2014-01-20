/*
 * Tetris
 *
 * Board.h
 *
 */

#ifndef BOARD_H
#define BOARD_H

#include "GraphicsEngine.h"

typedef enum {
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN
} Direction;

typedef struct {
	struct {
		int x, y;
	} position;
	int rotation, type, color;
	int cells[4][4][4];
} Block;

typedef enum {
	BLK_CUBE,
	BLK_PIPE,
	BLK_STAIR,
	BLK_STAIR_INV,
	BLK_L,
	BLK_L_INV,
	BLK_T,
} BlockType;

/*!
 * ...
 */
class Board
{
public:
	//! Constructor.
	/*!
	 * Constructs an instance of the Board class.
	 */
	Board(int width, int height, int tileSize);
	~Board();
	
	int init();
	
	int getWidth() const;
	int getHeight() const;
	
	int getScore() const;
	
	bool moveBlock(Direction direction);
	bool rotateBlock();
	
	bool update();
	void render(GraphicsEngine * gfx);

protected:
	int removeRow(int i);
	
	void newBlock();
	void putBlock();
	
private:
	int width, height;
	int tileSize;
	int ** board;
	Block block;
	int score;
	bool alive;
	
	bool isEmpty(int x, int y);
	bool isValid(int r, int x, int y);
};

#endif // BOARD_H

