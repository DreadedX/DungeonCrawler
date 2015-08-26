# include "Standard.h"

struct Character {
    GLuint tex;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};

GLuint vao;
GLuint vbo;

GLuint textProgramID;

std::map<GLchar, Character> characters;

std::vector<Text::TextObject*> textObjects;

void Text::init(std::string fontName) {

    #if not LEGACY
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    textProgramID = Shader::load("shader/text_vert", "shader/text_frag");

    glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));
    glUseProgram(textProgramID);
    glUniformMatrix4fv(glGetUniformLocation(textProgramID, "projection"), 1, GL_FALSE, &projectionMatrix[0][0]);

    FT_Library ft;
    if(FT_Init_FreeType(&ft)) {

	Log::print("Could not load FreeType library", ERROR);
	Game::stop(ERROR_FT);
    }

    FT_Face face;
    // TODO: Load the font from the gaff file
    Log::print(String::format("%s.ttf", fontName.c_str()).c_str(), DEBUG);
    if(FT_New_Face(ft, String::format("%s.ttf", fontName.c_str()).c_str(), 0, &face)) {

	Log::print("Could not load font", ERROR);
	Game::stop(ERROR_FONT);
    }

    FT_Set_Pixel_Sizes(face, 0, 40);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c< 128; c++) {

	if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {

	    Log::print("Could not load glyph", ERROR);
	    continue;
	}

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		face->glyph->bitmap.width,
		face->glyph->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		face->glyph->bitmap.buffer
		);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	Character character = {
	    tex,
	    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
	    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
	    (GLuint)face->glyph->advance.x
	};
	characters.insert(std::pair<GLchar, Character>(c, character));

	Log::print(String::format("tex: %i, sizew: %i, sizeh: %i, bearingl: %i, bearingt: %i, advance: %i", tex, character.size.x, character.size.y, character.bearing.x, character.bearing.y, (character.advance >> 6)), DEBUG);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    #endif
}

// TODO: This needs to retrun some kind of identifier, so that it can be removed from the array later on
Text::TextObject *Text::add(std::string mText, glm::ivec4 mPosition, GLfloat mScale, glm::vec4 mColor, float mSpeed = 0.0f) {

    TextObject *textObject = new TextObject{mText, mPosition, mScale, mColor, mSpeed};

    if (mSpeed == 0) {

	textObject->charIndex = mText.length();
	textObject->speed = 0;
    }
    
    textObjects.push_back(textObject);

    return textObject;
}

void Text::tick() {

    for (auto& t : textObjects) {

	t->charIndex += t->speed * VT;

	if (!t->display) {

	    // TODO: Make this free memory, currently causes SIGSEGV
	    // delete t;
	    t = nullptr;
	}
    }

    textObjects.erase(
	    std::remove_if(std::begin(textObjects), std::end(textObjects),
		[](TextObject *textObject) {

		return textObject == nullptr;
		}),
	    std::end(textObjects));
}

void Text::render() {

    #if not LEGACY
    for (auto& t : textObjects) {

	std::string text = t->text.substr(0, glm::min((int)t->charIndex, (int)t->text.length()));
	glm::ivec4 position = t->position;
	float scale = t->scale;
	glm::vec4 color = t->color;
	
	glUseProgram(textProgramID);
	glUniform4f(glGetUniformLocation(textProgramID, "textColor"), color.x, color.y, color.z, color.w);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {

	    Character ch = characters[*c];

	    GLfloat xpos = position.x + ch.bearing.x * scale;
	    GLfloat ypos = position.y - (ch.size.y - ch.bearing.y) * scale;

	    GLfloat w = ch.size.x * scale;
	    GLfloat h = ch.size.y * scale;

	    GLfloat vertices[6][4] = {
		{xpos, ypos + h, 0.0, 0.0},
		{xpos, ypos, 0.0, 1.0},
		{xpos + w, ypos, 1.0, 1.0},

		{xpos, ypos + h, 0.0, 0.0},
		{xpos + w, ypos, 1.0, 1.0},
		{xpos + w, ypos + h, 1.0, 0.0}
	    };

	    // Render::startTile();
	    // Render::tile(glm::vec4(xpos, ypos, 0.0f, 1.0f), ch.tex);
	    // Render::endTile();

	    glBindTexture(GL_TEXTURE_2D, ch.tex);
	    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	    glEnableVertexAttribArray(0);
	    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	    glDrawArrays(GL_TRIANGLES, 0, 6);

	    glDisableVertexAttribArray(0);
	    glBindBuffer(GL_ARRAY_BUFFER, 0);

	    position.x += (ch.advance >> 6) * scale;
	}
	glBindVertexArray(0);
    }
    #endif
}
