#ifndef TILE_H
#define TILE_H

void createTile(std::string name, byte id);

class Tile {
	
    public:
	static void render(int x, int y, byte id);
};

#endif

