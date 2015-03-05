#pragma once

#include <GL/glew.h>

class VAOBuilder {

public:
	static GLuint buildVAO(GLfloat* vertices, GLuint countV,
						   GLuint*  indices,  GLuint countI);

private:
	VAOBuilder() {}
	const static GLuint UNBIND = 0;
};
