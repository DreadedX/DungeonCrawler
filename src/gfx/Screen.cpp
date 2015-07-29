#if !LEGACY
#include "Standard.h"

void quad(int x1, int y1, int x2, int y2);
void quadTex(int x1, int y1, int x2, int y2, GLuint tex, float texWidth, float texHeight);

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

GLuint vertexBuffer;

void Screen::init() {

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Screen::drawTest() {

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}

void Screen::clear() {

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::drawTile(int x, int y, GLuint tex) {

    quadTex(x-8, y-8, x+8, y+8, tex, 1.0f, 1.0f);
#if DRAW_BOX
    drawOutline(x-8, y-8, x+8, y+8);
#endif
}

void Screen::drawOutline(int x1, int y1, int x2, int y2) {

    // x1 *= SCALE;
    // y1 *= SCALE;
    // x2 *= SCALE;
    // y2 *= SCALE;

    glBegin(GL_LINE_STRIP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glVertex2f(x1, y1);
    glEnd();
}

void quad(int x1, int y1, int x2, int y2) {

    // x1 *= SCALE;
    // y1 *= SCALE;
    // x2 *= SCALE;
    // y2 *= SCALE;

    glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
    glEnd();
}

void quadTex(int x1, int y1, int x2, int y2, GLuint tex, float texWidth, float texHeight) {

    // x1 *= SCALE;
    // y1 *= SCALE;
    // x2 *= SCALE;
    // y2 *= SCALE;

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
#endif
