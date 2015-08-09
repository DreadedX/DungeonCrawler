#include "Standard.h"

namespace Level {

    Player *player;

    byte *layout;

    vec2 levelSize;

    void init() {

	// Get a count of all tiles
	int tileCount = IO::Reader::countWithType(TYPE_TILE);
	//
	// Make a list of all files classified as tiles
	uint idList[tileCount];
	IO::Reader::getWithType(TYPE_TILE, idList);

	// Initialize the tiles
	Tile::init(tileCount);

	Log::print(String::format("Tile count: %i", tileCount), DEBUG);

	// Load each tile
	for (int i = 0; i < tileCount; i++) {

	    // Get the name associated with the id
	    std::string name = IO::Reader::getName(idList[i]);

	    // Get tile type
	    byte type = IO::Reader::getType(idList[i]);

	    // Create a tile
	    Tile::create(name, type, i);
	}

	// TODO: Now one room is loaded as an entire level, in the future the level generator needs to create a level using rooms
	uint room_test = IO::Reader::getId("room_test");

	// Get the layout sizes
	levelSize = IO::Reader::getImageSize(room_test);

	// Read the layout data
	layout = new byte[(int)(levelSize.x * levelSize.y)];
	IO::Reader::read(room_test, layout);

	// TODO: Make player selection
	// Create the player
	player = new Mage;

	// Initialize the player
	player->init();
    }

    void tick() {

	// Run camera logic
	Camera::tick();

	// Run player logic
	player->tick();
    }

    void render() {

	// Render all tiles
	for (int y = 0; y < levelSize.y; y++) {

	    for (int x = 0; x < levelSize.x; x++) {

		// Create location vector
		vec4 position = vec4 (x, levelSize.y-y, 0, 1);

		// Render each tile
		Tile::render(position, layout[(int)(x + y * levelSize.y)]);
	    }
	}

	// Render the player
	player->render();
    }

    Player *getPlayer() {

	// Return a pointer to the player
	return player;
    }

    void end() {

	// Free memory
	delete[] layout;
	delete player;

	// Deinitialize tiles
	Tile::end();
    }
}
