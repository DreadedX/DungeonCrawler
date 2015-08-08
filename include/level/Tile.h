#ifndef TILE_H
#define TILE_H

namespace Tile {

    struct TileData {

	GLuint tex = 0x00;
	std::string name = "";
	byte type = 0x00;
    };
	
    void init(int tileCount);
    void create(std::string name, byte type, byte id);
    void render(vec4 position, byte id);
    void end();
};

#endif

