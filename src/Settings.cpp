#include "Settings.hpp"


GLuint HEIGHT = 800;
GLuint WIDTH  = HEIGHT /2;

GLfloat ASPECT_RATIO = (GLfloat)WIDTH /(GLfloat)HEIGHT; 

uint ROWS  = 20;
uint COLS  = 10;
uint SROWS = 5;

glm::vec3 origin  = glm::vec3(0.f, 0.f, 0.f);

GLfloat BG = 0.082f;

RangeMap gridMap = RangeMap(0.f, (GLfloat)COLS, -(GLfloat)COLS /2, (GLfloat)COLS /2);

glm::vec3 colors[] {
	glm::vec3(0.753f, 0.224f, 0.169f), // apple
	glm::vec3(0.945f, 0.769f, 0.059f), // banana
	glm::vec3(0.608f, 0.349f, 0.714f), // grape
	glm::vec3(0.180f, 0.8f,   0.443f), // pear
	glm::vec3(0.902f, 0.494f, 0.133f)  // orange
};
