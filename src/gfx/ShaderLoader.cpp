# include "Standard.h"

namespace Shader {

    GLuint compileShader(std::string name, GLenum shaderType);

    GLuint load(const char *nameVert, const char *nameFrag) {

	GLuint vertexShader = compileShader(nameVert, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(nameFrag, GL_FRAGMENT_SHADER);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glLinkProgram(shaderProgram);

	Log::print(String::format("Compiled shader: %s, %s", nameVert, nameFrag), DEBUG);

	return shaderProgram;
    }

    GLuint compileShader(std::string name, GLenum shaderType) {

	// Make the max size automatically adjust depending on the size of the shader
	byte buffer[1000] = {0x00};
	int id = IO::Reader::getId(name);
	IO::Reader::read(id, buffer);
	const char *src = (const char*)buffer;

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	GLint test = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
	if(!test) {
	    Log::print(String::format("Shader (%s) compilation failed with message:", name.c_str()), ERROR);
	    std::vector<char> compilation_log(512);
	    glGetShaderInfoLog(shader, compilation_log.size(), NULL, &compilation_log[0]);
	    Log::print(String::format("%s", &compilation_log[0]), ERROR);
	    Window::terminate();
	    exit(-1);
	}

	return shader;
    }
}
