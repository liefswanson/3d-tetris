#include "Board.hpp" 

Board::Board(uint rows, uint cols, uint spawnRows){
	this->rows      = rows;
	this->cols      = cols;
	this->spawnRows = spawnRows;
	
	board = new Tile* [cols*(rows)];

	for (uint i = 0; i < cols*(rows); ++i) {
		board[i] = NULL;
	}
}

Board::~Board() {
	for (uint i = 0; i < cols*(rows); ++i) {
		if (board[i] != NULL){
			delete board[i];
		}
	}
	delete[] board;
}

//-------------------------------------------------------------------------------------------------

bool
Board::on(uint row, uint col) {
	return row < rows &&
		   col < cols;
}

Tile*
Board::at(uint row, uint col) {
	if (row > rows || col > cols ) {
		std::cout << "tried to get outside grid " << row << ' ' << col << std::endl;
		return NULL;
	}
	return board[cols*row + col];
}

Tile*
Board::makeAt(uint row, uint col, uint fruit){
	auto temp = at(row, col);
	if (temp == NULL) {
		set(row, col, new Tile(fruit));
		return at(row, col);
	} else {
		std::cout << "tried to place in illegal spot " << row << ' ' << col << std::endl;
		return NULL;	
	} 
}

void
Board::set(uint row, uint col, Tile* val) {
	board[cols*row + col] = val;
}

//-------------------------------------------------------------------------------------------------


Tile**
Board::scanForFullRows() {
	auto diff = new Tile*[cols*rows];

	for (uint i = 0; i < cols*rows; i++){
		diff[i] = NULL;
	}
	
	for(uint row = 0; row < rows; ++row){
		bool valid = true;
		for(uint col = 0; col < cols; ++col) {
			if (board[cols*row + col] == NULL) {
				valid = false;
				break;
			} else {
				diff[cols*row +col] = board[cols *row + col];
			}
		}
		if(!valid) {
			for(uint col = 0; col < cols; ++col) {
				diff[cols*row +col] = NULL;
			}
		}
	}
	return diff;
}

Tile**
Board::scanForFruitChainsRows() {

	Tile** diff  = new Tile*[cols*rows];

	for (uint i = 0; i < cols*rows; i++) {
		diff[i] = NULL;
	}
		
	for(uint row = 0; row < rows; ++row) {
		uint chain   = 0;
		Tile* firstLink = NULL;
		uint col = 0;
		for(; col < cols; ++col) {
			Tile* temp = at(row, col);

			if (firstLink != NULL) { 

				if (temp != NULL &&
					firstLink->fruit() == temp->fruit()) {
					++chain;
				} else {
					if (chain >= CHAIN_LENGTH) {
						for(uint i = 1; i <= chain; ++i) {
							diff[cols*row + col - i] = board[cols*row + col -i];
						}
					}
					firstLink = temp;
					if (temp != NULL) {
						chain = 1;
					} else {
						chain = 0;
					}
				}
			
			} else if (temp != NULL) {
				firstLink = temp;
				chain = 1;
			} else {
				chain = 0;
			}
		}
		if (chain >= CHAIN_LENGTH) {
			for(uint i = 1; i <= chain; ++i) {
				diff[cols*row + col - i] = board[cols*row + col -i];
			}
		}
	}
	return diff;
}

Tile**
Board::scanForFruitChainsCols() {

	Tile** diff  = new Tile*[cols*rows];

	for (uint i = 0; i < cols*rows; i++) {
		diff[i] = NULL;
	}
	
	for(uint col = 0; col < cols; ++col) {
		
		uint chain   = 0;
		Tile* firstLink = NULL;
		uint row = 0;
		for(; row < rows; ++row) {
			Tile* temp = at(row, col);

			if (firstLink != NULL) { 

				if (temp != NULL &&
					firstLink->fruit() == temp->fruit()) {
					++chain;
				} else {
					if (chain >= CHAIN_LENGTH) {
						for(uint i = 1; i <= chain; ++i) {
							diff[cols*(row -i) + col] = board[cols*(row -i) + col];
						}
					}
					firstLink = temp;
					if (temp != NULL) {
						chain = 1;
					} else {
						chain = 0;
					}
				}
			
			} else if (temp != NULL) {
				firstLink = temp;
				chain = 1;
			} else {
				chain = 0;
			}
		}
		if (chain >= CHAIN_LENGTH) {
			for(uint i = 1; i <= chain; ++i) {
				diff[cols*(row -i) + col] = board[cols*(row -i) + col];
			}
		}
	}
	return diff;
}

