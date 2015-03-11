#include "Piece.hpp"

RangeMap
Piece::pieceMap = RangeMap(0.f, (GLfloat) PIECE_SIZE-1, -(GLfloat)PIECE_SIZE/2, (GLfloat)PIECE_SIZE/2);

Piece::Piece(Board* board, GLfloat z){
	srand(time(NULL));
	this->board = board;
	location = glm::vec3(+10.f, +10.f, z);
}

Piece::~Piece(){
	for(uint row = 0; row < PIECE_SIZE; ++row) {
		for(uint col = 0; col < PIECE_SIZE; ++col) {
			if(piece[row][col] != NULL) {
				delete piece[row][col];
			}
		}
	}
}

bool
Piece::canRotateClockwise(){
	if (shape == I_PIECE ||
		shape == S_PIECE) {
		if (rotated) {
			rotCHelper();
		} else  {
			rotWHelper();
		}
		rotated = !rotated;
	} else {
		rotCHelper();
	}
	auto row = round(rowMap.mapBack(location.y));
	auto col = round(colMap.mapBack(location.x));
	return checkOnBoard(row, col);
}

bool
Piece::canRotateWishershins(){
	if (shape == I_PIECE ||
		shape == S_PIECE) {
		if (rotated) {
			rotWHelper();
		} else  {
			rotCHelper();
		}
		rotated = !rotated;
	} else {
		rotWHelper();
	}
	auto row = round(rowMap.mapBack(location.y));
	auto col = round(colMap.mapBack(location.x));
	return checkOnBoard(row, col);
}

void
Piece::rotW(){
	if (shape == I_PIECE ||
		shape == S_PIECE) {
		if (rotated) {
			rotWHelper();
		} else  {
			rotCHelper();
		}
		rotated = !rotated;
	} else {
		rotWHelper();
	}
	syncPiece();
}

void
Piece::rotC(){
	if (shape == I_PIECE ||
		shape == S_PIECE) {
		if (rotated) {
			rotCHelper();
		} else  {
			rotWHelper();
		}
		rotated = !rotated;
	} else {
		rotCHelper();
	}
	syncPiece();
}


void
Piece::rotCHelper(){
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			check[row][col] = piece[col][PIECE_SIZE -1 -row];
		}
	}
}

void
Piece::rotWHelper(){
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			check[row][col] = piece[PIECE_SIZE -1 -col][row];
		}
	}
}

void
Piece::shuffleL() {
	//uses a single bubble ->
	for(uint i = 0; i < TILES_PER_BLOCK-1; ++i) {
		std::swap(*TileOrder[i], *TileOrder[i +1]);
	}
}

void
Piece::shuffleR(){
	//uses a single bubble <-
	for(uint i = TILES_PER_BLOCK-1; i > 0 ; --i) {
	 	std::swap(*TileOrder[i],*TileOrder[i -1]);
	}
}

bool
Piece::canMove(GLfloat x, GLfloat y){
	checkLocation = glm::vec3(location.x + x,
							  location.y + y,
							  location.z);
	// std::cout << Term::INFO << location.x << ',' << location.y << ',' << location.z << std::endl;
	auto row = round(rowMap.mapBack(checkLocation.y));
	auto col = round(colMap.mapBack(checkLocation.x));
	return onBoard(row, col);

}

bool
Piece::canRelocate(GLfloat x, GLfloat y) {

	checkLocation = glm::vec3(x, y, location.z);
	// std::cout << Term::INFO << location.x << ',' << location.y << ',' << location.z << std::endl;
	auto row = round(rowMap.mapBack(checkLocation.y));
	auto col = round(colMap.mapBack(checkLocation.x));
	return onBoard(row, col);
}

uint
Piece::findTop(){
	for(uint row = 0; row < PIECE_SIZE; row++){
		for(uint col = 0; col < PIECE_SIZE; col++) {
			if(piece[row][col] != NULL){
				return row;
			}
		}
	}
	return PIECE_SIZE;
}

uint
Piece::findBottom(){
	for(int row = PIECE_SIZE -1; row >= 0; row--){
		for(uint col = 0; col < PIECE_SIZE; col++) {
			if(piece[row][col] != NULL){
				return row;
			}
		}
	}
	return PIECE_SIZE;
}

