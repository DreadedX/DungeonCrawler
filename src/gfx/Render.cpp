#if !LEGACY
#include "Standard.h"

namespace Render {

    static const GLfloat g_tile_vertex_buffer_data[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,

	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
    };

    static const GLfloat g_tile_uv_buffer_data[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,

	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f
    };

    static const GLfloat g_font_vertex_buffer_data[] = {
	0.0f, 0.0f, 0.0f,
	0.8f, 0.0f, 0.0f,
	0.8f, 1.0f, 0.0f,

	0.8f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f
    };

    static const GLfloat g_font_uv_buffer_data[] = {
	0.0f, 0.0f,
	0.012195f, 0.0f,
	0.012195f, 1.0f,

	0.012195f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f
    };

    static const GLfloat g_background_vertex_buffer_data[] = {
	-170.0f, 0.0f, 0.0f,
	170.0f, 0.0f, 0.0f,
	170.0f, 100.0f, 0.0f,

	170.0f, 100.0f, 0.0f,
	-170.0f, 100.0f, 0.0f,
	-170.0f, 0.0f, 0.0f
    };

    vec4 view = vec4(0, 0, 10, 1);
    // mat4 viewMatrix = translate(IDENTITY, vec3(0));

    float fov = 90.0f;
    mat4 projectionMatrix = perspective(fov, 4.0f / 3.0f, 0.1f, 200.0f);
    // mat4 projectionMatrix = ortho(0, 2, 0, 2, -100, 100);
    mat4 viewMatrix = lookAt(vec3(view.x, view.y, view.z), vec3(view.x, view.y, view.z-1), vec3(0, 1, 0));
    
    GLuint VertexArrayID;

    // Tiles
    GLuint tileVertexBuffer;
    GLuint tileUVBuffer;

    GLuint tileProgramID;
    GLuint tileMatrixID;

    GLuint tileTextureHandler;

    // Font
    GLuint fontVertexBuffer;
    GLuint fontUVBuffer;

    GLuint fontProgramID;
    GLuint fontMatrixID;

    GLuint fontTextureHandler;
    GLuint fontColor;
    GLuint fontIndex;

    // Background
    GLuint backgroundVertexBuffer;
    GLuint backgroundUVBuffer;

    GLuint backgroundProgramID;
    GLuint backgroundMatrixID;

    GLuint backgroundTextureHandler;

    void init() {
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(171.0f/255.0f, 106.0f/255.0f, 140.0f/255.0f, 1.0f);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Tiles
	glGenBuffers(1, &tileVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tileVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_tile_vertex_buffer_data), g_tile_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &tileUVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tileUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_tile_uv_buffer_data), g_tile_uv_buffer_data, GL_STATIC_DRAW);

	tileProgramID = Shader::load("shaders/tile_vertex", "shaders/tile_fragment");
	tileMatrixID = glGetUniformLocation(tileProgramID, "mvpMatrix");

	tileTextureHandler = glGetUniformLocation(tileProgramID, "textureSampler");

	// Background
	glGenBuffers(1, &fontVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, fontVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_font_vertex_buffer_data), g_font_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &fontUVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, fontUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_font_uv_buffer_data), g_font_uv_buffer_data, GL_STATIC_DRAW);

	fontProgramID = Shader::load("shaders/font_vertex", "shaders/font_fragment");
	fontMatrixID = glGetUniformLocation(fontProgramID, "mvpMatrix");

	fontTextureHandler = glGetUniformLocation(fontProgramID, "textureSampler");
	fontIndex = glGetUniformLocation(fontProgramID, "index");
	fontColor = glGetUniformLocation(fontProgramID, "vertexColor");
	
	// Background
	glGenBuffers(1, &backgroundVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, backgroundVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_background_vertex_buffer_data), g_background_vertex_buffer_data, GL_STATIC_DRAW);
    }

    void clear() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void move(vec4 toMove) {

	view += toMove;
	viewMatrix = lookAt(vec3(view.x, view.y, view.z), vec3(view.x, view.y, view.z-1), vec3(0, 1, 0));
    }

    void tile(vec4 position, GLuint tex) {

	glUseProgram(tileProgramID);

	mat4 modelMatrix = translate(IDENTITY, vec3(position.x, position.y, position.z));
	mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(tileMatrixID, 1, GL_FALSE, &mvpMatrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(tileTextureHandler, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, tileVertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, tileUVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glDrawArrays(GL_TRIANGLES, 0, 2*3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
    }

    void background(vec4 position, GLuint tex) {

	glUseProgram(tileProgramID);
	glBindVertexArray(VertexArrayID);

	mat4 modelMatrix = translate(IDENTITY, vec3(position.x, position.y, position.z));
	mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(tileMatrixID, 1, GL_FALSE, &mvpMatrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(tileTextureHandler, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, backgroundVertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, tileUVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glDrawArrays(GL_TRIANGLES, 0, 2*3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
    }

    void font(vec4 position, vec4 color, GLuint tex, int index) {

	glUseProgram(fontProgramID);

	mat4 modelMatrix = translate(IDENTITY, vec3(position.x, position.y, position.z));
	mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(fontMatrixID, 1, GL_FALSE, &mvpMatrix[0][0]);
	glUniform4f(fontColor, color.x, color.y, color.z, color.w);
	glUniform1i(fontIndex, index);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(fontTextureHandler, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, fontVertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, fontUVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glDrawArrays(GL_TRIANGLES, 0, 2*3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
    }

    void outline(vec4 modelMatrix , vec2 size, vec4 color) {
    }
    void outlineAbs(vec4 modelMatrix , vec2 size, vec4 color) {
    }

    void quad(vec4 modelMatrix , vec2 size, vec4 color) {
    }
    void quadAbs(vec4 modelMatrix, vec2 size, vec4 color) {
    }

    void quadTex(vec4 modelMatrix, vec2 size, GLuint tex, vec4 uv) {
    }
    void quadTexAbs(vec4 position, vec2 size, GLuint tex, vec4 uv) {
    }
}
#endif
