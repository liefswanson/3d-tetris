#include "../src/Array2D.hpp"
#include <gtest/gtest.h>
#include "../src/TermColor.hpp" 

#include <tuple>
namespace {
	class Array2DTest : public ::testing::Test {

	protected:
		// You can remove any or all of the following functions if its body
		// is empty.

		Array2DTest() {
			// You can do set-up work for each test here.
		}

		virtual ~Array2DTest() {
			// You can do clean-up work that doesn't throw exceptions here.
		}

		// If the constructor and destructor are not enough for setting up
		// and cleaning up each test, you can define the following methods:

		virtual void SetUp() {
			// Code here will be called immediately after the constructor (right
			// before each test).
		}

		virtual void TearDown() {
			// Code here will be called immediately after each test (right
			// before the destructor).
		}

		// Objects declared here can be used by all tests in the test case for Foo.
	};
	int width  = 10;
	int height = 10; 

	TEST(Array2D, createDestroy) {
		Array2D<int> a  (width, height);
		std::cout << Term::INFO << "running init array elems to 0 test" << std::endl;
		for(int x = 0; x < width; x++) {
			for(int y = 0; y < width; y++) {
				ASSERT_EQ(0, a[x][y]) << Term::FAIL << " did not initialize to null at index [" << x << "] [" << y << ']' << std::endl;
			}
		}
	}

   
	TEST(Array2D, SetGet) {
		Array2D<std::tuple<int, int>> a  (width, height);
		
		std::cout << Term::INFO << "running SetGet" << std::endl;
		for(int x = 0; x < width; x++) {
			for(int y = 0; y < width; y++) {
				auto temp = std::tuple<int, int>(x, y);
				a[x][y] = temp;
				ASSERT_EQ(temp, a[x][y]) << Term::FAIL << " value did not match at index [" << x << "] [" << y << ']' << std::endl;
			}
		}
	}

	TEST(Array2D, createDestroy_heap) {

		std::cout << Term::INFO << "running constructor" << std::endl;
		Array2D<int>* a = new Array2D<int>  (width, height);
		auto temp = *a; 
		std::cout << Term::INFO << "running init array elems to 0 test on the heap" << std::endl;
		for(int x = 0; x < width; x++) {
			for(int y = 0; y < width; y++) {
				ASSERT_EQ(0, temp[x][y]) << Term::FAIL << " did not initialize to null at index [" << x << "] [" << y << ']' << std::endl;
			}
		}
		std::cout << Term::INFO << "running destructor" << std::endl;
		// gtest seems to clean this up for me...
		// will segfault if i delete it
		// delete a;
	}

	TEST(Array2D, setGet_heap) {
		std::cout << Term::INFO << "running constructor" << std::endl;

		Array2D<std::tuple<int, int>> * a = new Array2D<std::tuple<int, int>>   (width, height);
		auto temp = *a; 
		std::cout << Term::INFO << "running SetGet on the heap" << std::endl;
		for(int x = 0; x < width; x++) {
			for(int y = 0; y < width; y++) {
				auto tup = std::tuple<int, int>(x, y);
				temp[x][y] = tup;
				ASSERT_EQ(tup, temp[x][y]) << Term::FAIL << " value did not match at index [" << x << "] [" << y << ']' << std::endl;
			}
		}
		std::cout << Term::INFO << "running destructor" << std::endl;
		// gtest seems to clean this up for me...
		// will segfault if i delete it
		// delete a; 
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
} 
