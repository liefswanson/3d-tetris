#pragma once

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include <GL/glew.h>

#include <cmath>
#include <cfloat>
#include <utility>
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
	GLfloat z;

	Piece(Board* board, GLfloat z);
	~Piece();

	void makePiece();
	void clear();

	void shuffleL();
	void shuffleR();

	void rotW();
	void rotC();

	bool canRotateWishershins();
	bool canRotateClockwise();

	bool canMove    (GLfloat x, GLfloat y);
	bool canRelocate(GLfloat x, GLfloat y);
	void applyMove();
	void discardMove();	

	bool properCanRelease();
	void properRelease();
	
	bool release();

	void render();

	void debug();

	
private:
	const static uint PIECE_SIZE = 5;
	const static uint TILES_PER_BLOCK = 4;

	static RangeMap pieceMap;
	
	glm::vec3 location;
	glm::vec3 checkLocation;

	Tile* piece[PIECE_SIZE][PIECE_SIZE] = {};
	Tile* check[PIECE_SIZE][PIECE_SIZE] = {};
	bool collideMatrix[PIECE_SIZE][PIECE_SIZE] = {};
	
	Tile* TileOrder[TILES_PER_BLOCK] = {};

	Board* board;

	uint shape;
	bool rotated;

	static uint randFruit();
	static uint randShape();
	
	void makeAt(uint row, uint col, uint order);
	void makeI();
	void makeL();
	void makeS();

	void rotWHelper();
	void rotCHelper();
	bool canRotateClockwiseHelper();
	bool canRotateWishershinsHelper();

	bool onBoard     (uint row, uint col);
	bool checkOnBoard(uint row, uint col);

	uint findTop();
	uint findLeft();
	uint findRight();
	uint findBottom();
	bool properCanReleaseAt(uint row, uint col);
	void properReleaseAt   (uint row, uint col);

	void generateCollisionMatrix();
	void clearCollisionMatrix();

	// deprecated as they do not follow the spec
	// they are also too complex
	bool canReleaseAt(uint row, uint col, uint top, uint left);
	void releaseAt   (uint row, uint col, uint top, uint left);
	GLfloat distTo   (uint row, uint col, uint top, uint left);

	// sync Piece to Check 
	void syncPiece();
	// sync Check to Piece
	void syncCheck();
};
