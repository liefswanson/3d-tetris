#pragma once

#include <iomanip>

#include "Tile.hpp"

class Board {
public:	
	Tile** board;

	Board(uint rows, uint cols, uint spawnRows);
	~Board();
//-------------------------------------------------------------------------------------------------
	
	bool   on    (uint row, uint col);
	Tile*  at    (uint row, uint col);
	Tile*  makeAt(uint row, uint col, uint fruit);
	void   set   (uint row, uint col, Tile* val);
//-------------------------------------------------------------------------------------------------

	Tile** scanForFullRows();
	Tile** scanForFruitChainsCols();
	Tile** scanForFruitChainsRows();
//-------------------------------------------------------------------------------------------------

	Tile** mergeDiffs  (Tile** a, Tile** b);
	bool   validateDiff(Tile** diff);
	void   removeDiff  (Tile** diff);
	void   debugDiff   (Tile** diff);
//-------------------------------------------------------------------------------------------------

	void   render();
	void   clear();
//-------------------------------------------------------------------------------------------------

	uint SpawnRows();
	uint Rows();
	uint Cols();

	bool eq(Tile** diff);

	const static uint CHAIN_LENGTH = 3;
private:
	uint spawnRows;
	uint rows;
	uint cols;
};
