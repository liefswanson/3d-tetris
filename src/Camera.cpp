#include "Camera.hpp"

Camera::Camera(glm::vec3 up, glm::vec3 location, glm::vec3 target,
			   GLfloat fov,  GLfloat aspectRatio,
			   GLfloat near, GLfloat far) {
	this->up          = up;
	this->location    = location;
	this->target      = target;

	this->fov         = fov;
	this->aspectRatio = aspectRatio;
	this->near        = near;
	this->far         = far;

	view              = glm::lookAt(target-location, location, up);
	projection        = glm::perspective(fov, aspectRatio,
										 near, far);
}

Camera::~Camera(){}

void
Camera::addProgram(GLuint program){
	programs.push_back(program);
}

void
Camera::removeProgram(GLuint program){
	auto index = std::find(programs.begin(), programs.end(), program);
	if (index != programs.end()) {
		programs.erase(index);
	}
}

void
Camera::Update(){
	view       = glm::lookAt(target-location, location, up);
	projection = glm::perspective(fov, aspectRatio, near, far);
	
	for(uint i = 0; i < programs.size(); i++){
		GLuint temp;
		temp = glGetUniformLocation(programs[i], "view");
		glUniformMatrix4fv(temp, 1, GL_FALSE, glm::value_ptr(view));

		temp = glGetUniformLocation(programs[i], "projection");
		glUniformMatrix4fv(temp, 1, GL_FALSE, glm::value_ptr(projection));
	}
}
