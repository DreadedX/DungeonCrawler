#include "Standard.h"

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

		    return textObject == nullptr;
		}),
	    std::end(lines));

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

    Text::tick();

    lineTick();
}

void Gui::render() {

    Text::render();
}
