#include "ShaderBuilder.hpp"

using namespace std;

GLuint
ShaderBuilder::build(const std::string& path, GLuint type){
	auto source = readFile(path);
	return compile(source, type, path);
}

std::string
ShaderBuilder::readFile(const std::string& path){
	string text;

	try {
		stringstream temp;
		
		ifstream file(path);
		temp << file.rdbuf();
		file.close();
		text = temp.str();

	} catch(exception e) {
		cout << Term::ERROR << "file " << Term::IYellow << path << Term::Reset << " could not be read." << endl;
	}
	return text;
}

GLuint
ShaderBuilder::compile (const std::string& source, GLuint type, const std::string& path){
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

		std::cout << Term::INFO << std::endl << infoLog << std::endl;
	}
	
	return shader;
}
