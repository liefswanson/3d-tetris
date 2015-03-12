#pragma once
#include <GL/glew.h>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

class Renderable {

public:
	glm::vec3 color;
	glm::vec3 location;
	GLfloat rotation;	

	Renderable (GLuint VAO, GLuint count, GLuint program,
				GLuint mode,
				glm::vec3 color    = glm::vec3(),
				glm::vec3 location = glm::vec3(),
				GLfloat rotation = 0);
	~Renderable();
	
	virtual void render();

private:
	GLuint VAO;
	GLuint count;
	GLuint mode;
	GLuint program;
};
