#include "ShaderBuilder.hpp"

GLuint
ShaderBuilder::buildShader(const std::string& path, GLuint type){
	auto source = readFile(path);
	return ShaderBuilder::compile(source, type, path);
}

GLuint
ShaderBuilder::linkProgram(GLuint vert, GLuint frag){
	GLuint program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);

	glLinkProgram(program);

	GLint success;

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success){
		GLchar infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << Term::ERROR << " Failed to link shaders" << std::endl;
		std::cout << infoLog << std::endl;
	}
	glDetachShader(program, vert);
	glDetachShader(program, frag);
	return program;
}

GLuint
ShaderBuilder::compile (const std::string& source, GLuint type,
						const std::string& path = "path unspecified"){
	const GLchar* temp = source.c_str();
    
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &temp, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << Term::ERROR << " Failed to compile " <<
			Term::IYellow << path << Term::Reset << std::endl;

		std::cout << infoLog << std::endl;
	}
	
	return shader;
}

std::string
readFile(const std::string& path){
	std::string text;

	try {
		std::stringstream temp;
		
		std::ifstream file(path);
		temp << file.rdbuf();
		file.close();
		text = temp.str();

	} catch(std::exception e) {
		std::cout << Term::ERROR << ' ' << Term::IYellow << path << Term::Reset << " could not be read." << std::endl;
	}
	return text;
}
