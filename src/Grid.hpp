#pragma once

#include "VAOBuilder.hpp"
#include "ShaderBuilder.hpp"
#include "Renderable.hpp"
#include "Settings.hpp"

class Grid {
public:
	Grid();
	~Grid();

	GLuint program;
	
	void render();
	
private:
	GLuint HVAO, HVBO, HEBO;
	GLuint VVAO, VVBO, VEBO;

	const static GLubyte order[];
	
	Renderable* vertical;
	Renderable* horizontal;
};
