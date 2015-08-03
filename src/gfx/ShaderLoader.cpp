# include "Standard.h"

namespace Shader {

    void readShader(std::string fileName, std::vector<char> &buffer);
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
	// glUseProgram(shaderProgram);

	Log::print(String::format("Succesfully compiled shader: %s, %s", nameVert, nameFrag), DEBUG);

	return shaderProgram;
    }

    void readShader(std::string fileName, std::vector<char> &buffer) {

	// TODO: Make shaders load from asset file
	// TODO: Add error handeling to opening files
	std::ifstream file(fileName, std::ios::in | std::ios::binary);

	if(!file.is_open()) {
	    Log::print(String::format("Failed to open shader: %s", fileName.c_str()), ERROR);
	}

	file.seekg(0, std::ios::end);
	int length = file.tellg();
	file.seekg(0, std::ios::beg);

	buffer.resize(length + 1);
	file.read(&buffer[0], length);
	file.close();
	buffer[length] = '\0';
    }

    GLuint compileShader(std::string name, GLenum shaderType) {

	std::vector<char> buffer;
	readShader(name, buffer);
	const char *src = &buffer[0];

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
