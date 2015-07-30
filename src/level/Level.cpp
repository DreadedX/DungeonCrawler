#include "Standard.h"

const int width = 8;
const int height = 4;

// TODO: This should be done by the shader
const mat4 tileScale = scale(IDENTITY, vec3(16));
const mat4 tileOffset = translate(IDENTITY, vec3(8, 8, 0));

Entity entity;

// TODO: Make this not hardcoded
byte layout[height][width];

void Level::init() {

    uint idList[255] {0x00};
    IO::Reader::getWithType(TYPE_TILE, idList);
    
    for (uint i = 0; i < sizeof(idList)/sizeof(uint); i++) {
	std::string name = IO::Reader::getName(idList[i]);

	if (name == IO::Reader::getName(0) && i != 0) {
	    break;
	}
    
	Tile::create(name, i);
    }

    int layoutID = IO::Reader::getId("level");
    // TODO: Load width and height from file
    byte layout1d[width * height];
    IO::Reader::read(layoutID, layout1d);

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
	    vec4 position = vec4 (x, y, 0, 1);
	    // TODO: This should be done by the shader
	    position = tileOffset * tileScale * position;

	    Tile::render(position, layout[y][x]);
    	}

    }

    entity.render();

#if DRAW_BOX
    Screen::drawOutline(0, 0, WIDTH, HEIGHT);
#endif
}

void Level::end() {
    // delete entity;
}

Entity* Level::getPlayer() {
    return &entity;
}
