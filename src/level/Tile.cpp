#include "Standard.h"

// TODO: Make this automatically determine size
uint tiles[256] = {0x00};

void Tile::create(std::string name, byte id) {
    tiles[id] = Texture::load(name) - 1;
}

void Tile::render(vec4 position, byte id) {
    if (id != 1) {
	Render::tile(position, tiles[id] + 1);
    }
}
