#include "Standard.h"

static const GLfloat g_tile_vertex_buffer_data[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,

    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f
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
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,

    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f
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

glm::vec4 view = glm::vec4(0, 0, 10, 1);
// mat4 viewMatrix = translate(IDENTITY, vec3(0));

float fov = 90.0f;
glm::mat4 projectionMatrix = glm::perspective(fov, 16.0f / 9.0f, 0.1f, 200.0f);
// mat4 projectionMatrix = ortho(0, 2, 0, 2, -100, 100);
glm::mat4 viewMatrix = glm::lookAt(glm::vec3(view.x, view.y, view.z), glm::vec3(view.x, view.y, view.z-1), glm::vec3(0, 1, 0));

GLuint vertexArrayID;

// Tiles
GLuint tileVertexBuffer;
GLuint tileUVBuffer;

GLuint tileProgramID;
GLuint tileMatrixID;

// Entity
GLuint entityVertexBuffer;
GLuint entityUVBuffer;

GLuint entityProgramID;
GLuint entityMatrixID;

void Render::init() {

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(33.0f/255.0f, 30.0f/255.0f, 39.0f/255.0f, 1.0f);

    #if not LEGACY
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Tiles
    glGenBuffers(1, &tileVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, tileVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_tile_vertex_buffer_data), g_tile_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &tileUVBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, tileUVBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_tile_uv_buffer_data), g_tile_uv_buffer_data, GL_STATIC_DRAW);

    tileProgramID = Shader::load("shader/tile_vert", "shader/tile_frag");
    tileMatrixID = glGetUniformLocation(tileProgramID, "mvpMatrix");

    // Entity
    glGenBuffers(1, &entityVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, entityVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_entity_vertex_buffer_data), g_entity_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &entityUVBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, entityUVBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_entity_uv_buffer_data), g_entity_uv_buffer_data, GL_STATIC_DRAW);

    entityProgramID = Shader::load("shader/entity_vert", "shader/entity_frag");
    entityMatrixID = glGetUniformLocation(entityProgramID, "mvpMatrix");

    #else
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // TODO: Try and make this work
    // gluPerspective(fov, 4.0f / 3.0f, 0.1f, 200.0f);
    glOrtho(0,32,0,18,-100, 100);
    #endif
}

void Render::clear() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::move(glm::vec4 toMove) {

    view += toMove;
    #if not LEGACY
    viewMatrix = glm::lookAt(glm::vec3(view.x, view.y, view.z), glm::vec3(view.x, view.y, view.z-1), glm::vec3(0, 1, 0));
    #else
    glTranslatef(-toMove.x, -toMove.y, -toMove.z);
    #endif
}

glm::vec4 Render::getPosition() {

    return view;
}

void Render::startTile() {

    #if not LEGACY
    glUseProgram(tileProgramID);
    glBindVertexArray(vertexArrayID);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, tileVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, tileUVBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glActiveTexture(GL_TEXTURE0);
    #else
    glEnable(GL_TEXTURE_2D);
    #endif
}

void Render::tile(glm::vec4 position, GLuint tex) {

    #if not LEGACY
    // TODO: Use instancing to draw the tiles
    glm::mat4 modelMatrix = glm::translate(IDENTITY, glm::vec3(position.x, position.y, position.z));
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

    if (activeTexture != tex) {

	glBindTexture(GL_TEXTURE_2D, tex);

	activeTexture = tex;
    }

    glUniformMatrix4fv(tileMatrixID, 1, GL_FALSE, &mvpMatrix[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 2*3);
    #else
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(position.x, position.y, 0);

    glTexCoord2f(1, 0);
    glVertex3f(position.x+1.0f, position.y, 0);

    glTexCoord2f(1, 1);
    glVertex3f(position.x+1.0f, position.y+1.0f, 0);

    glTexCoord2f(0, 1);
    glVertex3f(position.x, position.y+1.0f, 0);
    glEnd();
    #endif
}

void Render::endTile() {

    #if not LEGACY
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    #else
    glDisable(GL_TEXTURE_2D);
    #endif
}

void Render::startEntity() {

    #if not LEGACY
    glUseProgram(entityProgramID);
    glBindVertexArray(vertexArrayID);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, entityVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, entityUVBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glActiveTexture(GL_TEXTURE0);
    #endif
}

void Render::entity(glm::vec4 position, glm::vec4 scale, float mAngle, GLuint tex) {

    #if not LEGACY
    glm::mat4 rotateMatrix = glm::rotate(IDENTITY, mAngle, glm::vec3(0, 0, 1));
    glm::mat4 scaleMatrix = glm::scale(IDENTITY, glm::vec3(scale.x, scale.y, scale.z));
    glm::mat4 modelMatrix = glm::translate(IDENTITY, glm::vec3(position.x, position.y, position.z));
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix *
	glm::translate(IDENTITY, glm::vec3(scale.x/2, scale.y/2, scale.z/2)) *
	rotateMatrix *
	glm::translate(IDENTITY, glm::vec3(-scale.x/2, -scale.y/2, -scale.z/2)) *
	scaleMatrix;

    if (activeTexture != tex) {

	glBindTexture(GL_TEXTURE_2D, tex);

	activeTexture = tex;
    }

    glUniformMatrix4fv(entityMatrixID, 1, GL_FALSE, &mvpMatrix[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 2*3);
    #else
    
    glPushMatrix();
    glTranslatef(position.x, position.y, 0);
    glRotatef(mAngle*57.2974, 0, 0, 1);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-scale.x/2, -scale.y/2, 0);

    glTexCoord2f(1, 0);
    glVertex3f(scale.x/2, -scale.y/2, 0);

    glTexCoord2f(1, 1);
    glVertex3f(scale.x/2, scale.y/2, 0);

    glTexCoord2f(0, 1);
    glVertex3f(-scale.x/2, scale.y/2, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    #endif
}

void Render::endEntity() {

    #if not LEGACY
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    #endif
}
