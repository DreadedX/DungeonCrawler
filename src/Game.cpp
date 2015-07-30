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
    std::string fileName[] {"base.gaff", "level.gaff"};
    IO::Reader::load(fileName);

    Window::create();

    // Screen::init();

    Level::init();
    Camera::init();

    gameLoop();

    Level::end();
    IO::Reader::freeReader();
}

void gameLoop() {
    lastTick = getMilliCount();
    while (!Window::shouldClose()) {
	info();

	tick();
	render();

	Window::poll();
    }
    Window::destroy();
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
    if (getMilliSpan(lastTick) > 1000/TPS) {
	lastTick = getMilliCount();

	Level::tick();
	Camera::tick();

	ticks++;
    }
}

void render() {
    Render::clear();

    Level::render();
    Camera::tick();

    // Screen::drawVao();

    Window::swap();

    frames++;
}
