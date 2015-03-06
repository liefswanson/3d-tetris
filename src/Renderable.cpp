#include "Renderable.hpp"

Renderable::Renderable(GLuint VAO, GLuint count, GLuint program,
					   GLuint mode,
					   glm::vec3 color,
					   glm::vec3 location,
					   glm::vec3 rotation){
	this->VAO      = VAO;
	this->count    = count;
	this->mode     = mode;
	this->program  = program;

	
	this->color    = color;
	this->location = location;
	this->rotation = rotation;
}

Renderable::~Renderable(){}

void
Renderable::render() {
	glUseProgram(program);

	GLuint modelLoc = glGetUniformLocation(program, "model");
	glm::mat4 model;
	// FIXME cannot rotate
	// model = glm::rotate   (model, glm::radians(1.f), rotation);
	model = glm::translate(model, location);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	
	GLuint colorLoc = glGetUniformLocation(program, "rgb");
	glUniform3fv      (colorLoc, 1,           glm::value_ptr(color));
	
	glBindVertexArray(VAO);
	glDrawElements(mode, count, GL_UNSIGNED_BYTE, 0);
	glBindVertexArray(0);
}
