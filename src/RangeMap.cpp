#include "RangeMap.hpp"

RangeMap::RangeMap(GLfloat inLow,  GLfloat inHigh,
				   GLfloat outLow, GLfloat outHigh){
	this->inOffset  = inLow;
	this->outOffset = outLow;

	GLfloat inRange   = inHigh  - inLow;
	GLfloat outRange  = outHigh - outLow;

	this->ratio = outRange / inRange;
}

GLfloat
RangeMap::map(GLfloat x){
	return (x - inOffset) * ratio + outOffset;
}

GLfloat
RangeMap::mapBack(GLfloat x) {
	return (x - outOffset) / ratio + inOffset;
}

RangeMap::~RangeMap(){}
