# include "Standard.h"

static const GLfloat g_text_box_vertex_buffer_data[] = {
    0.0f, 0.0f, 0.0f,
    WIDTH, 0.0f, 0.0f,
    WIDTH, HEIGHT/4, 0.0f,

    WIDTH, HEIGHT/4, 0.0f,
    0.0f, HEIGHT/4, 0.0f,
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

struct TextBoxObject {

    int index = 0;
    bool end = false;

    std::vector<std::string> lines;
    std::vector<Text::TextObject*> textLines;

    TextBoxObject(std::string text) {

	// TODO: Make this devide the text in lines
	lines.push_back(text);
    }

    bool canContinue() {

	return (index == 3 || end);
    }
};

TextBoxObject *currentTextBox = nullptr;

GLuint guiVertexArrayID;

GLuint textBoxVertexBuffer;
GLuint textBoxUVBuffer;

GLuint textBoxProgramID;

void TextBox::add(std::string text) {

    if (currentTextBox != nullptr) {

	for (auto& t : currentTextBox->textLines) {

	    t->display = false;
	    t = nullptr;
	}

	delete currentTextBox;
	currentTextBox = nullptr;
    }

    currentTextBox = new TextBoxObject(text);
}

void TextBox::init() {

    #if not LEGACY
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
    #endif
}

void TextBox::tick() {

    // TODO: Make the game pause when a textbox is on screen
    if (currentTextBox != nullptr) {

	bool next = true;

	bool continueText = Input::isPressed(Key::CONTINUE);

	// TODO: This code needs to be cleaned up
	for (auto& t : currentTextBox->textLines) {

	    if (t->charIndex < t->text.length()) {

		next = false;
	    } else {

		if (!continueText) {

		    next = false;
		}
	    }

	    if (t != nullptr && t->charIndex >= t->text.length() +  50.0f && currentTextBox->index < 3) {

		next = true;
	    }
	}

	if (next && continueText && currentTextBox->canContinue()) {
	    for (auto& t : currentTextBox->textLines) {

		// TODO: Move this improved version back into GUI
		t->display = false;
		t = nullptr;

		currentTextBox->index = 0;
		currentTextBox->end = false;
	    }
	}

	// TODO: Move this improved version back into GUI
	currentTextBox->textLines.erase(
		std::remove_if(std::begin(currentTextBox->textLines), std::end(currentTextBox->textLines),
		    [](Text::TextObject *textObject) {

		    return textObject == nullptr;
		    }),
		std::end(currentTextBox->textLines));

	if (next) {

	    if (currentTextBox->lines.size() > 0) {

		currentTextBox->textLines.push_back(Text::add(currentTextBox->lines[0], glm::ivec4(15.0f, HEIGHT/4 - 30.0f - (currentTextBox->index * 21.0f), 0, 1), 0.5f, glm::ivec4(1, 1, 1, 1), 1.5f));

		currentTextBox->lines.erase(currentTextBox->lines.begin());

		currentTextBox->index++;
	    } else {

		currentTextBox->end = true;
	    }
	}

	Game::setPaused(true);

	if (currentTextBox->textLines.size() == 0) {

	    delete currentTextBox;
	    currentTextBox = nullptr;

	    Game::setPaused(false);
	}
    }
}

void TextBox::render() {

    static GLuint tex = Texture::load("textbox");

    #if not LEGACY
    
    if (currentTextBox != nullptr) {

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
    }
    #endif
}

void TextBox::end() {

    if (currentTextBox != nullptr) {

	delete currentTextBox;
	currentTextBox = nullptr;
    }
}
