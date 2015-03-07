#include "../src/Board.hpp"
#include <gtest/gtest.h>
#include "../src/TermColor.hpp" 

#include <stdlib.h>
#include <time.h> 

namespace {
	class BoardTest : public ::testing::Test {

	protected:
		BoardTest() {}
		virtual ~BoardTest() {}

		virtual void SetUp() {}
		virtual void TearDown() {}
	};
//-------------------------------------------------------------------------------------------------

	TEST(BoardTest, constructor){
		Board a  = Board(25, 10, 5);
		EXPECT_EQ(a.Rows(), 25);
		EXPECT_EQ(a.Cols(), 10);
		EXPECT_EQ(a.SpawnRows(), 5);
	}

//-------------------------------------------------------------------------------------------------

	// TODO write better validate test
	TEST(BoardTest, validateDiff) {
		Board a  = Board(25, 10, 5);
		EXPECT_EQ(a.validateDiff(a.board), false) << Term::FAIL << "Board did not initialize to empty, or the validate function returned a false positive." << std::endl;
		srand(time(NULL));
		for(uint i = 0; i < 20; ) {
			auto row   = rand() % a.Rows();
			auto col   = rand() % a.Cols();
			auto fruit = rand() % FRUITS;

			if (a.at(row, col) == NULL) {
				a.set(row, col, new Tile(fruit));
				i++;
			}
		}
		// a.debugDiff(a.board);
		EXPECT_EQ(a.validateDiff(a.board), true) << Term::FAIL << "Validate diff cannot see there are objects in the diff." << std::endl;
	}

//-------------------------------------------------------------------------------------------------

	TEST(Board, clear) {
		Board a  = Board(25, 10, 5);
		EXPECT_EQ(a.validateDiff(a.board), false) << Term::FAIL << "Board did not initialize to empty, or the validate function returned a false positive." << std::endl;
		srand(time(NULL));
		for(uint i = 0; i < 20; ) {
			auto row   = rand() % a.Rows();
			auto col   = rand() % a.Cols();
			auto fruit = rand() % FRUITS;

			if (a.at(row, col) == NULL) {
				a.set(row, col, new Tile(fruit));
				i++;
			}
		}
		// a.debugDiff(a.board);
		a.clear();
		// a.debugDiff(a.board);
		EXPECT_EQ(a.validateDiff(a.board), false) << Term::FAIL << "Board did not clear." << std::endl;
	}

//-------------------------------------------------------------------------------------------------
	
	TEST(BoardTest, rowScan) {
		Board empty = Board(25, 10, 5);
		auto emptyDiff = empty.scanForFullRows();
		EXPECT_FALSE(empty.validateDiff(emptyDiff))<< Term::FAIL << "empty board made false positive" << std::endl;
		
		Board a = Board(25, 10, 5);
		for(uint i = 0; i < a.Cols(); i++) {
			a.makeAt(0, i, ORANGE);
		}
		// std::cout << Term::INFO << " board" << std::endl;
		// a.debugDiff(a.board);
		auto adiff = a.scanForFullRows();
		// std::cout << Term::INFO << " diff" << std::endl;
		// a.debugDiff(diff);
		EXPECT_TRUE(a.eq(adiff)) << Term::FAIL << "full row scan failed" << std::endl;

		Board b = Board(25, 10, 5);

		for(uint i = 0; i < a.Cols()-1; i++) {
			b.makeAt(0, i, APPLE);
		}
		auto bdiff = b.scanForFullRows();
		// b.debugDiff(b.board);
		// b.debugDiff(bdiff);
		EXPECT_FALSE(b.validateDiff(bdiff))<< Term::FAIL << "almost full row scan gave false positive" << std::endl;
	}
	//-------------------------------------------------------------------------------------------------

	TEST (BoardTest, ColColorScan) {
		std::cout << Term::INFO << " starting column colorchain tests" << std::endl;
		Board a = Board(25, 10, 5);
		for(uint i = 0; i < a.Rows(); i++) {
			for(uint j = 0; j <= i; j++) {
				a.makeAt(j, 0, PEAR);
			}
			// a.debugDiff(a.board);
			auto diff = a.scanForFruitChainsCols();
			// a.debugDiff(diff);

			if(i +1 >= Board::CHAIN_LENGTH) {
				EXPECT_TRUE(a.eq(diff)) << Term::FAIL << " iterating colorchain trailing NULL test " << i;
			} else {
				EXPECT_FALSE(a.eq(diff)) << Term::FAIL << " iterating colorchain trailing NULL test " << i;			
			}
			a.clear();
		}

		for(uint i = 0; i < a.Rows(); i++) {
			for(uint j = 0; j <= i; j++) {
				a.makeAt(a.Rows() -1 -j, 0, PEAR);
			}
			// a.debugDiff(a.board);
			auto diff = a.scanForFruitChainsCols();
			// a.debugDiff(diff);

			if(i +1 >= Board::CHAIN_LENGTH) {
				EXPECT_TRUE(a.eq(diff)) << Term::FAIL << " iterating colorchain leading NULL test " << i;
			} else {
				EXPECT_FALSE(a.eq(diff)) << Term::FAIL << " iterating colorchain leading NULL test " << i;			
			}
			a.clear();
		}
		std::cout << Term::WARN << " missing complex colorchain column tests" << std::endl;
	}

	TEST (BoardTest, RowColorScan) {
		std::cout << Term::INFO << " starting row colorchain tests" << std::endl;
		Board a = Board(25, 10, 5);
		for(uint i = 0; i < a.Cols(); i++) {
			for(uint j = 0; j <= i; j++) {
				a.makeAt(0, j, PEAR);
			}
			// a.debugDiff(a.board);
			auto diff = a.scanForFruitChainsRows();
			// a.debugDiff(diff);

			if(i +1 >= Board::CHAIN_LENGTH) {
				EXPECT_TRUE(a.eq(diff)) << Term::FAIL << " iterating colorchain trailing NULL test " << i;
			} else {
				EXPECT_FALSE(a.eq(diff)) << Term::FAIL << " iterating colorchain trailing NULL test " << i;			
			}
			a.clear();
		}

		for(uint i = 0; i < a.Cols(); i++) {
			for(uint j = 0; j <= i; j++) {
				a.makeAt(0, a.Cols() -1 -j, PEAR);
			}
			// a.debugDiff(a.board);
			auto diff = a.scanForFruitChainsRows();
			// a.debugDiff(diff);

			if(i +1 >= Board::CHAIN_LENGTH) {
				EXPECT_TRUE(a.eq(diff)) << Term::FAIL << " iterating colorchain leading NULL test " << i;
			} else {
				EXPECT_FALSE(a.eq(diff)) << Term::FAIL << " iterating colorchain leading NULL test " << i;			
			}
			a.clear();
		}
		std::cout << Term::WARN << " missing complex colorchain row tests" << std::endl;
	}
//-------------------------------------------------------------------------------------------------

}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
} 
 
