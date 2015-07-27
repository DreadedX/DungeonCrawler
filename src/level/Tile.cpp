#include "Standard.h"

// TODO: Make this automatically determine size
uint tiles[256] = {0x00};

void createTile(std::string name, byte id) {

    tiles[id] = loadTexture(name) - 1;
}

void Tile::render(int x, int y, byte id) {

    Screen::drawTile(x, y, tiles[id] + 1);
}
