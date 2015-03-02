#include "../src/termColor.hpp"
#include <gtest/gtest.h>

namespace {

// The fixture for testing class Foo.
class TermTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  TermTest() {
    // You can do set-up work for each test here.
  }

  virtual ~TermTest() {
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
	// tests the macros for info, warn, error, fail, and pass
	TEST(TermTest, macros) {
		std::cout << Term::INFO  << std::endl;
		std::cout << Term::WARN  << std::endl;
		std::cout << Term::ERROR << std::endl;

		std::cout << Term::PASS << std::endl;
		std::cout << Term::FAIL << std::endl;

	}
	
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
} 
