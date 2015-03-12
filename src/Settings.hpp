#pragma once
#include <GL/glew.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include "RangeMap.hpp"

extern const GLfloat initDistance;
extern const GLfloat minDistance;
extern const GLfloat maxDistance;

extern const GLfloat initOrbitAngle;
extern const GLfloat orbitSpeed;
extern const GLfloat shoulderRotatePerSecond;
extern const GLfloat elbowRotatePerSecond;
extern const GLfloat shoulderDefaultRotation;
extern const GLfloat elbowDefaultRotation;

extern const GLfloat rotateTimerMax;

extern const GLuint HEIGHT;
extern const GLuint WIDTH;

extern const GLfloat ASPECT_RATIO; 

extern const uint ROWS;
extern const uint COLS;
extern const uint SROWS;

extern const glm::vec3 gridVerticalMeasurements;
extern const glm::vec3 gridHorizontalMeasurements;

extern const GLfloat LEFT, RIGHT,
	                 TOP,  BOTTOM;

extern RangeMap colMap;
extern RangeMap rowMap;

extern const glm::vec3 origin;

extern const GLfloat BG;
extern const glm::vec3 armColor;
extern const glm::vec3 collideColor;
extern const glm::vec3 gridColor;
extern const glm::vec3 colors[];

enum Fruits {
	APPLE = 0,
	BANANA,
	GRAPE,
	PEAR,
	ORANGE,
	FRUITS
};
