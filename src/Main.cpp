#include "Main.hpp"

void
releasePieceHandler(){
	if(piece->properCanRelease()){
		piece->properRelease();
		piece->clear();
		piece->makePiece();
			
		arm->checkRepositionShoulder(shoulderDefaultRotation);
		arm->applyMove();
		auto temp = arm->checkRepositienElbow(elbowDefaultRotation);
		arm->applyMove();
		
		piece->makePiece();
		piece->canRelocate(temp.x, temp.y);
		piece->applyMove();

		piece->debug();
		board->debugDiff(board->board);
	}
}

void
rotatePieceClockwiseHandler(){
	if(piece->canRotateClockwise()) {
		piece->applyMove();
	} else {
		piece->discardMove();
	}
}

void
rotatePieceWithershinsHandler(){
	if(piece->canRotateWishershins()) {
		piece->applyMove();
	} else {
		piece->discardMove();
	}
}

void
rotateShoulderHandler(GLfloat theta){
	auto pos = arm->checkRotateShoulder(theta);
	if (piece->canRelocate(pos.x, pos.y)) {
		arm->applyMove();
		piece->applyMove();	
	} else {
		arm->discardMove();
		piece->discardMove();	
	}
}

void
rotateElbowHandler(GLfloat theta){
	auto pos = arm->checkRotateElbow(theta);
	if (piece->canRelocate(pos.x, pos.y)) {
		arm->applyMove();
		piece->applyMove();	
	} else {
		arm->discardMove();
		piece->discardMove();	
	}	
}

void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// handle modifiers
	shift = (mods & GLFW_MOD_SHIFT)   == GLFW_MOD_SHIFT;
	ctrl  = (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL;
	alt   = (mods & GLFW_MOD_ALT)     == GLFW_MOD_ALT;
	super = (mods & GLFW_MOD_SUPER)   == GLFW_MOD_SUPER;

	if(action == GLFW_PRESS){
		switch (key) {
		case GLFW_KEY_ESCAPE:
		case GLFW_KEY_Q:
			glfwWindowShouldClose(window);
			break;
		case GLFW_KEY_R: {
			board->clear();
			piece->destroyPiece();
			piece->makePiece();
			
			arm->checkRepositionShoulder(shoulderDefaultRotation);
			arm->applyMove();
			auto temp = arm->checkRepositienElbow(elbowDefaultRotation);
			arm->applyMove();
		
			piece->makePiece();
			piece->canRelocate(temp.x, temp.y);
			piece->applyMove();
			break;
		}
		case GLFW_KEY_SPACE:
			releasePieceHandler();
			break;
		default:
			break;
		}
	}
	// for custom repeat behaviour
	if (action == GLFW_PRESS) {
            keys[key] = true;
	} else if (action == GLFW_RELEASE) {
            keys[key] = false;
	}
}

void
actOnKeys(){
	if(keys[GLFW_KEY_LEFT] && ctrl) {
		orbitAngle -= orbitSpeed *deltaTime;
	}
	if(keys[GLFW_KEY_RIGHT] && ctrl) {
		orbitAngle += orbitSpeed *deltaTime;
	}
	if(keys[GLFW_KEY_UP] && rotateTimer <= 0.f) {
		rotateTimer = rotateTimerMax;
		if (ctrl) {
			rotatePieceWithershinsHandler();
		} else {
			rotatePieceClockwiseHandler();
		}
	}
	if(keys[GLFW_KEY_W]){
		rotateElbowHandler(elbowRotatePerSecond *deltaTime);
	}
	if(keys[GLFW_KEY_S]){
		rotateElbowHandler(-elbowRotatePerSecond *deltaTime);
	}
	if(keys[GLFW_KEY_A]) {
		rotateShoulderHandler(shoulderRotatePerSecond *deltaTime);
	}
	if(keys[GLFW_KEY_D]) {
		rotateShoulderHandler(-shoulderRotatePerSecond *deltaTime);
	}
}


void
scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	distance -= yoffset;
	if (distance < minDistance) {
		distance = minDistance;
	} else if (distance > maxDistance) {
		distance = maxDistance;
	}
}

void
updateTime(){
	GLfloat timeThisFrame  = glfwGetTime();
	deltaTime              = timeThisFrame - timeLastFrame;
	timeLastFrame          = timeThisFrame;
}

void
updateRotateTimer(){
	rotateTimer -= deltaTime;
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
	arm   = new Arm(glm::vec3(-7.f, -12.f, 2.f), 14.4f, piece);

	arm->checkRepositionShoulder(shoulderDefaultRotation);
	arm->applyMove();
	auto temp = arm->checkRepositienElbow(elbowDefaultRotation);
	arm->applyMove();

	piece->makePiece();
	piece->canRelocate(temp.x, temp.y);
	piece->applyMove();
	
	cam.addProgram(Tile::program);
	cam.addProgram(arm->program);

	while(!glfwWindowShouldClose(window)) {
		updateTime();
		updateRotateTimer();
		
		
		glClearColor(BG, BG, BG, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.location = glm::vec3(distance  *sin(-glm::radians(orbitAngle)),
								 origin.y,
								 -distance *cos(-glm::radians(orbitAngle)));
		cam.Update();

		board->render();
		piece->render();
		arm->render();
		glfwSwapBuffers(window);

		glfwPollEvents();
		actOnKeys();
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
