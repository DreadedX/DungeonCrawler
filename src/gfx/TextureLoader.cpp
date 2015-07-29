#include "Standard.h"

GLuint Texture::load(std::string name) {

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    uint id = Reader::getId(name);
    if (id == 256) {
	std::cerr << "Could not load texture: " << name << std::endl;
	// TODO: Make this not hardcoded
	id = Reader::getId("tile/void");
    }

    std::cout << "Loaded: " << name << " with id: " << tex << std::endl;
    
    v2i imageSize = Reader::getImageSize(id);
    byte pixels[imageSize.x * imageSize.y * 4];
    Reader::read(id, pixels);
    // for(int i = 0; i < imageSize.x*imageSize.y*3; i += 3) {std::cout << +pixels[i] << " " << +pixels[i+1] << " " << +pixels[i+2] << std::endl; }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSize.x, imageSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    return tex;
}
