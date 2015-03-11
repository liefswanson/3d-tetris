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
			board->debugDiff(board->board);
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

	if(keys[GLFW_KEY_J]){
		auto pos = arm->checkRotateShoulder(5.f);
		piece->canRelocate(pos.x, pos.y);
		piece->applyMove();
	}
	if(keys[GLFW_KEY_L]) {
		auto pos = arm->checkRotateShoulder(-5.f);
		piece->canRelocate(pos.x, pos.y);
		piece->applyMove();
	}
	if(keys[GLFW_KEY_K]){
		auto pos = arm->checkRotateElbow(5.f);
		piece->canRelocate(pos.x, pos.y);
		piece->applyMove();
	}
	if(keys[GLFW_KEY_I]) {
		auto pos = arm->checkRotateElbow(-5.f);
		piece->canRelocate(pos.x, pos.y);
		piece->applyMove();
	}

	// wasd
	auto temp = moveSpeed *deltaTime;
	if(keys[GLFW_KEY_W]) {
		if(piece->canRelocate(x,y +temp)){
			piece->applyMove();
			y += temp;
		} else {
			piece->discardMove();
		}
	}
	if(keys[GLFW_KEY_A]){
		if(piece->canRelocate(x -temp,y)){
			piece->applyMove();
			x -= temp;
		} else {
			piece->discardMove();
		}
	}
	if(keys[GLFW_KEY_S]){
		if(piece->canRelocate(x,y -temp)){
			piece->applyMove();
			y -= temp;
		} else {
			piece->discardMove();
		}
	}
	if(keys[GLFW_KEY_D]) {
		if(piece->canRelocate(x +temp,y)){
			piece->applyMove();
			x += temp;
		} else {
			piece->discardMove();
		}
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
	

	board = new Board(ROWS, COLS, SROWS);
	piece = new Piece(board, 2.f);
	
	arm   = new Arm(glm::vec3(-7.f, -12.f, 2.f), 10.f, piece);

	auto temp = arm->checkRotateElbow(0);

	piece->makePiece();
	piece->canRelocate(temp.x, temp.y);
	piece->applyMove();
	
	cam.addProgram(Tile::program);
	cam.addProgram(arm->program);

	while(!glfwWindowShouldClose(window)) {
		updateTime();
		glfwPollEvents();
		actOnKeys();
		
		glClearColor(BG, BG, BG, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.location = glm::vec3(distance  *sin(-glm::radians(angle)),
								 origin.y,
								 -distance *cos(-glm::radians(angle)));
		cam.Update();

		board->render();
		piece->render();
		arm->render();
		glfwSwapBuffers(window);
	}

	cam.removeProgram(Tile::program);
	cam.removeProgram(arm->program);
	Tile::clean();
	delete board;
	delete piece;
	delete arm;
	
	glfwTerminate();
	return 0;
}
