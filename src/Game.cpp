#include "Standard.h"

void gameLoop();
void info();
void tick();
void render();

int lastTick;
int lastInfo;

int ticks = 0;
int frames = 0;

void Game::init() {
    
    if(!createWindow()) {
	Log::print("Failed to create window!", ERROR);
	return;
    }

    Reader::load("gaff");

    Level::init();

    gameLoop();

    Reader::freeReader();
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

	Level::tick();

	ticks++;
    // }
}

void render() {
    Screen::clear();

    Level::render();

    swapWindow();

    frames++;
}
