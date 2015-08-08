#include "Standard.h"

namespace Level {

    Entity player;

    byte **layout;
    byte **layout0;

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

	// TODO: Create an actual level format
	// Get the layout ids
	uint layoutID = IO::Reader::getId("level");
	uint layout0ID = IO::Reader::getId("level0");

	// Get the layout sizes
	vec2 layoutSize = IO::Reader::getImageSize(layoutID);
	vec2 layout0Size = IO::Reader::getImageSize(layout0ID);

	levelSize = layoutSize;

	// Check if sizes match
	if (layoutSize != layout0Size) {

	    // Print error message
	    Log::print("Layout sizes do not match!", ERROR);

	    // End game
	    Game::stop(ERROR_LEVEL);
	}

	// Read the layout data
	byte layout1d[(int)(levelSize.x * levelSize.y)];
	IO::Reader::read(layoutID, layout1d);

	// Create 2d layout array (y-component)
	layout = new byte*[(int)levelSize.y];

	// Read the layout0 data
	byte layout01d[(int)(levelSize.x * levelSize.y)];
	IO::Reader::read(layout0ID, layout01d);

	// Create 2d layout0 array (y-component)
	layout0 = new byte*[(int)levelSize.y];

	// Convert the layout data from a 1d array to a 2d array
	for (int y = 0; y < levelSize.y; y++) {

	    // Create 2d layout0 array (x-component)
	    layout[y] = new byte[(int)levelSize.x];
	    layout0[y] = new byte[(int)levelSize.x];

	    for (int x = 0; x < levelSize.x; x++) {

		layout[y][x] = layout1d[(int)((y * levelSize.x) + x)];
		layout0[y][x] = layout01d[(int)((y * levelSize.x) + x)];
	    }
	}

	// Initialize the player
	player.init();
    }

    void tick() {

	// Run camera logic
	Camera::tick();

	// Run player logic
	player.tick();
    }

    void render() {

	// Render all tiles
	for (int y = 0; y < levelSize.y; y++) {

	    for (int x = 0; x < levelSize.x; x++) {

		// Create location vector
		vec4 position = vec4 (x, levelSize.y-y, 0, 1);

		// Render layout0 tiles
		if (!Input::isPressed(GLFW_KEY_2)) {

		    Tile::render(position, layout0[y][x]);
		}

		// Render layout tiles
		if (!Input::isPressed(GLFW_KEY_1)) {

		    Tile::render(position, layout[y][x]);
		}
	    }
	}

	// Render the player
	player.render();
    }

    Entity* getPlayer() {

	// Return a pointer to the player
	return &player;
    }

    void end() {

	// Free memory
	for (int i = 0; i < levelSize.y; i++) {

	    delete[] layout[i];
	    delete[] layout0[i];
	}
	delete[] layout;
	delete[] layout0;

	// Deinitialize tiles
	Tile::end();
    }
}
