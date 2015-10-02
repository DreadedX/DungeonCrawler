#include "Standard.h"


// TODO: The pointers in this array need to be updated to where the pointers in Text.cpp are pointing to
std::vector<Text::TextObject*> lines;

void Gui::init() {

    Text::init("font/aesymatt");

    TextBox::init();
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

    TextBox::tick();

    // NOTE: This needs to be called last, else it will cause nullpointers
    Text::tick();

    // Inventory ui code
    Manager *manager = Level::getManager();
    auto items = manager->getEntitiesByGroup(GROUP_INVENTORY);

    // TODO: This should propably move into the inventory component
    static uint currentItem = 0;

    for (uint i = 0; i < 16; i++) {

	std::string itemName = "";
	if (manager->getEntitiesByGroup(GROUP_INVENTORY).size() > i) {

	    itemName = items[i]->getComponent<ItemComponent>().name;
	} else {

	    break;
	}

	std::string suffix = "";
	if (i == currentItem) {

	    suffix = " *";
	}

	Text::add(String::format("%s %s", itemName.c_str(), suffix.c_str()), glm::ivec4(2, HEIGHT-(10*(i+1)), 0, 1), 0.25f, glm::ivec4(1, 1, 1, 1), 0)->display = false;
    }

    // TODO: This should propably move into the inventory component
    if (Input::isPressed(Key::ITEM_DOWN)) {

	Input::setState(Key::ITEM_DOWN, false);

	currentItem++;
    }
    if (Input::isPressed(Key::ITEM_UP)) {

	Input::setState(Key::ITEM_UP, false);

	currentItem--;
    }
}

void Gui::render() {

    TextBox::render();
    Text::render();

    // Game::stop(0);
}

void Gui::end() {

    Text::end();
    TextBox::end();
}
