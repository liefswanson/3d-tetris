#pragma once

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include <GL/glew.h>

#include "VAOBuilder.hpp"
#include "ShaderBuilder.hpp"
#include "Renderable.hpp"

enum
Fruits {
	APPLE = 0,
	BANANA,
	GRAPE,
	PEAR,
	ORANGE,
	FRUITS
};

const glm::vec3
colors[] {
	glm::vec3(0.753f, 0.224f, 0.169f), // apple
	glm::vec3(0.945f, 0.769f, 0.059f), // banana
	glm::vec3(0.608f, 0.349f, 0.714f), // grape
	glm::vec3(0.180f, 0.8f,   0.443f), // pear
	glm::vec3(0.902f, 0.494f, 0.133f)  // orange
};

class Tile : public Renderable {
public:
	Tile(uint fruit);
	~Tile();

	uint fruit();

	static void init(glm::vec3 size = glm::vec3(1.f, 1.f, 1.f));
	static void clean();

	static GLuint VAO, VBO, EBO;
	static GLuint program;

private:
	uint _fruit;

	static const GLubyte order[];

	static bool intitialized;
};
