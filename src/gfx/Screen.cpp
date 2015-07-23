#include "gfx/Screen.h"
#include "gfx/Window.h"

void Screen::clear() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::drawRectangle(int x1, int y1, int x2, int y2, f3 colour) {
    x1 *= SCALE;
    y1 *= SCALE;
    x2 *= SCALE;
    y2 *= SCALE;

    glColor3f(colour.x, colour.y, colour.z);
    glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
}
