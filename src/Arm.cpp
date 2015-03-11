#include "Arm.hpp"

const GLubyte
Arm::order[] = {
	0, 1, 3,   0, 2, 3, // Front
	4, 5, 7,   4, 6, 7, // Back
	4, 5, 1,   4, 0, 1, // Top
	6, 7, 3,   6, 2, 3, // Bottom
	1, 5, 7,   1, 3, 7, // Right
	0, 4, 6,   0, 2, 6	// Left
};

Arm::Arm(glm::vec3 shoulder, GLfloat length, Piece* piece) {

	GLuint vert   = ShaderBuilder::buildShader("shaders/default.vert", GL_VERTEX_SHADER);
	GLuint frag   = ShaderBuilder::buildShader("shaders/default.frag", GL_FRAGMENT_SHADER);
	Arm::program  = ShaderBuilder::linkProgram(vert, frag);

	glDeleteShader(vert);
	glDeleteShader(frag);

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	
	GLfloat x = 2.f;
	GLfloat y = 0.5f;
	GLfloat z = 1.f;

	GLfloat mountVertices[] = {
		// front
		-x,  y,  z, // top left
		 x,  y,  z, // top right
		-x, -y,  z, // bottom left
		 x, -y,  z, // bottom right
		// back
		-x,  y, -z, // top left
		 x,  y, -z, // top right
		-x, -y, -z, // bottom left
		 x, -y, -z  // bottom right
	};

	mountVAO =VAOBuilder::buildVAO(mountVBO, mountVertices, sizeof(mountVertices)/sizeof(GLfloat),
								   mountEBO, Arm::order,    sizeof(Arm::order)   /sizeof(GLubyte));
	
	x = 0.5f  *length;
	y = 0.05f *x;
	z = 0.05f *x;
	
	GLfloat armVertices[] = {
		// front
		-x,  y,  z, // top left
		 x,  y,  z, // top right
		-x, -y,  z, // bottom left
		 x, -y,  z, // bottom right
		// back
		-x,  y, -z, // top left
		 x,  y, -z, // top right
		-x, -y, -z, // bottom left
		 x, -y, -z  // bottom right
	};

	armVAO  = VAOBuilder::buildVAO(armVBO, armVertices, sizeof(armVertices) /sizeof(GLfloat),
								   armEBO, Arm::order,  sizeof(Arm::order)  /sizeof(GLubyte));

	this->shoulder    = shoulder;
	shoulderRotation  = 0;
	elbowDelta        = glm::vec3();
	elbowRotation     = 0;
	handDelta         = glm::vec3();

	sectionLength = length;

	mount   = new Renderable(mountVAO, sizeof(order) /sizeof(GLubyte),
							 program, GL_TRIANGLES, color, shoulder);

	bicep   = new Renderable(armVAO,  sizeof(order) /sizeof(GLubyte),
							 program, GL_TRIANGLES, color);

	forearm = new Renderable(armVAO,  sizeof(order) /sizeof(GLubyte),
							 program, GL_TRIANGLES, color);
}

Arm::~Arm(){
	glDeleteProgram     (Arm::program);

	glDeleteVertexArrays(1, &armVAO);
	glDeleteBuffers     (1, &armVBO);
	glDeleteBuffers     (1, &armEBO);

	
	glDeleteVertexArrays(1, &mountVAO);
	glDeleteBuffers     (1, &mountVBO);
	glDeleteBuffers     (1, &mountEBO);

	delete mount;
	delete bicep;
	delete forearm;
}

glm::vec2
Arm::checkRotateShoulder(GLfloat theta) {
	shoulderRotationCheck = shoulderRotation +glm::radians(theta);
	elbowDeltaCheck.x = cos(shoulderRotationCheck)*sectionLength;
	elbowDeltaCheck.y = sin(shoulderRotationCheck)*sectionLength;
	elbowDeltaCheck.z = 0;
	
	return checkRotateElbow(0);
}

glm::vec2
Arm::checkRotateElbow(GLfloat theta) {
	elbowRotationCheck = elbowRotation +glm::radians(theta);
	handDeltaCheck.x = cos(elbowRotationCheck)*sectionLength;
	handDeltaCheck.y = sin(elbowRotationCheck)*sectionLength;
	handDeltaCheck.z = 0;

	return glm::vec2(shoulder.x + elbowDeltaCheck.x + handDeltaCheck.x,
					 shoulder.y + elbowDeltaCheck.y + handDeltaCheck.y);
}

glm::vec2
Arm::checkRepositionShoulder(GLfloat theta) {
	shoulderRotationCheck = glm::radians(theta);
	elbowDeltaCheck.x = cos(shoulderRotationCheck)*sectionLength;
	elbowDeltaCheck.y = sin(shoulderRotationCheck)*sectionLength;
	elbowDeltaCheck.z = 0;
	
	return checkRotateElbow(0);
}

glm::vec2
Arm::checkRepositienElbow(GLfloat theta) {
	elbowRotationCheck = glm::radians(theta);
	handDeltaCheck.x = cos(elbowRotationCheck)*sectionLength;
	handDeltaCheck.y = sin(elbowRotationCheck)*sectionLength;
	handDeltaCheck.z = 0;

	return glm::vec2(shoulder.x + elbowDeltaCheck.x + handDeltaCheck.x,
					 shoulder.y + elbowDeltaCheck.y + handDeltaCheck.y);
}

void
Arm::syncArm(){
	shoulderRotation  = shoulderRotationCheck;
	elbowDelta        = elbowDeltaCheck;
	elbowRotation     = elbowRotationCheck;
	handDelta         = handDeltaCheck;

	bicep->rotation   = shoulderRotation;
	forearm->rotation = elbowRotation;
	bicep->location   = shoulder + 0.5f *elbowDeltaCheck;
	forearm->location = shoulder +       elbowDeltaCheck + 0.5f *handDeltaCheck;
}

void
Arm::syncCheck(){
	shoulderRotationCheck = shoulderRotation;
	elbowDeltaCheck	      =	elbowDelta;       
	elbowRotationCheck    = elbowRotation;    
	handDeltaCheck	      = handDelta;        
}

void
Arm::applyMove(){
	syncArm();
}

void
Arm::discardMove(){
	syncCheck();
}

void
Arm::render(){
	mount->render();
	bicep->render();
	forearm->render();
}
