#include "Game.h"
#include "Input.h"
#include "gfx/Window.h"
#include "gfx/Screen.h"
#include "util/Math.h"
#include "util/Tick.h"
#include "util/Log.h"

void gameLoop();
void info();
void tick();
void render();

int lastTick;
int lastInfo;

int ticks = 0;

void Game::init() {

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

	std::cout << "Ticks: " << ticks << std::endl;

	ticks = 0;
    }
}

void tick() {

    int delta = getMilliSpan(lastTick);
// TODO: This appears to not work correctly yet
    while (delta > 1000/TPS) {
	lastTick = getMilliCount();
	delta -= 1000/TPS;

	ticks++;

	if(Input::isPressed(32)) {
	    Log::print("Spacebar pressed");
	    Input::setState(32, false);
	}
    }
}

void render() {
    Screen::clear();

    vec3f colour {1.0f, 0.5f, 0.2f};
    // colour.x = 1.0f;
    // colour.y = 0.5f;
    // colour.z = 0.2f;
    Screen::drawRectangle(100, 100, 200, 200, colour);

    swapWindow();
}
