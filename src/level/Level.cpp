#include "Standard.h"

const int width = 8;
const int height = 4;

// TODO: Make this not hardcoded
byte layout[height][width];

Entity entity;

void Level::init() {

    uint idList[255] {0x00};
    Reader::getWithType(TYPE_TILE, idList);
    
    for (uint i = 0; i < sizeof(idList)/sizeof(uint); i++) {
	std::string name = Reader::getName(idList[i]);

	if (name == Reader::getName(0) && i != 0) {
	    break;
	}
    
    	createTile(name, i);
    }

    int layoutID = Reader::getId("level");
    // TODO: Load width and height from file
    byte layout1d[width * height];
    Reader::read(layoutID, layout1d);

    for (int y = 0; y < height; y++) {
	for (int x = 0; x < width; x++) {
	    layout[y][x] = layout1d[(y * width) + x];
    	}
    }

    entity.init();
}

void Level::tick() {

    entity.tick();
}

void Level::render() {

    for (int y = 0; y < height; y++) {
	for (int x = 0; x < width; x++) {
	    Tile::render((x << 4) + 8, (y << 4) + 8, layout[y][x]);
    	}

    }

    entity.render();
}
