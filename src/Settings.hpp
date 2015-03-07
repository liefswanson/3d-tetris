#pragma once
#include <GL/glew.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

const GLuint HEIGHT = 800;
const GLuint WIDTH  = HEIGHT /2;

const GLfloat ASPECT_RATIO = (GLfloat)WIDTH /(GLfloat)HEIGHT; 

const uint ROWS  = 20;
const uint COLS  = 10;
const uint SROWS = 5;


const GLfloat BG = 0.082f;

const glm::vec3 origin  = glm::vec3(0.f, 0.f, 0.f);

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
