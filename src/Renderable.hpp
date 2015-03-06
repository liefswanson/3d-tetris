#pragma once
#include <GL/glew.h>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

class Renderable {

public:
	glm::vec3 color;
	glm::vec3 location;
	glm::vec3 rotation;	

	Renderable (GLuint VAO, GLuint count, GLuint program,
				GLuint mode,
				glm::vec3 color    = glm::vec3(),
				glm::vec3 location = glm::vec3(),
				glm::vec3 rotation = glm::vec3());
	~Renderable();
	
	void render();

private:
	GLuint VAO;
	GLuint count;
	GLuint mode;
	GLuint program;
};
