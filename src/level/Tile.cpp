#include "Standard.h"

namespace Tile {
    
    // TODO: Make this automatically determine size
    TileData tiles[TILE_COUNT];

    void create(std::string name, byte type, byte id) {
	
	// Load tile texture
	tiles[id].tex = Texture::load(name);

	// Set tile name
	tiles[id].name = name;

	// Set tile type
	tiles[id].type = type;

	// Print debug message
	Log::print(String::format("Created tile: %s @ %i", name.c_str(), id), DEBUG);
    }

    void render(vec4 position, byte id) {

	// If the tile is the grid tile, do not render it
	if (id != 1) {

	    // Render tile
	    Render::tile(position, tiles[id].tex);
	}
    }
}
