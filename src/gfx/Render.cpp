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

    static const GLfloat g_entity_vertex_buffer_data[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,

	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
    };

    static const GLfloat g_entity_uv_buffer_data[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,

	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f
    };

    static uint activeTexture = 0;

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
    
    // Entity
    GLuint entityVertexBuffer;
    GLuint entityUVBuffer;

    GLuint entityProgramID;
    GLuint entityMatrixID;

    GLuint entityTextureHandler;

    void init() {
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(33.0f/255.0f, 30.0f/255.0f, 39.0f/255.0f, 1.0f);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Tiles
	glGenBuffers(1, &tileVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tileVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_tile_vertex_buffer_data), g_tile_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &tileUVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tileUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_tile_uv_buffer_data), g_tile_uv_buffer_data, GL_STATIC_DRAW);
	
	tileProgramID = Shader::load("shaders/tile_vert", "shaders/tile_frag");
	tileMatrixID = glGetUniformLocation(tileProgramID, "mvpMatrix");

	tileTextureHandler = glGetUniformLocation(tileProgramID, "textureSampler");
	
	// Entity
	glGenBuffers(1, &entityVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, entityVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_entity_vertex_buffer_data), g_entity_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &entityUVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, entityUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_entity_uv_buffer_data), g_entity_uv_buffer_data, GL_STATIC_DRAW);

	entityProgramID = Shader::load("shaders/entity_vert", "shaders/entity_frag");
	entityMatrixID = glGetUniformLocation(entityProgramID, "mvpMatrix");

	tileTextureHandler = glGetUniformLocation(entityProgramID, "textureSampler");
    }

    void clear() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void move(vec4 toMove) {

	view += toMove;
	viewMatrix = lookAt(vec3(view.x, view.y, view.z), vec3(view.x, view.y, view.z-1), vec3(0, 1, 0));
    }

    vec4 getPosition() {

	return view;
    }

    void startTile() {

	glUseProgram(tileProgramID);
	glBindVertexArray(VertexArrayID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, tileVertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, tileUVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    }

    void tile(vec4 position, GLuint tex) {

	// TODO: Use instancing to draw the tiles
	mat4 modelMatrix = translate(IDENTITY, vec3(position.x, position.y, position.z));
	mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

	if (activeTexture != tex) {

	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, tex);
	    glUniform1i(tileTextureHandler, 0);

	    activeTexture = tex;
	}

	glUniformMatrix4fv(tileMatrixID, 1, GL_FALSE, &mvpMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 2*3);
    }

    void endTile() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
    }

    void startEntity() {

	glUseProgram(entityProgramID);
	glBindVertexArray(VertexArrayID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, entityVertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, entityUVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    }

    void entity(vec4 position, vec4 scale, GLuint tex) {

	mat4 scaleMatrix = glm::scale(IDENTITY, vec3(scale.x, scale.y, scale.z));
	mat4 modelMatrix = translate(IDENTITY, vec3(position.x, position.y, position.z));
	mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix * scaleMatrix;

	if (activeTexture != tex) {

	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, tex);
	    glUniform1i(entityTextureHandler, 0);

	    activeTexture = tex;
	}

	glUniformMatrix4fv(entityMatrixID, 1, GL_FALSE, &mvpMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 2*3);
    }

    void endEntity() {
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
    }
}
