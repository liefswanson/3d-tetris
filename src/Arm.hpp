#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include <GL/glew.h>

#include "VAOBuilder.hpp"
#include "ShaderBuilder.hpp"
#include "Renderable.hpp"
#include "Piece.hpp"
#include "Settings.hpp"

class Arm {
private:
	Renderable mount;
	glm::vec3  shoulder;
	Renderable bicep;
	glm::vec3  elbow;
	Renderable forearm;
	
	Piece* piece;

	Arm();
	~Arm();

	
	
};
