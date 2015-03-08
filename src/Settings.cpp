#include "Settings.hpp"

GLfloat distance      = 22.f;
GLfloat angle         = 0.f;
GLfloat orbitSpeed    = 20.f;

GLuint HEIGHT = 800;
GLuint WIDTH  = HEIGHT /2;

GLfloat ASPECT_RATIO = (GLfloat)WIDTH /(GLfloat)HEIGHT; 

uint ROWS  = 25;
uint COLS  = 10;
uint SROWS = 5;

glm::vec3 origin  = glm::vec3(0.f, 0.f, 0.f);

GLfloat BG = 0.082f;

RangeMap colMap = RangeMap(0.f, (GLfloat)COLS-1, -(GLfloat)COLS /2, (GLfloat)COLS /2);
RangeMap rowMap = RangeMap((GLfloat)SROWS +1, (GLfloat)ROWS-1.f/ASPECT_RATIO, -(GLfloat)(ROWS-SROWS) /2, (GLfloat)(ROWS-SROWS) /2);


glm::vec3 colors[] {
	glm::vec3(0.753f, 0.224f, 0.169f), // apple
	glm::vec3(0.945f, 0.769f, 0.059f), // banana
	glm::vec3(0.608f, 0.349f, 0.714f), // grape
	glm::vec3(0.180f, 0.8f,   0.443f), // pear
	glm::vec3(0.902f, 0.494f, 0.133f)  // orange
};
