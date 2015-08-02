#if !LEGACY
#include "Standard.h"

namespace Render {

    static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f
    };

    void quad(int x1, int y1, int x2, int y2);
    void quadTex(int x1, int y1, int x2, int y2, GLuint tex, float texWidth, float texHeight);

    GLuint vertexBuffer;

    void init() {

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    }

    void clear() {

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void test() {

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
    }

    void tile(vec4 position, GLuint tex) {

	quadTex(position.x-8, position.y-8, position.x+8, position.y+8, tex, 1.0f, 1.0f);
#if DRAW_BOX
	outline(position, 16, 16);
#endif
    }

    void outline(vec4 position , int width, int height) {

	glBegin(GL_LINE_STRIP);
	glVertex2f(position.x-width/2, position.y-height/2);
	glVertex2f(position.x+width/2, position.y-height/2);
	glVertex2f(position.x+width/2, position.y+height/2);
	glVertex2f(position.x-width/2, position.y+height/2);
	glVertex2f(position.x-width/2, position.y-height/2);
	glEnd();
    }

    void quad(int x1, int y1, int x2, int y2) {

	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
    }

    void quadTex(int x1, int y1, int x2, int y2, GLuint tex, float texWidth, float texHeight) {

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
}
#endif
