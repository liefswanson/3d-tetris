#pragma once
#include <GL/glew.h>

class RangeMap {

	// internals determining how mapping from one range to another is done
	// linear mapping
	// in practise this is used to map from numbers in a 100 percent range to the normalized grid in opengl
private:
	GLfloat inOffset, outOffset;
	GLfloat ratio;

	// creates a new mappingy
public:
	RangeMap(GLfloat inLow,  GLfloat inHigh,
			 GLfloat outLow, GLfloat outHigh);
	~RangeMap();

	// moves a number from one map to another
	GLfloat map    (GLfloat x);
	GLfloat mapBack(GLfloat x);
};
