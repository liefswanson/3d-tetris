#include "Main.hpp"

void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
	}else if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		if(piece->release()){
			piece->clear();
			piece->makePiece();
			piece->debug();
		}
	} else if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS){
            keys[key] = true;
			
		}
        else if (action == GLFW_RELEASE) {
            keys[key] = false;
		}
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

GLfloat x = 0;
GLfloat y = 0;

GLfloat moveSpeed = 10.f;

void
actOnKeys(){
	if(keys[GLFW_KEY_LEFT]){
		angle -= orbitSpeed *deltaTime;
	}
	if(keys[GLFW_KEY_RIGHT]) {
		angle += orbitSpeed *deltaTime;
	}

	if(keys[GLFW_KEY_UP]){
		// TODO limit by delta time
		piece->rotC();
	}

	// wasd
	if(keys[GLFW_KEY_W]) {
		y += moveSpeed *deltaTime;
	}
	if(keys[GLFW_KEY_A]){
		x -= moveSpeed *deltaTime;
	}
	if(keys[GLFW_KEY_S]){
		y -= moveSpeed *deltaTime;
	}
	if(keys[GLFW_KEY_D]) {
		x += moveSpeed *deltaTime;
	}
}


//-------------------------------------------------------------------------------------------------

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
	
	Tile::init(glm::vec3(.8f, .8f, .8f));

	Camera cam = Camera(glm::vec3(0.f, 1.f, 0.f),
						glm::vec3(), // this need not be initialized it is updated every turn
						origin, 
						45.f, (GLfloat)WIDTH/(GLfloat)HEIGHT,
						0.1f, 1000.f);
	
	cam.addProgram(Tile::program);

	board = new Board(ROWS, COLS, SROWS);
	piece = new Piece(board);
	
	// for (uint i = SROWS; i < ROWS; i++) {
	// 	board.makeAt(i, COLS-1, PEAR);
	// 	board.makeAt(i, 0, APPLE);
	// }

	// for (uint i = 1; i < COLS -1; i++) {
	// 	board.makeAt(SROWS, i, GRAPE);
	// 	board.makeAt(ROWS-1, i, BANANA);
	// }
	
	//board.debugDiff(board.board);

	piece->makePiece();
	//piece.debug();
	while(!glfwWindowShouldClose(window)) {
		updateTime();
		glfwPollEvents();
		actOnKeys();
		
		glClearColor(BG, BG, BG, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.location = glm::vec3(distance  * sin(-glm::radians(angle)),
								 origin.y,
								 -distance * cos(-glm::radians(angle)));
		cam.Update();

		if(piece->canRelocate(x,y)){
			piece->applyMove();
		} else {
			piece->discardMove();
		}
		board->render();
		piece->render();
		glfwSwapBuffers(window);
	}

	Tile::clean();
	
	glfwTerminate();
	return 0;
}
