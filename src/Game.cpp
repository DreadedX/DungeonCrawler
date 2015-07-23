#include "Game.h"
#include "Defs.h"
#include "Input.h"
#include "gfx/Window.h"
#include "gfx/Screen.h"
#include "entities/Entity.h"
#include "util/Tick.h"
#include "util/Log.h"

#include <fstream>

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

    // byte buffer[100];
    // std::ifstream myFile ("out.gaff", std::ios::in | std::ios::binary);
    // myFile.read(reinterpret_cast<char*>(buffer), 100);
    // myFile.close();
    // for(int i = 0; i < 4; i++) {
	// std::cout << +buffer[i] << std::endl;
    // }
    // return;

    Log::print("Debug", DEBUG);
    Log::print("Info", INFO);
    Log::print("Warning", WARNING);
    Log::print("Error", ERROR);

    if(!createWindow()) {
	Log::print("Failed to create window!", ERROR);
	return;
    }

    Log::print("Starting game loop");
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
