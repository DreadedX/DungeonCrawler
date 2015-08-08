# include "Standard.h"

namespace Shader {

    GLuint compileShader(std::string name, GLenum shaderType);

    GLuint load(const char *nameVert, const char *nameFrag) {

	// Compile the shaders
	GLuint vertexShader = compileShader(nameVert, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(nameFrag, GL_FRAGMENT_SHADER);

	// Create new shader program
	GLuint shaderProgram = glCreateProgram();

	// Attacht the shaders to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Delete the individual shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Link the shader program
	glLinkProgram(shaderProgram);

	// Print debug message
	Log::print(String::format("Compiled shader: %s, %s", nameVert, nameFrag), DEBUG);

	// Return the id of the shader program
	return shaderProgram;
    }

    GLuint compileShader(std::string name, GLenum shaderType) {

	// TODO: Make the max size automatically adjust depending on the size of the shader
	// Create buffer for reading shader
	byte buffer[1000] = {0x00};

	// Get the file id of the requested shader and read it
	int id = IO::Reader::getId(name);
	IO::Reader::read(id, buffer);

	// Turn the byte array into a char array
	const char *src = (const char*)buffer;

	//Create a new shader
	GLuint shader = glCreateShader(shaderType);

	// Set the shader source and compile
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	// Check the compile status of the shader
	GLint status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	// If the compile failed
	if (!status) {

	    // Print that an error has occured
	    Log::print(String::format("Shader (%s) compilation failed with message:", name.c_str()), ERROR);

	    // Read the error message
	    std::vector<char> compilation_log(512);
	    glGetShaderInfoLog(shader, compilation_log.size(), NULL, &compilation_log[0]);

	    // Print the error message
	    Log::print(String::format("%s", &compilation_log[0]), ERROR);

	    // End game
	    Game::stop(ERROR_SHADER_COMPILE);
	}

	// Return shader id
	return shader;
    }
}
