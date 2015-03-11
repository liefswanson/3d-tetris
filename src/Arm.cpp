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

	this->shoulder = shoulder;
	sectionLength = length;
	
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

	mount = new Renderable(mountVAO, sizeof(order) /sizeof(GLubyte), program, GL_TRIANGLES,
						   color,    shoulder);
	
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

	bicep = new Renderable(armVAO,  sizeof(order) /sizeof(GLubyte),
						   program, GL_TRIANGLES, color,
						   glm::vec3(shoulder.x +cos(0)*sectionLength*.5f,
									 shoulder.y +sin(0)*sectionLength*.5f,
									 shoulder.z));

	elbow = glm::vec3(shoulder.x +cos(0)*sectionLength,
					  shoulder.y +sin(0)*sectionLength,
					  shoulder.z);
	forearm = new Renderable(armVAO,  sizeof(order) /sizeof(GLubyte),
							 program, GL_TRIANGLES, color,
							 elbow);
						   // glm::vec3(bicep->location.x +cos(0)*sectionLength*.5f,
						   // 			 bicep->location.y +sin(0)*sectionLength*.5f,
						   // 			 bicep->location.z));
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

bool
Arm::canRotateShoulder(GLfloat theta) {
	bicep->rotation = bicep->rotation +glm::radians(theta);
	bicep->location = glm::vec3(shoulder.x +cos(bicep->rotation)*sectionLength*.5f,
	  							shoulder.y +sin(bicep->rotation)*sectionLength*.5f,
	  							shoulder.z);
	
	elbow = glm::vec3(shoulder.x +cos(bicep->rotation)*sectionLength,
					  shoulder.y +sin(bicep->rotation)*sectionLength,
					  shoulder.z);
	
	return canRotateElbow(0);
}

bool
Arm::canRotateElbow(GLfloat theta) {
	forearm->rotation = forearm->rotation +glm::radians(theta);
	forearm->location = glm::vec3(elbow.x +cos(forearm->rotation)*sectionLength*.5f,
								  elbow.y +sin(forearm->rotation)*sectionLength*.5f,
								  elbow.z);
	return true;
}

void
Arm::render(){
	mount->render();
	bicep->render();
	forearm->render();
}
