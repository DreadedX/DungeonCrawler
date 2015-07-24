#include "gfx/TextureLoader.h"

GLuint loadTexture(std::string name) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    uint id = Reader::getId(name);
    // TODO: Find better thing to return when an error has occured
    if (id == 256) {
	Log::print("Could not load texture", ERROR);
	return tex;
    }

    size imageSize = Reader::getImageSize(id);
    byte pixels[imageSize.width * imageSize.height * 3];
    Reader::read(id, pixels);
    for(int i = 0; i < imageSize.width*imageSize.height*3; i += 3) {std::cout << +pixels[i] << " " << +pixels[i+1] << " " << +pixels[i+2] << std::endl; }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageSize.width, imageSize.height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    // glGenerateMipmap(GL_TEXTURE_2D);

    return tex;
}
