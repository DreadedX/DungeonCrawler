#include "Standard.h"

void quad(int x1, int y1, int x2, int y2);
void quadTex(int x1, int y1, int x2, int y2, GLuint tex, float texWidth, float texHeight);

void Screen::clear() {

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::drawTile(int x, int y, GLuint tex) {

    quadTex(x-8, y-8, x+8, y+8, tex, 1.0f, 1.0f);
}

void quad(int x1, int y1, int x2, int y2) {

    x1 *= SCALE;
    y1 *= SCALE;
    x2 *= SCALE;
    y2 *= SCALE;

    glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
    glEnd();
}

void quadTex(int x1, int y1, int x2, int y2, GLuint tex, float texWidth, float texHeight) {

    x1 *= SCALE;
    y1 *= SCALE;
    x2 *= SCALE;
    y2 *= SCALE;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x1, y1);
	glTexCoord2f(texWidth, 0.0f);
	glVertex2f(x2, y1);
	glTexCoord2f(texWidth, texHeight);
	glVertex2f(x2, y2);
	glTexCoord2f(0.0f, texHeight);
	glVertex2f(x1, y2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
