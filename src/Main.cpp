#include "Main.hpp"

void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void
scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	distance -= yoffset;
}

void updateTime(){
	GLfloat timeThisFrame  = glfwGetTime();
	deltaTime              = timeThisFrame - timeLastFrame;
	timeLastFrame          = timeThisFrame;
}

void
actOnKeys(){
	if(keys[GLFW_KEY_LEFT]){
		angle -= orbitSpeed *deltaTime;
	}
	if(keys[GLFW_KEY_RIGHT]) {
		angle += orbitSpeed *deltaTime;
	}
}


//---------------------------------------------------------------------------------------------------

int
main(int argc, char *argv[]) {
	glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, WIDTH, HEIGHT);

    glEnable(GL_DEPTH_TEST);

	glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
	
	Tile::init();
    // glm::vec3(2.f/(GLfloat)COLS, 2.f/(GLfloat)COLS, 2.f/(GLfloat)COLS)
	Camera cam = Camera(glm::vec3(0.f, -1.f, 0.f),
						glm::vec3(), // this need not be initialized it is updated every turn
						origin, 
						45.f, (GLfloat)WIDTH/(GLfloat)HEIGHT,
						0.1f, 1000.f);
	
	cam.addProgram(Tile::program);

	Board board (ROWS, COLS, SROWS);
	board.makeAt(0, 0, APPLE);
	board.makeAt(1, 1, APPLE);
	board.makeAt(2, 2, APPLE);
	board.makeAt(3, 3, APPLE);
	board.makeAt(4, 4, APPLE);
	board.makeAt(5, 5, APPLE);
	board.makeAt(6, 6, APPLE);
	board.makeAt(7, 7, APPLE);
	board.makeAt(8, 8, APPLE);
	board.makeAt(9, 9, APPLE);
	
	board.makeAt(10, 0, ORANGE);
	board.makeAt(11, 1, ORANGE);
	board.makeAt(12, 2, ORANGE);
	board.makeAt(13, 3, ORANGE);
	board.makeAt(14, 4, ORANGE);
	board.makeAt(15, 5, ORANGE);
	board.makeAt(16, 6, ORANGE);
	board.makeAt(17, 7, ORANGE);
	board.makeAt(18, 8, ORANGE);
	board.makeAt(19, 9, ORANGE);

	board.makeAt(20, 0, PEAR);
	board.makeAt(21, 1, PEAR);
	board.makeAt(22, 2, PEAR);
	board.makeAt(23, 3, PEAR);
	board.makeAt(24, 4, PEAR);

	board.debugDiff(board.board);

	while(!glfwWindowShouldClose(window)) {
		updateTime();
		glfwPollEvents();
		actOnKeys();
		
		glClearColor(BG, BG, BG, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.location = glm::vec3(distance  * sin(-glm::radians(angle)),
								 origin.y,
								 distance * cos(-glm::radians(angle)));
		cam.Update();

		board.render();
		glfwSwapBuffers(window);
	}

	Tile::clean();
	
	glfwTerminate();
	return 0;
}
