#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include <GL/glew.h>

#include <cmath>
#include <vector>

class Camera {
public:
	// control the view
	glm::vec3 up;
	glm::vec3 location;
	glm::vec3 target;

	// control the projection
	GLfloat fov;
	GLfloat aspectRatio;
	GLfloat near;
	GLfloat far;
	
	Camera(glm::vec3 up, glm::vec3 location, glm::vec3 target,
		   GLfloat fov,  GLfloat aspectRatio,
		   GLfloat near, GLfloat far);
	~Camera();

	// propogate changes to the shader
	void Update();

	void addProgram(GLuint program);
	
private:
	// list of shader programs which this camera applies to
	// typically this would be all the programs which are being used within the fustrum
	// or just every program running in the context
	std::vector<GLuint> programs;

	// there is only one view and projection per camera.
	// in theory this should only be applied once per frame.
	// However, they will be applied to EVERY program bound to the camera.
	glm::mat4 view;
	glm::mat4 projection;
};
