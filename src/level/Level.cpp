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
		vec4 position = vec4 (x, height-y, 0, 1);

		if (!Input::isPressed(GLFW_KEY_2)) {
		    Tile::render(position, layout0[y][x]);
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
