#include "Standard.h"

namespace Texture {

    GLuint load(std::string name) {

	// Create texture
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// TODO: Check if this actually works
	// Set anisotropic filtering
	GLfloat largest_supported_anisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_supported_anisotropy);

	// Create vector containing fallback image size
	vec2 imageSize = vec2(2, 2);

	// Create pixel data array filled with a fallback texture
	byte *pixels;
	pixels = new byte[(int) (imageSize.x * imageSize.y * 4)] {
	    255,   0, 255, 255,      0,   0,   0, 255,
	    0,   0,   0, 255,    255,   0, 255, 255
	};

	// Get the file id
	uint id = IO::Reader::getId(name);

	// Check if the file was found
	if (id != FILE_NOT_FOUND) {

	    // Set the image size
	    imageSize = IO::Reader::getImageSize(id);

	    // Free memory
	    delete[] pixels;

	    // Read the image data
	    pixels = new byte[(int) (imageSize.x * imageSize.y * 4)];
	    IO::Reader::read(id, pixels);
	} else {

	    // Print error in case the file does not exist
	    Log::print(String::format("Could not load texture: %s", name.c_str()), WARNING);
	}

	// Put the texture in the GPU memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSize.x, imageSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	// Print debug message
	Log::print(String::format("Loaded texture: %s @ %i", name.c_str(), tex), DEBUG);

	// Free memory
	delete[] pixels;

	// Return texture id
	return tex;
    }
}