uint
Piece::findLeft(){
	for(uint col = 0; col < PIECE_SIZE; col++) {
		for(uint row = 0; row < PIECE_SIZE; row++){
			if(piece[row][col] != NULL){
				return col;
			}
		}
	}
	return PIECE_SIZE;
}

uint
Piece::findRight(){
	for(int col = PIECE_SIZE -1; col >= 0; col--) {
		for(uint row = 0; row < PIECE_SIZE; row++){
			if(piece[row][col] != NULL){
				return col;
			}
		}
	}
	return PIECE_SIZE;
}

void
Piece::applyMove(){
	syncPiece();
}

void
Piece::discardMove(){
	syncCheck();
}


bool
Piece::properCanRelease(){
	auto drow = round(rowMap.mapBack(location.y));
	auto dcol = round(colMap.mapBack(location.x));
	return properCanReleaseAt(drow,dcol);
}

bool
Piece::properCanReleaseAt(uint row, uint col){
	for(uint prow = 0; prow < PIECE_SIZE; prow++ ){
		for(uint pcol = 0; pcol < PIECE_SIZE; pcol++) {
			if(!board->on(row +prow, col +pcol) ||
			   board->at(row +prow, col +pcol) != NULL){
				if(piece[prow][pcol] != NULL){
					return false;
				}
			}
		}
	}
	return true;
}

bool
Piece::onBoard(uint row, uint col){
	for(uint prow = 0; prow < PIECE_SIZE; prow++ ){
		for(uint pcol = 0; pcol < PIECE_SIZE; pcol++) {
			if(piece[prow][pcol] != NULL &&
			   (!board->on(row +prow, col +pcol) || row < board->SpawnRows())){
				return false;
			}
		}
	}
	return true;
}

// this one is almost entirely a rotate helper function
bool
Piece::checkOnBoard(uint row, uint col) {
	for(uint prow = 0; prow < PIECE_SIZE; prow++ ){
		for(uint pcol = 0; pcol < PIECE_SIZE; pcol++) {
			if(check[prow][pcol] != NULL &&
			   (!board->on(row +prow, col +pcol) || row < board->SpawnRows())){
				return false;
			}
		}
	}
	return true;
}

void
Piece::properReleaseAt(uint row, uint col){
	for(uint prow = 0; prow < PIECE_SIZE; prow++ ){
		for(uint pcol = 0; pcol < PIECE_SIZE; pcol++) {
			if(board->on(row +prow, col +pcol) &&
			   board->at(row +prow, col +pcol) == NULL) {
				board->set(row +prow, col +pcol, piece[prow][pcol]);
			}
		}
	}
}

void
Piece::properRelease(){
	auto drow = round(rowMap.mapBack(location.y));
	auto dcol = round(colMap.mapBack(location.x));
	properReleaseAt(drow,dcol);
}

// FIXME does not follow project spec
// need to replace with correct implementation
bool
Piece::release(){
	auto top  = findTop();
	auto left = findLeft();

	GLfloat min = FLT_MAX;
	uint r = 0;
	uint c = 0;
	for(uint row = board->SpawnRows(); row < board->Rows(); row++) {
		for(uint col = 0; col < board->Cols(); col++) {
			if(canReleaseAt(row, col, top, left)){
				auto temp = distTo(row, col, top, left);
				if(min > temp ) {
					r = row;
					c = col;
					min = temp;
				}
			}
		}
	}
	if(min != FLT_MAX) {
		// std::cout << Term::INFO << "releasing" << std::endl; 
		// std::cout << "dist to   " << r << "," << c << " = " << min << std::endl;
		// std::cout << "piece loc " << location.x << ',' <<location.y << std::endl;
		// std::cout << "cell loc  "  << colMap.map(c)<< ','<<rowMap.map(r)<< std::endl;
		releaseAt(r, c, top, left);
		return true;
	}
	return false;
}

bool
Piece::canReleaseAt(uint row, uint col, uint top, uint left){
	for(uint prow = 0; prow < PIECE_SIZE; prow++ ){
		for(uint pcol = 0; pcol < PIECE_SIZE; pcol++) {
			if(!board->on(row +prow-top, col +pcol-left) ||
			   board->at(row +prow-top, col +pcol-left) != NULL){
				if(piece[prow][pcol] != NULL){
					return false;
				}
			}
		}
	}
	return true;
}

