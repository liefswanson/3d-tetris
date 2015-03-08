#pragma once

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include <GL/glew.h>

#include <cmath>
#include "Board.hpp"
#include "Settings.hpp"

enum Shapes {
	I_PIECE = 0,
	L_PIECE,
	S_PIECE,
	SHAPES
};

class Piece {
public:

	Piece(Board* board);
	~Piece();

	void makePiece(GLfloat x, GLfloat y);

	void shuffleL();
	void shuffleR();

	// FIXME not sure which to use,
	// but if i make the location piece center it shouldnt be needed? 
	bool canRotW();
	bool canRotC();

	void rotW();
	void rotC();
	
	bool canMove(GLfloat x, GLfloat y);
	void applyMove();
	void discardMove();	

	void release();

	void render();

	
private:
	const static uint PIECE_SIZE = 5;
	const static uint TILES_PER_BLOCK = 4;
	
	glm::vec3 location;
	glm::vec3 checkLocation;

	GLfloat top,  bottom,
		    left, right;

	Tile* piece[PIECE_SIZE][PIECE_SIZE] = {};
	Tile* check[PIECE_SIZE][PIECE_SIZE] = {};

	Tile* TileOrder[TILES_PER_BLOCK] = {};

	Board* board;

	uint shape;
	uint rotation;

	static uint randFruit();
	static uint randShape();
	
	void makeAt(uint row, uint col, uint order);
	void makeI();
	void makeL();
	void makeS();

	// sync Piece to Check 
	void syncPiece();
	// sync Check to Piece
	void syncCheck();

	void clear();
};
