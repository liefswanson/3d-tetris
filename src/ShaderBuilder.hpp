#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

#include "TermColor.hpp"

class ShaderBuilder {

public:
	// the actual order of shaders shouldn't matter in theory,
	// but for clarity the fragment shader should be added second
	static      GLuint linkProgram(GLuint vert, GLuint frag);
	static      GLuint buildShader(const std::string& path, GLuint type);
	
private:
	// should be noted  that the path is only passed for debug purposes
	static      GLuint compile    (const std::string& source, GLuint type,
								   const std::string& path);
	//class is meant to be static!
	ShaderBuilder(){};
};

// odds are this will not be needed outside ShaderBuilder, but it isn't really part of the class
// TODO put in a separate file
std::string readFile (const std::string& path);
