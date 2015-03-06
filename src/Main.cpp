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
		angle -= 20.f * deltaTime;
	}
	if(keys[GLFW_KEY_RIGHT]) {
		angle += 20.f * deltaTime;
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

	Camera cam = Camera(glm::vec3(0.f, 1.f, 0.f),
						glm::vec3(2.f, 0.f, 2.f),
						glm::vec3(0.f, 0.f, 0.f),
						45.f, (GLfloat)WIDTH/(GLfloat)HEIGHT,
						0.1f, 100.f);
	cam.addProgram(Tile::program);

	Tile temp  = Tile(ORANGE);
	
	while(!glfwWindowShouldClose(window)) {
		updateTime();
		glfwPollEvents();
		actOnKeys();
		
		glClearColor(BG, BG, BG, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.location = glm::vec3(distance * sin(-glm::radians(angle)),
								 0.f,
								 -distance * cos(-glm::radians(angle)));
		cam.Update();

        temp.render();
		glfwSwapBuffers(window);
	}

	Tile::clean();
	
	glfwTerminate();
	return 0;
}
