#include "gfx/Screen.h"

void Screen::clear() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::drawRectangle(int x1, int y1, int x2, int y2, GLuint tex) {
    x1 *= SCALE;
    y1 *= SCALE;
    x2 *= SCALE;
    y2 *= SCALE;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x1, y1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(x2, y1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x2, y2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(x1, y2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // glColor3f(1.0f, 1.0f, 1.0f);
}
