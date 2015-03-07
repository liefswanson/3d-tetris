#include "../src/Camera.hpp"
#include <gtest/gtest.h>
#include "../src/TermColor.hpp" 

#include <tuple>
namespace {
	class CameraTest : public ::testing::Test {

	protected:
		CameraTest() {}

		virtual ~CameraTest() {}

		virtual void SetUp() {}

		virtual void TearDown() {}
	};
   
	TEST(CameraTest, addRemoveProgram) {
			Camera cam = Camera(glm::vec3(0.f, 1.f, 0.f),
								glm::vec3(),
								glm::vec3(), 
								45.f, 2.f,
								0.1f, 100.f);
			std::vector<GLuint> temp = {1, 45, 81, 0, 348, 3546481, 996441, 12};
			for(uint i = 0; i < temp.size(); i++) {
				cam.addProgram(temp[i]);
			}

			EXPECT_EQ(cam.debug().size(), temp.size()) << Term::FAIL << "not all programs copied into the cameras targets." << std::endl;
			
			for(uint i = 0; i < temp.size(); i++) {
				cam.removeProgram(temp[i]);
			}
			EXPECT_EQ(cam.debug().size(), 0) << Term::FAIL << "not all programs were removed from the cameras targets." << std::endl;

	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
} 
 
