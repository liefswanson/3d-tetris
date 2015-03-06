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
	
	GLfloat vertices[] = {
		// front
		-0.5f,  0.5f,  0.5f, // top left
		 0.5f,  0.5f,  0.5f, // top right
		-0.5f, -0.5f,  0.5f, // bottom left
		 0.5f, -0.5f,  0.5f, // bottom right
		// back
		-0.5f,  0.5f, -0.5f, // top left
		 0.5f,  0.5f, -0.5f, // top right
		-0.5f, -0.5f, -0.5f, // bottom left
		 0.5f, -0.5f, -0.5f, // bottom right
	};

	GLubyte indices[] = {
		0, 1, 3,   0, 2, 3, // Front
		4, 5, 7,   4, 6, 7, // Back
		4, 5, 1,   4, 0, 1, // Top
		6, 7, 3,   6, 2, 3, // Bottom
		1, 5, 7,   1, 3, 7, // Right
		0, 4, 6,   0, 2, 6	// Left
	};

	GLuint     VBO, EBO;
	GLuint     VAO     = VAOBuilder::buildVAO(VBO, vertices, sizeof(vertices) /sizeof(GLfloat),
											  EBO, indices,  sizeof(indices)  /sizeof(GLubyte));

	GLuint     vert    = ShaderBuilder::buildShader("shaders/default.vert", GL_VERTEX_SHADER);
	GLuint     frag    = ShaderBuilder::buildShader("shaders/default.frag", GL_FRAGMENT_SHADER);
	GLuint     program = ShaderBuilder::linkProgram(vert, frag);
	
	Renderable temp    = Renderable(VAO, sizeof(indices) /sizeof(GLubyte), program, GL_TRIANGLES,
									glm::vec3(0.608f, 0.349f, 0.714f)); 
	
	Camera cam = Camera(glm::vec3(0.f, 1.f, 0.f),
						glm::vec3(2.f, 0.f, 2.f),
						glm::vec3(0.f, 0.f, 0.f),
						45.f, (GLfloat)WIDTH/(GLfloat)HEIGHT,
						0.1f, 100.f);
	cam.addProgram(program);
	
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
	
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	glfwTerminate();
	return 0;
}



