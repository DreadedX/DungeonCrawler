#include "Standard.h"

namespace Game {

    void gameLoop();
    void info();
    void tick();
    void render();

    int lastTick;
    int lastInfo;

    int ticks = 0;
    int frames = 0;

    int actualTPS = 0;
    int actualFPS = 0;

    bool paused = false;
#if DEBUG_MODE
    bool showDebug = false;
#endif

    Entity *player = Level::getPlayer();

    void init() {

	std::string fileName[] {"test.gaff"};
	IO::Reader::load(fileName);

	Window::create();

	Render::init();

	Level::init();
	Camera::init();

	Font::init();

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

	    actualTPS = ticks;
	    actualFPS = frames;

	    ticks = 0;
	    frames = 0;
	}
    }

    void tick() {

	// TODO: This appears to not work correctly yet
	if (getMilliSpan(lastTick) > 1000/TPS) {
	    lastTick = getMilliCount();

	    if(Input::isPressed(Key::PAUSE)) {
		Input::setState(Key::PAUSE, false);
		paused = !paused;
	    }

#if DEBUG_MODE
	    if(Input::isPressed(Key::DEBUG)) {
		Input::setState(Key::DEBUG, false);
		showDebug = !showDebug;
	    }
#endif

	    if (!paused) {
		Level::tick();
		Camera::tick();
	    }

	    ticks++;
	}
    }

    void render() {
	Render::clear();

	Level::render();
	Camera::render();

	// TODO: Improve the format code!
#if DEBUG_MODE
	if (showDebug) {
	    Font::render(vec4(0, 1, 0, 1), vec4(1), String::format("FPS: %i, TPS: %i", actualFPS, actualTPS));
	    Font::render(vec4(0, 0, 0, 1), vec4(1), String::format("x: %i, y: %i", (int) (player->position.x), (int) (player->position.y)));
	}
#endif

	if (paused) {
	    Font::render(vec4(WIDTH - 6 * 8, 0, 0, 1), vec4(1), "Paused");
	    Render::quadAbs(vec4(WIDTH/2, HEIGHT/2, 0, 1), vec2(WIDTH, HEIGHT), vec4(1, 1, 1, 0.05f));
	}

	Window::swap();

	frames++;
    }
}
