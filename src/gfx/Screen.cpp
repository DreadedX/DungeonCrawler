#include "Standard.h"

void quad(int x1, int y1, int x2, int y2);
void quadTex(int x1, int y1, int x2, int y2, GLuint tex, float texWidth, float texHeight);

GLfloat vertices_position[8] = {
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.5f, 0.5f,
    -0.5f, 0.5f

    // 0.0f, 0.0f,
    // 0.0f, 0.5f,
    // -0.5f, 0.5f,
    //
    // 0.0f, 0.0f,
    // -0.5f, 0.0f,
    // -0.5f, -0.5f,
    //
    // 0.0f, 0.0f,
    // 0.0f, -0.5f,
    // 0.5f, -0.5f
};

GLuint vao;
void Screen::init() {
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_position), vertices_position, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint shaderProgram = Shader::load("shaders/test.vert", "shaders/test.frag");
    GLint positionAttribute = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(positionAttribute);
}

void Screen::drawVao() {
    glBindVertexArray(vao);
    glDrawArrays(GL_QUADS, 0, 4);
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
