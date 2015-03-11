#pragma once
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include <GL/glew.h>

#include <cmath>

#include "VAOBuilder.hpp"
#include "ShaderBuilder.hpp"
#include "Renderable.hpp"
#include "Piece.hpp"
#include "Settings.hpp"

class Arm {
	// for simplicity everything in the arm is based off a simple size value
	// because trying to work out the math with more variables made it difficult for me to keep track of everything and it was sufficient for the purpose
private:
	const static GLubyte order[];
	GLuint mountVAO,
		   mountVBO,
		   mountEBO;
	Renderable* mount;
	// these vao vbo and ebo should be able to be reused for both the bicep and forearm
	GLuint armVAO,
		   armVBO,
		   armEBO;
	Renderable* bicep;
	Renderable* forearm;

	glm::vec3   shoulder;

	GLfloat     shoulderRotation;
	GLfloat     shoulderRotationCheck;

	glm::vec3   elbowDelta;
	glm::vec3   elbowDeltaCheck;

	GLfloat     elbowRotation;
	GLfloat     elbowRotationCheck;

	glm::vec3   handDelta;     
	glm::vec3   handDeltaCheck;
	
	
	GLfloat     sectionLength;

	void syncCheck();
	void syncArm();

public:
	GLuint program;
	Piece* piece;

	Arm(glm::vec3 shoulder, GLfloat length, Piece* piece);
	~Arm();

	glm::vec2 checkRotateShoulder(GLfloat theta);
	glm::vec2 checkRotateElbow   (GLfloat theta);
	
	void applyMove();
	void discardMove();

	void render();
};
