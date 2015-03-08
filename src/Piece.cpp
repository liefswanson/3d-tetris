#include "Piece.hpp"


Piece::Piece(Board* board){
	srand(time(NULL));
	this->board = board;
}

Piece::~Piece(){
}


// GLboolean
// Block::canRotW(){
// 	if (shape == I_piece ||
// 		shape == S_piece) {
// 		if (rotation == 0) {
// 			rotation = 1;
// 		} else if (rotation == 1) {
// 			rotation = 0;
// 			for(GLuint row = 0; row < PIECE_SIZE; ++row) {
// 				for(GLuint col = 0; col < PIECE_SIZE; ++col) {
// 					check[row][col] = piece[PIECE_SIZE -1 -col][row];
// 				}
// 			}
// 			return checkMove();
// 		}
// 	}
// 	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
// 		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
// 			check[row][col] = piece[col][PIECE_SIZE -1 -row];
// 		}
// 	}
// 	return checkMove();
// }

// GLboolean
// Block::canRotC(){
// 	if (shape == I_piece ||
// 		shape == S_piece) {
// 		if (rotation == 0) {
// 			rotation = 1;
// 			for(GLuint row = 0; row < PIECE_SIZE; ++row) {
// 				for(GLuint col = 0; col < PIECE_SIZE; ++col) {
// 					check[row][col] = piece[col][PIECE_SIZE -1 -row];
// 				}
// 			}
// 			return checkMove();
// 		} else if (rotation == 1) {
// 			rotation = 0;
// 		}
// 	} else {
// 		if (rotation < 4) {
// 			++rotation;
// 		} else {
// 			rotation = 0;
// 		}
// 	}
// 	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
// 		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
// 			check[row][col] = piece[PIECE_SIZE -1 -col][row];
// 		}
// 	}
// 	return checkMove();
// }

void
Piece::shuffleL() {
	//uses a single bubble ->
	for(GLuint i = 0; i < TILES_PER_BLOCK-1; ++i) {
		std::swap(*TileOrder[i], *TileOrder[i +1]);
	}
}

void
Piece::shuffleR(){
	//uses a single bubble <-
	for(GLuint i = TILES_PER_BLOCK-1; i > 0 ; --i) {
	 	std::swap(*TileOrder[i],*TileOrder[i -1]);
	}
}

// TODO set location somehow
void
Piece::makePiece(GLfloat x, GLfloat y){
	this->clear();
	shape    = randShape();
	rotation = 0;
	switch(shape) {
	case I_PIECE:
		makeI();
		break;
	case L_PIECE:
		makeL();
		break;
	case S_PIECE:
		makeS();
		break;
	}

	syncCheck();
	
	GLuint rotations = rand() % 4;
	for(GLuint i = 0; i < rotations; ++i) {
		rotW();
	}
}



void
Piece::syncPiece(){
	for(uint row = 0; row < PIECE_SIZE; ++row) {
		for(uint col = 0; col < PIECE_SIZE; ++col) {
			piece[row][col] = check[row][col];
		}
	}
	location = checkLocation;
}

void
Piece::syncCheck(){
	for(uint row = 0; row < PIECE_SIZE; ++row) {
		for(uint col = 0; col < PIECE_SIZE; ++col) {
			check[row][col] = piece[row][col] ;
		}
	}
	checkLocation = location;
}

void
Piece::makeAt(uint row, uint col, uint order){
	piece[row][col]  = new Tile(randFruit());
	TileOrder[order] = piece[row][col];
}

uint
Piece::randFruit() {
	return rand() % FRUITS;
}

uint
Piece::randShape() {
	return rand() % SHAPES;
}


void
Piece::makeI(){
    //-----
	//-----
	//++++-
	//-----
	//------
    //2, 0..3

	makeAt(2, 0, 0);
	makeAt(2, 1, 1);
	makeAt(2, 2, 2);
	makeAt(2, 3, 3);
}


void
Piece::makeL(){
	//-----
	//-----
	//-+++-
	//-+---
	//-----
    //3, 1
	//2, 1..3
	
	makeAt(3, 1, 0);
	makeAt(2, 1, 1);
	makeAt(2, 2, 2);
	makeAt(2, 3, 3);
}

void
Piece::makeS(){
	//-----
	//-----
	//--++-
	//-++--
	//----- 
    //1..2, 3
	//2..3, 2

	makeAt(3, 1, 0);
	makeAt(3, 2, 1);
	makeAt(2, 2, 2);
	makeAt(2, 3, 3);
}
