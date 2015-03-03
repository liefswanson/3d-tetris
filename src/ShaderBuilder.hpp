#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

#include "TermColor.hpp"

class ShaderBuilder {

public:
	static      GLuint build   (const std::string& path, GLuint type);
	
private:
	static std::string readFile(const std::string& path);
	// should be noted  that the path is only passed for debug purposes
	static      GLuint compile (const std::string& source, GLuint type,
		                        const std::string& path);
	
};
