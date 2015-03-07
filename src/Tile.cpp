#include "Tile.hpp"

GLuint Tile::VAO     = 0;
GLuint Tile::VBO     = 0;
GLuint Tile::EBO     = 0;
GLuint Tile::program = 0;

const GLubyte
Tile::order[] = {
	0, 1, 3,   0, 2, 3, // Front
	4, 5, 7,   4, 6, 7, // Back
	4, 5, 1,   4, 0, 1, // Top
	6, 7, 3,   6, 2, 3, // Bottom
	1, 5, 7,   1, 3, 7, // Right
	0, 4, 6,   0, 2, 6	// Left
};

void
Tile::init(glm::vec3 size) {
	GLfloat x = 0.5f *size.x;
	GLfloat y = 0.5f *size.y;
	GLfloat z = 0.5f *size.z;

	GLfloat vertices[] = {
		// front
		-x,  y,  z, // top left
		 x,  y,  z, // top right
		-x, -y,  z, // bottom left
		 x, -y,  z, // bottom right
		// back
		-x,  y, -z, // top left
		 x,  y, -z, // top right
		-x, -y, -z, // bottom left
		 x, -y, -z, // bottom right
	};

	Tile::VAO  = VAOBuilder::buildVAO(Tile::VBO, vertices,    sizeof(vertices)    /sizeof(GLfloat),
									  Tile::EBO, Tile::order, sizeof(Tile::order) /sizeof(GLubyte));

	GLuint vert   = ShaderBuilder::buildShader("shaders/default.vert", GL_VERTEX_SHADER);
	GLuint frag   = ShaderBuilder::buildShader("shaders/default.frag", GL_FRAGMENT_SHADER);
	Tile::program = ShaderBuilder::linkProgram(vert, frag);

	glDetachShader(Tile::program, vert);
	glDeleteShader(vert);

	glDetachShader(Tile::program, frag);
	glDeleteShader(frag);
}

void
Tile::clean(){
	glDeleteProgram     (Tile::program);

	glDeleteVertexArrays(1, &Tile::VAO);
	glDeleteBuffers     (1, &Tile::VBO);
	glDeleteBuffers     (1, &Tile::EBO);
}

Tile::Tile(uint fruit)
	: Renderable(VAO, sizeof(order) /sizeof(GLubyte), program,
				 GL_TRIANGLES,
				 colors[fruit]) {
	_fruit = fruit;
}

Tile::~Tile(){}

uint
Tile::fruit() {
	return _fruit;
}
