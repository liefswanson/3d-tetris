#include "Settings.hpp"

const GLfloat initDistance   = 35.f;
const GLfloat minDistance    = 10.f;
const GLfloat maxDistance    = 55.f;
	
const GLfloat initOrbitAngle = 0.f;
const GLfloat orbitSpeed     = 20.f;
const GLfloat rotateTimerMax = 0.10f;

const GLfloat shoulderRotatePerSecond = 15.f;
const GLfloat elbowRotatePerSecond    = 15.f;

const GLfloat shoulderDefaultRotation = 115.f;
const GLfloat elbowDefaultRotation    = -15.f;

const GLuint HEIGHT = 800;
const GLuint WIDTH  = HEIGHT /2;

const GLfloat ASPECT_RATIO = (GLfloat)WIDTH /(GLfloat)HEIGHT; 

const uint ROWS  = 25;
const uint COLS  = 10;
const uint SROWS = 0;

const glm::vec3 origin  = glm::vec3(0.f, 0.f, 0.f);

const GLfloat BG = 0.082f;

const GLfloat LEFT   = -(GLfloat)(COLS) /2;
const GLfloat RIGHT  =  (GLfloat)(COLS) /2;
const GLfloat TOP    =  (GLfloat)(ROWS-SROWS) /2;
const GLfloat BOTTOM = -(GLfloat)(ROWS-SROWS) /2;

RangeMap colMap = RangeMap(0.f,                            (GLfloat)COLS-1,
						   LEFT,   RIGHT);
RangeMap rowMap = RangeMap((GLfloat)ROWS-1.f/ASPECT_RATIO, (GLfloat)SROWS +1,
						   BOTTOM, TOP);

const glm::vec3 gridHorizontalMeasurements = glm::vec3(0.2, (GLfloat)ROWS-SROWS+2 +1.2, 0.2);
const glm::vec3 gridVerticalMeasurements   = glm::vec3((GLfloat)COLS+1.2, 0.2, 0.2);

const glm::vec3 armColor     = glm::vec3(0.74f,  0.76f,  0.78f);
const glm::vec3 collideColor = glm::vec3(0.498f, 0.549f, 0.553f);
const glm::vec3 gridColor    = glm::vec3(0.086f, 0.102f, 0.122f);
const glm::vec3 colors[] {
	glm::vec3(0.753f, 0.224f, 0.169f), // apple
	glm::vec3(0.945f, 0.769f, 0.059f), // banana
	glm::vec3(0.608f, 0.349f, 0.714f), // grape
	glm::vec3(0.180f, 0.8f,   0.443f), // pear
	glm::vec3(0.902f, 0.494f, 0.133f)  // orange
};
