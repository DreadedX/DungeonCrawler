#include "Game.h"

void gameLoop();
void info();
void tick();
void render();

int lastTick;
int lastInfo;

int ticks = 0;
int frames = 0;

// TESTING
Entity entity;

void Game::init() {
    Reader::load("gaff");
    
    // Log::print("Debug", DEBUG);
    // Log::print("Info", INFO);
    // Log::print("Warning", WARNING);
    // Log::print("Error", ERROR);

    if(!createWindow()) {
	Log::print("Failed to create window!", ERROR);
	return;
    }

    Log::print("Starting game loop");
    entity.init();
    gameLoop();
}

void gameLoop() {
    lastTick = getMilliCount();
    while (!shouldCloseWindow()) {
	info();

	tick();
	render();

	pollWindow();
    }
    destroyWindow();
}

void info() {

    if (getMilliSpan(lastInfo) > 1000) {
	lastInfo = getMilliCount();

	std::cout << "Ticks: " << ticks << ", Frames: " << frames << std::endl;

	ticks = 0;
	frames = 0;
    }
}

void tick() {

// TODO: This appears to not work correctly yet
    // if (getMilliSpan(lastTick) > 1000/TPS) {
	lastTick = getMilliCount();

	entity.tick();

	ticks++;
    // }
}

void render() {
    Screen::clear();

    entity.render();

    swapWindow();

    frames++;
}