//-------------------------------------------------------------------------------------------------

Tile**
Board::mergeDiffs(Tile** a, Tile** b) {
	Tile** val = new Tile* [cols*(rows-spawnRows)];
	for(uint i = 0; i < cols*(rows-spawnRows); i++){
		if (a[i] != NULL) {
			val[i] = a[i];
		} else {
			val[i] = b[i];
		}
	}
	return val;
}

bool
Board::validateDiff(Tile** diff){
	for(uint i = 0; i < rows*cols; ++i ) {
		if (diff[i] != NULL) {
			return GL_TRUE;
		}
	}
	return GL_FALSE;
}

void
Board::removeDiff(Tile** diff) {
	Tile** destination = new Tile*[cols*(rows)];

	for (uint i = 0; i < cols*(rows -spawnRows); i++) {
		destination[i] = NULL;
	}

	Tile** source      = board;

	for(uint col = 0; col < cols; ++col) {

		    uint destRow   = rows -1;
		for(uint sourceRow = rows -1; sourceRow >= spawnRows; --sourceRow) {
			while(diff[cols*(sourceRow -spawnRows) + col] != NULL) {
				delete source[cols*(sourceRow) + col];
				--sourceRow;
			}
			destination[cols*(destRow)   + col] =
				 source[cols*(sourceRow) + col];
			--destRow;
		}
	}
	board = destination;
	delete[] source;
}

void
Board::debugDiff(Tile** diff){
	for(uint row = 0; row < rows; ++row) {
		std::cout << std::setfill(' ') << std::setw(2) << (int)row -(int)spawnRows;
		std::cout << ':';
		for(uint col = 0; col < cols; ++col) {
			auto temp = diff[cols*row + col]; 
			if(temp != NULL) {
				switch(temp->fruit()){
				case APPLE:
					std::cout << Term::IRed << '+';
					break;
				case BANANA:
					std::cout << Term::IYellow << '+';
					break;
				case GRAPE:
					std::cout << Term::IPurple << '+';
					break;
				case PEAR:
					std::cout << Term::IGreen << '+';
					break;
				case ORANGE:
					std::cout << Term::Yellow << '+';
					break;
				}
				std::cout << Term::Reset;
			} else {
				std::cout << '-';
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


//-------------------------------------------------------------------------------------------------

void
Board::render() {
	for (GLuint row = spawnRows; row < rows; ++row) {
		for (GLuint col = 0; col < cols; ++col) {
			Tile* current = this->at(row, col);
			if (current != NULL) {
				//TODO doesn't actually render
				// current->location = glm::vec3(gridMap.map((GLfloat)col),
				// 							  gridMap.map((GLfloat)row),
				// 							  0.f);
				current->location = glm::vec3(
					colMap.map((GLfloat)col),
					rowMap.map((GLfloat)row),
					0.f);
				current->render();
			}
		}
	}
}

void
Board::clear() {
	for (GLuint i = 0; i < cols*(rows); ++i) {
		if (board[i] != NULL){
			delete board[i];
			board[i] = NULL;
		}
	}
}

//-------------------------------------------------------------------------------------------------

uint
Board::SpawnRows() {return spawnRows;}
uint
Board::Rows()      {return rows;}
uint
Board::Cols()      {return cols;}

// dangerous operation
// DEBUG ONLY
bool
Board::eq(Tile** diff) {
	for(uint i = 0; i < rows*cols; i++) {
		if (board[i] != diff[i]) {
			return false;
		}
	}
	return true;
}
