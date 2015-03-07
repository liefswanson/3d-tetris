#pragma once

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include <GL/glew.h>

#include "VAOBuilder.hpp"
#include "ShaderBuilder.hpp"
#include "Renderable.hpp"
#include "Settings.hpp"

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
