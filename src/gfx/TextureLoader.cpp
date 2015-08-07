#include "Standard.h"

namespace Texture {

    GLuint load(std::string name) {

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLfloat largest_supported_anisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_supported_anisotropy);

	vec2 imageSize = vec2(2, 2);
	byte *pixels;
	pixels = new byte[(int) (imageSize.x * imageSize.y * 4)] {
	    255,   0, 255, 255,      0,   0,   0, 255,
	    0,   0,   0, 255,    255,   0, 255, 255
	};

	uint id = IO::Reader::getId(name);
	if (id == 256) {
	    Log::print(String::format("Could not load texture: %s", name.c_str()), WARNING);
	    // TODO: Make this not hardcoded
	} else {
	    imageSize = IO::Reader::getImageSize(id);
	    pixels = new byte[(int) (imageSize.x * imageSize.y * 4)];
	    IO::Reader::read(id, pixels);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSize.x, imageSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	Log::print(String::format("Loaded texture: %s @ %i", name.c_str(), tex), DEBUG);
	delete[] pixels;
	return tex;
    }
}
