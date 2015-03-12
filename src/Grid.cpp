#include "Grid.hpp"

const GLubyte
Grid::order[] = {
	0, 1, 3,   0, 2, 3, // Front
	4, 5, 7,   4, 6, 7, // Back
	4, 5, 1,   4, 0, 1, // Top
	6, 7, 3,   6, 2, 3, // Bottom
	1, 5, 7,   1, 3, 7, // Right
	0, 4, 6,   0, 2, 6	// Left
};

Grid::Grid(){
	GLuint vert   = ShaderBuilder::buildShader("shaders/default.vert", GL_VERTEX_SHADER);
	GLuint frag   = ShaderBuilder::buildShader("shaders/default.frag", GL_FRAGMENT_SHADER);
	program       = ShaderBuilder::linkProgram(vert, frag);

	glDeleteShader(vert);
	glDeleteShader(frag);

	GLfloat x = gridVerticalMeasurements.x *.5f;
	GLfloat y = gridVerticalMeasurements.y *.5f;
	GLfloat z = gridVerticalMeasurements.z *.5f;

	GLfloat vVertices[] = {
		// front
		-x,  y,  z, // top left
		 x,  y,  z, // top right
		-x, -y,  z, // bottom left
		 x, -y,  z, // bottom right
		// back
		-x,  y, -z, // top left
		 x,  y, -z, // top right
		-x, -y, -z, // bottom left
		 x, -y, -z  // bottom right
	};

	VVAO = VAOBuilder::buildVAO(VVBO, vVertices,   sizeof(vVertices)/sizeof(GLfloat),
								VEBO, Grid::order, sizeof(Grid::order)   /sizeof(GLubyte));

	x = gridHorizontalMeasurements.x *.5f;
	y = gridHorizontalMeasurements.y *.5f;
	z = gridHorizontalMeasurements.z *.5f;

	GLfloat hVertices[] = {
		// front
		-x,  y,  z, // top left
		 x,  y,  z, // top right
		-x, -y,  z, // bottom left
		 x, -y,  z, // bottom right
		// back
		-x,  y, -z, // top left
		 x,  y, -z, // top right
		-x, -y, -z, // bottom left
		 x, -y, -z  // bottom right
	};

	HVAO = VAOBuilder::buildVAO(HVBO, hVertices,   sizeof(hVertices)/sizeof(GLfloat),
								HEBO, Grid::order, sizeof(Grid::order)   /sizeof(GLubyte));

	vertical   = new Renderable(VVAO, sizeof(order) /sizeof(GLubyte),
							  program, GL_TRIANGLES, gridColor);

	horizontal = new Renderable(HVAO, sizeof(order) /sizeof(GLubyte),
							  program, GL_TRIANGLES, gridColor);
}

void
Grid::render() {
	auto offset = -.5f;
	for(uint row = SROWS+1; row < ROWS-SROWS; row++ ){
		vertical->location = glm::vec3(0.f,
									   rowMap.map((GLfloat)row +offset),
									   0.f);
		vertical->render();
	}

	for(uint col = 0; col < COLS+1; col++ ){
		horizontal->location = glm::vec3(colMap.map((GLfloat)col +offset),
									   0.f,
									   0.f);
		horizontal->render();
	}
}

Grid::~Grid(){
	glDeleteProgram     (program);

	glDeleteVertexArrays(1, &VVAO);
	glDeleteBuffers     (1, &VVBO);
	glDeleteBuffers     (1, &VEBO);

	
	glDeleteVertexArrays(1, &HVAO);
	glDeleteBuffers     (1, &HVBO);
	glDeleteBuffers     (1, &HEBO);

	delete vertical;
	delete horizontal;
}
