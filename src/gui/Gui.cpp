#include "Standard.h"

static const GLfloat g_text_box_vertex_buffer_data[] = {
    0.0f, 0.0f, 0.0f,
    WIDTH, 0.0f, 0.0f,
    WIDTH, HEIGHT/3, 0.0f,

    WIDTH, HEIGHT/3, 0.0f,
    0.0f, HEIGHT/3, 0.0f,
    0.0f, 0.0f, 0.0f
};

static const GLfloat g_text_box_uv_buffer_data[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f
};

// TODO: The pointers in this array need to be updated to where the pointers in Text.cpp are pointing to
std::vector<Text::TextObject*> lines;

GLuint guiVertexArrayID;

GLuint textBoxVertexBuffer;
GLuint textBoxUVBuffer;

GLuint textBoxProgramID;

void textBoxInit() {

    glGenVertexArrays(1, &guiVertexArrayID);
    glBindVertexArray(guiVertexArrayID);

    // Tiles
    glGenBuffers(1, &textBoxVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, textBoxVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_text_box_vertex_buffer_data), g_text_box_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &textBoxUVBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, textBoxUVBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_text_box_uv_buffer_data), g_text_box_uv_buffer_data, GL_STATIC_DRAW);

    textBoxProgramID = Shader::load("shader/tile_vert", "shader/tile_frag");

    glUseProgram(textBoxProgramID);
    glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));
    glUniformMatrix4fv(glGetUniformLocation(textBoxProgramID, "mvpMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);
}

void Gui::init() {

    Text::init("font/aesymatt");

    textBoxInit();
}

void Gui::printLine(std::string mText) {

    for (auto& line : lines) {

	line->position.y += 15;
    }

    lines.push_back(Text::add(mText, glm::ivec4(1.0f, 3.0f, 0, 1), 0.5f, glm::ivec4(1, 1, 1, 1), 1.5f));
}

void lineTick() {

    lines.erase(
	    std::remove_if(std::begin(lines), std::end(lines),
		[](Text::TextObject *textObject) {

		return !textObject->display;
		}),
	    std::end(lines));

    // TODO: This causes a crash because the object is deleted, but is not set to nullptr in the array in Gui.cpp, only in Text.cpp
    for (auto& line : lines) {

	if (line->charIndex >= line->text.length()+60) {

	    line->color.w -= 0.05f;

	    if (line->color.w <= 0) {

		line->destroy();
	    }
	}
    }
}

void Gui::tick() {

    lineTick();

    // NOTE: This needs to be called last, else it will cause nullpointers
    Text::tick();
}

void textBoxRender() {

    static GLuint tex = Texture::load("textbox");

    #if not LEGACY

    glUseProgram(textBoxProgramID);
    glBindVertexArray(guiVertexArrayID);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, textBoxVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, textBoxUVBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, tex);

    glDrawArrays(GL_TRIANGLES, 0, 2*3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    #endif
}

void Gui::render() {

    textBoxRender();
    Text::render();

    // Game::stop(0);
}
