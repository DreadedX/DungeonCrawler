#include "Standard.h"

namespace Game {

    float lastTick;

    int ticks = 0;
    int frames = 0;

    int actualTPS = 0;
    int actualFPS = 0;
    float minFT = 10;
    float maxFT = 0;
    float avgFT = 0;

    bool paused = false;
#if DEBUG_MODE
    bool showDebug = false;
    bool showConsole = true;
#endif
#if DEBUG_MODE && __linux__
    struct proc_t proc;
    float vsize = proc.vsize / 1000000;
#endif

    Entity *player = Level::getPlayer();

    void init();
    void gameLoop();
    void end();
    void control();
    void tick();
    void render();

    void renderDebug();

    void init() {

	std::string fileName[] {"test.gaff"};
	IO::Reader::load(fileName);

	Window::create();

	Log::print(String::format("Vendor: %s", glGetString(GL_VENDOR)), DEBUG_I);
	Log::print(String::format("GPU: %s", glGetString(GL_RENDERER)), DEBUG_I);
	Log::print(String::format("OpenGL: %s", glGetString(GL_VERSION)), DEBUG_I);

	Render::init();

	Level::init();
	Camera::init();

	Font::init();

	lastTick = glfwGetTime();
    }

    void end() {
	Window::destroy();

	Level::end();
	IO::Reader::freeReader();
#if DEBUG_MODE
	ImGui_ImplGlfwGL3_Shutdown();
#endif
    }

    void main() {
	init();
	gameLoop();
	end();
    }

    void gameLoop() {

	while (!Window::shouldClose()) {
	    control();

	    tick();

	    float timerStart = glfwGetTime();
	    render();
	    float time = glfwGetTime() - timerStart;

	    if (time > maxFT) {
		maxFT = time;
	    }
	    if (time < minFT) {
		minFT = time;
	    }

	    Window::poll();
	}
    }

    void control() {

	if (glfwGetTime() - lastTick > 1) {
	    actualTPS = ticks;
	    actualFPS = frames;
	    minFT = 10;
	    avgFT = 1.0f/frames;
	    maxFT = 0;

	    ticks = 0;
	    frames = 0;

	    lastTick = glfwGetTime();
#if DEBUG_MODE && __linux__
	look_up_our_self(&proc);
	vsize = proc.vsize / 1000000;
#endif
	}
    }

    void tick() {
	
	for (float delta = glfwGetTime() - lastTick; delta > FT*ticks; delta -= FT) {
	    if(Input::isPressed(Key::PAUSE)) {
		Input::setState(Key::PAUSE, false);
		paused = !paused;
	    }

#if DEBUG_MODE
	    if(Input::isPressed(Key::DEBUG)) {
		Input::setState(Key::DEBUG, false);
		showDebug = !showDebug;
	    }
	    if(Input::isPressed(Key::CONSOLE)) {
		Input::setState(Key::CONSOLE, false);
		showConsole = !showConsole;
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

	// TODO: Make this actually work again
	if (paused) {
	    Font::render(vec4(WIDTH - 6 * 8, 0, 0, 1), vec4(1), "Paused");
	    Render::quadAbs(vec4(WIDTH/2, HEIGHT/2, 0, 1), vec2(WIDTH, HEIGHT), vec4(1, 1, 1, 0.05f));
	}

#if DEBUG_MODE
	renderDebug();
#endif

	Window::swap();

	frames++;
    }

    void renderDebug() {
	ImGui_ImplGlfwGL3_NewFrame();
	if (showDebug) {
	    ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiSetCond_FirstUseEver);
	    ImGui::Begin("Debug information");
	    ImGui::Text("FPS: %i, TPS: %i", actualFPS, actualTPS);
	    ImGui::Text("minFT: %.4f, avgFT: %.4f, maxFT: %.4f", minFT, avgFT, maxFT);
	    ImGui::Separator();
	    static ImVector<float> values; if(values.empty()) {values.resize(900); memset(values.Data, 0, values.Size*sizeof(float));}
	    static int values_offset = 0;

	    values[values_offset] = avgFT;
	    values_offset = (values_offset+1)%values.Size;

	    ImGui::PlotLines("avgFT", values.Data, values.Size, values_offset, "avgFT", 0.0f, FT*2, ImVec2(0, 100));

	    ImGui::Separator();
#if __linux__
	    ImGui::Text("Memory usage: %.3f MB", vsize);
#endif
	    ImGui::End();
	}
	if (showConsole) {
	    Console::show(&showConsole);
	}

	ImGui::Render();
    }
}
