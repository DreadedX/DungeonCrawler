#include "Standard.h"

Manager manager;
auto& player = manager.addEntity();

uint *layout   = nullptr;
// vec2 levelSize = vec2(256, 256);
glm::vec2 size = glm::vec2(25, 25);
// vec2 levelSize = vec2(25, 25);
glm::vec2 levelSize = size * 5;

void newLevel() {

    double timerStart = glfwGetTime();
    layout = BlueprintGenerator::generate(LevelGenerator::generate(size), size, levelSize);
    for (int i = 0; i < levelSize.x * levelSize.y; i++) {

	layout[i] = BlueprintGenerator::getTile(layout[i]);
    }
    double time = glfwGetTime() - timerStart;

    Log::print(String::format("Generation time: %.3fms", time*1000), DEBUG);
}

void Level::init() {

    // Get a count of all tiles
    int tileCount = Reader::countWithType(TYPE_TILE);
    //
    // Make a list of all files classified as tiles
    uint idList[tileCount];
    Reader::getWithType(TYPE_TILE, idList);

    // Initialize the tiles
    Tile::init(tileCount);

    Log::print(String::format("Tile count: %i", tileCount), DEBUG);

    // Load each tile
    for (int i = 0; i < tileCount; i++) {

	// Get the name associated with the id
	std::string name = Reader::getName(idList[i]);

	// Get tile type
	byte type = Reader::getType(idList[i]);

	// Create a tile
	Tile::create(name, type, i);
    }

    // TODO: Now one room is loaded as an entire level, in the future the level generator needs to create a level using rooms
    // uint room_test = IO::Reader::getId("room_test");

    // Get the layout sizes
    // levelSize = IO::Reader::getImageSize(room_test);

    // Read the layout data
    // layout = new byte[(int)(levelSize.x * levelSize.y)];
    // IO::Reader::read(room_test, layout);

    newLevel();

    // TODO: Make player selection
    player.addComponent<PositionComponent>(glm::vec4(size.x/2, size.y/2, 0, 1));
    player.addComponent<HitboxComponent>(glm::vec4(0, 0, 0, 0), glm::vec4(17.0f/16.0f, 10.0f/16.0f, 1, 0));
    player.addComponent<CollisionComponent>();
    player.addComponent<PhysicsComponent>();
    player.addComponent<TextureComponent>("entity/player/class/mage", glm::vec4(17.0f/16.0f, 20.0f/16.0f, 1, 0));
    player.addComponent<PlayerComponent>();
    player.addComponent<InventoryComponent>();

    // Initialize all entities
}

Entity &Level::spawn() {

    return manager.addEntity();
}

void Level::tick() {

    // Run camera logic
    Camera::tick();

    // Run all entity logic
    // for (Entity *entity : entities) {
    //
    //     entity->tick();
    // }

    if (Input::isPressed(Key::DEBUG_NEW_LEVEL)) {

	Input::setState(Key::DEBUG_NEW_LEVEL, false);

	delete[] layout;
	newLevel();
    }

    manager.refresh();
    manager.tick();
}

void Level::render() {

    Render::startTile();

    for (int y = (int)levelSize.y-1; y >= 0; y--) {

	for (int x = 0; x < (int)levelSize.x; x++) {
	    // Create location vector
	    glm::vec4 position = glm::vec4 (x, y, 0, 1);

	    // Render each tile
	    Tile::render(position, layout[(int)(x + y * levelSize.y)]);
	}
    }

    Render::endTile();

    // Render the player
    Render::startEntity();

    manager.render();

    Render::endEntity();
}

Entity *Level::getPlayer() {

    // Return a pointer to the player
    return &player;
}

bool Level::isSolid(glm::vec4 mPosition) {

    Tile::TileData tile = Tile::getTileData(layout[(int)(mPosition.x) + (int)(mPosition.y) * (int)(levelSize.x)]);

    return (tile.type & TYPE_SOLID) == TYPE_SOLID;
}

void Level::end() {

    // Free memory
    delete[] layout;
    layout = nullptr;

    // for (Entity *entity : entities) {
    //
    //     delete entity;
    // }
    //
    // entities.clear();
    // player = nullptr;

    // Deinitialize tiles
    Tile::end();
}
