#include "Standard.h"

// TODO: The pointers in this array need to be updated to where the pointers in Text.cpp are pointing to
std::vector<Text::TextObject*> lines;

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

void Gui::render() {

    Text::render();
}