void
Piece::releaseAt(uint row, uint col, uint top, uint left) {
	for(uint prow = 0; prow < PIECE_SIZE; prow++ ){
		for(uint pcol = 0; pcol < PIECE_SIZE; pcol++) {
			if(board->on(row +prow-top, col +pcol-left) &&
			   board->at(row +prow-top, col +pcol-left) == NULL) {
				board->set(row +prow-top, col +pcol-left, piece[prow][pcol]);
			}
		}
	}
}

GLfloat
Piece::distTo(uint row, uint col, uint top, uint left){
	GLfloat dx = colMap.map((GLfloat)col+top) - (location.x) ;
	GLfloat dy = rowMap.map((GLfloat)row+left) - (location.y) ;
	// std::cout << Term::INFO << " row "<< row << " = " << rowMap.map((GLfloat)row) << std::endl;
	// std::cout << "        " << " col "<< col << " = " << colMap.map((GLfloat)col) << std::endl;
	return sqrt(dx*dx + dy*dy);
}

void
Piece::makePiece(){
	this->clear();
	shape    = randShape();
	// shape = I_PIECE;
	rotated = false;
	std::string temp;
	switch(shape) {
	case I_PIECE:
		temp = "I piece";
		makeI();
		break;
	case L_PIECE:
		temp = "L piece";
		makeL();
		break;
	case S_PIECE:
		temp = "S piece";
		makeS();
		break;
	}

	syncCheck();
	GLuint rotations = rand() % 4; // 4 * 90 = 360
	// std::cout << "rotating " << temp << ' ' << rotations << " times" << std::endl;
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

void
Piece::clear(){
	for(uint row = 0; row < PIECE_SIZE; ++row) {
		for(uint col = 0; col < PIECE_SIZE; ++col) {
			piece[row][col] = NULL;
		}
	}
	syncCheck();
}

void
Piece::render() {
	clearCollisionMatrix();
	generateCollisionMatrix();

	for (GLuint row = 0; row < PIECE_SIZE; ++row) {
		for (GLuint col = 0; col < PIECE_SIZE; ++col) {
			auto current = piece[row][col];
			if (current != NULL) {

				current->colliding = collideMatrix[row][col];
				current->location  = glm::vec3((GLfloat)col + this->location.x,
											  -(GLfloat)row + this->location.y,
											  location.z);
				current->render();
				current->colliding = false;
			}
		}
	}
}

void
Piece::generateCollisionMatrix(){
	auto row = round(rowMap.mapBack(location.y));
	auto col = round(colMap.mapBack(location.x));
	for(uint prow = 0; prow < PIECE_SIZE; prow++ ){
		for(uint pcol = 0; pcol < PIECE_SIZE; pcol++) {
			if(!board->on(row +prow, col +pcol) ||
			   board->at(row +prow, col +pcol) != NULL){
				if(piece[prow][pcol] != NULL){
					collideMatrix[prow][pcol] = true;
				}
			}
		}
	}
}

void
Piece::clearCollisionMatrix(){
	for (GLuint row = 0; row < PIECE_SIZE; ++row) {
		for (GLuint col = 0; col < PIECE_SIZE; ++col) {
			collideMatrix[row][col] = false;
		}
	}
}

void
Piece::debug(){
	for(uint row = 0; row < PIECE_SIZE; ++row) {
		std::cout << row;
		std::cout << ':';
		for(uint col = 0; col < PIECE_SIZE; ++col) {
			auto temp = piece[row][col];
			if(temp != NULL) {
				switch(temp->fruit()){
				case APPLE:
					std::cout << Term::IRed;
					break;
				case BANANA:
					std::cout << Term::IYellow;
					break;
				case GRAPE:
					std::cout << Term::IPurple;
					break;
				case PEAR:
					std::cout << Term::IGreen;
					break;
				case ORANGE:
					std::cout << Term::Yellow;
					break;
				}
				std::cout << '+' << Term::Reset;
			} else {
				std::cout << '-';
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
