#include "Settings.hpp"

GLfloat distance       = 35.f;
GLfloat angle          = 0.f;
GLfloat orbitSpeed     = 20.f;
GLfloat rotateTimerMax = 0.05f;

GLuint HEIGHT = 800;
GLuint WIDTH  = HEIGHT /2;

GLfloat ASPECT_RATIO = (GLfloat)WIDTH /(GLfloat)HEIGHT; 

uint ROWS  = 25;
uint COLS  = 10;
uint SROWS = 0;

glm::vec3 origin  = glm::vec3(0.f, 0.f, 0.f);

GLfloat BG = 0.082f;

GLfloat LEFT   = -(GLfloat)(COLS) /2;
GLfloat RIGHT  =  (GLfloat)(COLS) /2;
GLfloat TOP    =  (GLfloat)(ROWS-SROWS) /2;
GLfloat BOTTOM = -(GLfloat)(ROWS-SROWS) /2;

RangeMap colMap = RangeMap(0.f,                            (GLfloat)COLS-1,
						   LEFT,   RIGHT);
RangeMap rowMap = RangeMap((GLfloat)ROWS-1.f/ASPECT_RATIO, (GLfloat)SROWS +1,
						   BOTTOM, TOP);

glm::vec3 collideColor = glm::vec3(0.498f, 0.549f, 0.553f);
glm::vec3 gridColor    = glm::vec3(0.608f, 0.349f, 0.714f);
glm::vec3 colors[] {
	glm::vec3(0.753f, 0.224f, 0.169f), // apple
	glm::vec3(0.945f, 0.769f, 0.059f), // banana
	glm::vec3(0.608f, 0.349f, 0.714f), // grape
	glm::vec3(0.180f, 0.8f,   0.443f), // pear
	glm::vec3(0.902f, 0.494f, 0.133f)  // orange
};
