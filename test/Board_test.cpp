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

	TEST(BoardTest, constructor){
		Board a  = Board(25, 10, 5);
		EXPECT_EQ(a.Rows(), 25);
		EXPECT_EQ(a.Cols(), 10);
		EXPECT_EQ(a.SpawnRows(), 5);
	}
   
	TEST(BoardTest, validateDiff) {
		Board a  = Board(25, 10, 5);
		EXPECT_EQ(a.validateDiff(a.board), false) << Term::FAIL << "Board did not initialize to empty, or the validate function malfunctioned." << std::endl;
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

	TEST(BoardTest, rowScan) {
		Board a = Board(25, 10, 5);

		for(uint i = 0; i < a.Cols(); i++) {
			a.makeAt(0, i, ORANGE);
		}
		// std::cout << Term::INFO << " board" << std::endl;
		// a.debugDiff(a.board);

		auto diff = a.scanForFullRows();
		// std::cout << Term::INFO << " diff" << std::endl;
		// a.debugDiff(diff);

		EXPECT_TRUE(a.eq(diff)) << Term::FAIL << "The first row scan failed";
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
} 
 
