#include "VAOBuilder.hpp"

GLuint
VAOBuilder::buildVAO(GLfloat* vertices, GLuint countV,
					 GLuint*  indices,  GLuint countI) {
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers     (1, &VBO);
	glGenBuffers     (1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,         VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER,         sizeof(GLfloat) *countV, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)  *countI, indices,  GL_STATIC_DRAW);

	// make sure the array buffer is in fact reading in 3 dimensions properly
	// FIXME this may be a bug
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(UNBIND);
	glBindBuffer     (GL_ARRAY_BUFFER,         UNBIND);
	glBindBuffer     (GL_ELEMENT_ARRAY_BUFFER, UNBIND);

	// make sure this is legal...
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return VAO;
}
