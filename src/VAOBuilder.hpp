#pragma once

#include <GL/glew.h>

class VAOBuilder {

public:
	static GLuint buildVAO(GLuint& VBO, const GLfloat* vertices, GLuint countV,
						   GLuint& EBO, const GLubyte* indices,  GLuint countI);

private:
	VAOBuilder() {}
	const static GLuint UNBIND = 0;
};
