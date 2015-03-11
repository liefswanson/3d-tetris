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
	glm::vec3   elbow;
	GLfloat     elbowRotation;

	glm::vec3   shoulderCheck;
	GLfloat     shoulderRotationCheck;
	glm::vec3   elbowCheck;
	GLfloat     elbowRotationCheck;

	GLfloat     sectionLength;

public:
	GLuint program;
	Piece* piece;

	Arm(glm::vec3 shoulder, GLfloat length, Piece* piece);
	~Arm();

	bool canRotateShoulder(GLfloat theta);
	bool canRotateElbow(GLfloat theta);
	void applyMove();
	void discardMove();

	void render();
};
