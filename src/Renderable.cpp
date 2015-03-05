#include "Renderable.hpp"

Renderable::Renderable(GLuint VAO, GLuint count, GLuint program){
	this->VAO     = VAO;
	this->count  = count;
	this->program = program;
}

Renderable::~Renderable(){}

void
Renderable::render() {
	glUseProgram(program);
	GLuint modelLoc = glGetUniformLocation(program, "model");
	GLuint colorLoc = glGetUniformLocation(program, "color");

	glm::mat4 model;
	model = glm::rotate   (model, glm::radians(1.f), rotation);
	model = glm::translate(model, location);
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv      (colorLoc, 1,           glm::value_ptr(color));
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	// glBindVertexArray(0);
}
