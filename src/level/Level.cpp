#include "Standard.h"

namespace Level {
    // TODO: This should be done by the shader
    const mat4 tileScale = scale(IDENTITY, vec3(Level::tileScaleInt));
    const mat4 tileOffset = translate(IDENTITY, vec3(8, 8, 0));

    Entity entity;

    // TODO: Make this not hardcoded
    byte layout[Level::height][Level::width];
    byte layout0[Level::height][Level::width];

    void init() {

	uint idList[255] {0x00};
	IO::Reader::getWithType(TYPE_TILE, idList);

	// for (uint i = 0; i < sizeof(idList)/sizeof(uint); i++) {
	// std::string name = IO::Reader::getName(idList[i]);
	//
	// if (name == IO::Reader::getName(0) && i != 0) {
	//     break;
	// }
	//
	// Tile::create(name, i);
	// }
	// TODO: This is only hardcoded because else it can't load the existing debug_level, convert the test level to new format
	Tile::create("tile/void", 0);
	Tile::create("tile/grid", 1);
	Tile::create("tile/brickDark", 2);
	Tile::create("tile/brickLight", 3);
	Tile::create("tile/window00", 4);
	Tile::create("tile/window01", 5);
	Tile::create("tile/window02", 6);
	Tile::create("tile/window03", 7);
	Tile::create("tile/window04", 8);
	Tile::create("tile/window05", 9);
	Tile::create("tile/window06", 10);
	Tile::create("tile/window07", 11);
	Tile::create("tile/window08", 12);
	Tile::create("tile/window09", 13);
	Tile::create("tile/window10", 14);
	Tile::create("tile/window11", 15);
	Tile::create("tile/flag00", 16);
	Tile::create("tile/flag01", 17);
	Tile::create("tile/flag02", 18);
	Tile::create("tile/flag03", 19);
	Tile::create("tile/flag04", 20);
	Tile::create("tile/flag05", 21);
	Tile::create("tile/flag06", 22);
	Tile::create("tile/flag07", 23);
	Tile::create("tile/flag08", 24);
	Tile::create("tile/flag09", 25);
	Tile::create("tile/flag10", 26);
	Tile::create("tile/flag11", 27);
	Tile::create("tile/pillar", 28);
	Tile::create("tile/block", 29);

	int layoutID = IO::Reader::getId("level");
	// TODO: Load width and height from file
	byte layout1d[width * height];
	IO::Reader::read(layoutID, layout1d);

	for (int y = 0; y < height; y++) {
	    for (int x = 0; x < width; x++) {
		layout[y][x] = layout1d[(y * width) + x];
	    }
	}

	int layout0ID = IO::Reader::getId("level0");
	// TODO: Load width and height from file
	byte layout01d[width * height];
	IO::Reader::read(layout0ID, layout01d);

	for (int y = 0; y < height; y++) {
	    for (int x = 0; x < width; x++) {
		layout0[y][x] = layout01d[(y * width) + x];
	    }
	}

	entity.init();
    }

    void tick() {

	entity.tick();
    }

    void render() {

	for (int y = 0; y < height; y++) {
	    for (int x = 0; x < width; x++) {
		vec4 position = vec4 (x, y, 0, 1);
		// TODO: This should be done by the shader
		position = tileOffset * tileScale * position;

		if (!Input::isPressed(GLFW_KEY_2)) {
		    // Tile::render(position, layout0[y][x]);
		}
		if (!Input::isPressed(GLFW_KEY_1)) {
		    Tile::render(position, layout[y][x]);
		}
	    }

	}

	entity.render();

	Render::outline(tileScale * vec4(width/2, height/2, 0, 1), vec2(16*width, 16*height), vec4(1, 0, 0, 1));
    }

    void end() {
	// delete entity;
    }

    Entity* getPlayer() {
	return &entity;
    }
}
