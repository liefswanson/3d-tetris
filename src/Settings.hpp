#pragma once
#include <GL/glew.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include "RangeMap.hpp"

extern GLfloat distance;
extern GLfloat angle;
extern GLfloat orbitSpeed;

extern GLuint HEIGHT;
extern GLuint WIDTH;

extern GLfloat ASPECT_RATIO; 

extern uint ROWS;
extern uint COLS;
extern uint SROWS;

extern RangeMap colMap;
extern RangeMap rowMap;

extern glm::vec3 origin;

extern GLfloat BG;
extern glm::vec3 colors[];

enum Fruits {
	APPLE = 0,
	BANANA,
	GRAPE,
	PEAR,
	ORANGE,
	FRUITS
};
