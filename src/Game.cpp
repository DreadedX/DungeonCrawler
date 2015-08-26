#include "Standard.h"

double lastTick;
double lastFrame;

int ticks  = 0;
int frames = 0;

int actualTPS = 0;
int actualFPS = 0;
double minFT = 10;
double maxFT = 0;
double avgFT = 0;

bool paused      = false;
#if DEBUG_MODE
bool showDebug   = false;
bool showConsole = false;
bool switchInput = false;
#endif
#if DEBUG_MODE && __linux__
struct proc_t proc;
float vsize = proc.vsize / 1000000;
#endif

inline void init();
inline void gameLoop();
inline void end();

inline void audio();
inline void tick();
inline void render();

void renderDebug();

void Game::main() {

    // Initalize the game
    init();

    // Set lastTick to current time
    lastTick = glfwGetTime();
    lastFrame = glfwGetTime();

    // Run the game loop
    gameLoop();

    // Deinitalize the game
    end();
}

void Game::stop(int exitCode) {
    end();

    exit(exitCode);
}

void init() {

    // Load the gaff files
    std::string fileName[] = {"out.gaff"};
    Reader::load(fileName, sizeof(fileName)/sizeof(std::string));

    // Create GLFW window with OpenGL context
    Window::create();

    // Print debug information about the system
    Log::print(String::format("Vendor: %s", glGetString(GL_VENDOR)), DEBUG);
    Log::print(String::format("GPU: %s", glGetString(GL_RENDERER)), DEBUG);
    Log::print(String::format("OpenGL: %s", glGetString(GL_VERSION)), DEBUG);

    // Initialize the renderer
    Render::init();

    // Initalize the level controller
    Level::init();

    // Initialize the camera controller
    Camera::init();

    // Initalize the audio system
    Audio::init();

    // Initialize text system
    Text::init("font/aesymatt");
}

void end() {

    #if DEBUG_MODE
    // Shutdown the debug ui
    #if not LEGACY
    ImGui_ImplGlfwGL3_Shutdown();
    #else
    ImGui_ImplGlfw_Shutdown();
    #endif
    #endif

    // Close the game window
    Window::destroy();

    // Deinitialize level
    Level::end();

    // Deinitialize the audio system
    Audio::end();

    #if DEBUG_MODE
    // stb_leakcheck_dumpmem();
    #endif

    // Free allocated memory
    // Function does not yet exist
}

void gameLoop() {

    std::thread tAudio(audio);

    while(!Window::shouldClose()) {

	tick();
	render();
    }

    tAudio.join();
}

void audio() {

    while(!Window::shouldClose()) {

	// Update audio manager
	Audio::tick();
    }
}

void tick() {

    // Run a tick every 1/TPS seconds
    for (double delta = glfwGetTime() - lastTick; delta > FT*ticks; delta -= FT) {

	// If the game is not paused execute the game logic
	if (!paused) {

	    Level::tick();
	}

	Gui::tick();

	// If the pause key is pressed toggle the paused state
	if (Input::isPressed(Key::PAUSE)) {

	    Input::setState(Key::PAUSE, false);
	    paused = !paused;

	    // NOTE: This is for testing audio
	    // Audio::test();
	}

	// Increment the tick counter
	ticks++;

	#if DEBUG_MODE
	// If the debug key is pressed toggle the debug window
	if (Input::isPressed(Key::DEBUG_INFO)) {

	    Input::setState(Key::DEBUG_INFO, false);
	    showDebug = !showDebug;
	}

	// If the console key is pressed toggle the console window
	if (Input::isPressed(Key::DEBUG_CONSOLE)) {

	    Input::setState(Key::DEBUG_CONSOLE, false);
	    showConsole = !showConsole;
	    switchInput = true;
	}

	if (Input::isPressed(Key::DEBUG_ITEM)) {

	    Input::setState(Key::DEBUG_ITEM, false);
	    Level::getPlayer()->getComponent<InventoryComponent>().addItem();
	}
	#endif
    }

    if (glfwGetTime() - lastTick > 1) {

	// Reset variables used to check game performance
	actualTPS = ticks;
	Log::print(String::format("%i", actualFPS), INFO);
	ticks     = 0;

	#if DEBUG_MODE && __linux__
	// Check the memory usage of the game
	look_up_our_self(&proc);
	vsize = proc.vsize / 1000000;
	#endif

	// Set lastTick to current time
	lastTick = glfwGetTime();
    }
}

void render() {

    // Start frametime timer
    double timerStart = glfwGetTime();

    // Clear the current buffer
    Render::clear();

    // Render the level
    Level::render();

    Gui::render();
    
    // static int i = 0;
    // if (i == 10) {
	// Game::stop(0);
    // }
    // i++;

    #if DEBUG_MODE
    // Render the debug interface
    renderDebug();
    #endif

    // Swap framebuffers
    Window::swap();

    // Increment frame counter
    frames++;

    // Calculate frametime
    double time = glfwGetTime() - timerStart;

    // Set min and max frametimes
    if (time > maxFT) {
	maxFT = time;
    }
    if (time < minFT) {
	minFT = time;
    }

    // Poll the game window
    Window::poll();

    if (glfwGetTime() - lastFrame > 1) {

	// Reset variables used to check game performance
	actualFPS = frames;
	minFT     = 10;
	avgFT     = 1.0f/frames;
	maxFT     = 0;
	frames    = 0;

	// Set lastTick to current time
	lastFrame = glfwGetTime();
    }
}

#if DEBUG_MODE
void renderDebug() {

    // create variables used to display frametime graph
    static ImVector<float> values;
    static int values_offset = 0;

    // If values is empty fill it with zeroes
    if (values.empty()) {

	values.resize(900);
	memset(values.Data, 0, values.Size*sizeof(float));
    }

    // Set values for the frametime graph
    values[values_offset] = avgFT;
    values_offset = (values_offset+1)%values.Size;

    // Start a new ImGui frame, using the correct implementation
    #if not LEGACY
    ImGui_ImplGlfwGL3_NewFrame();
    #else
    ImGui_ImplGlfw_NewFrame();
    #endif

    // Check if the debug window needs to be displayed
    if (showDebug) {

	// Begin a new ImGui window
	ImGui::Begin("Debug infomation", &showDebug, ImVec2(0,0), 0.3f, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoInputs);

	// Display fps and tps information
	ImGui::Text("FPS: %i, TPS: %i", actualFPS, actualTPS);

	// Display frametime information
	ImGui::Text("minFT: %.3fms, avgFT: %.3fms, maxFT: %.3fms", minFT*1000, avgFT*1000, maxFT*1000);

	// Draw a seperator
	ImGui::Separator();
	//
	// Draw the frametime graph
	ImGui::PlotLines("avgFT", values.Data, values.Size, values_offset, "avgFT", 0.0f, FT*2, ImVec2(0, 100));

	#if LEGACY
	// Draw a seperator
	ImGui::Separator();

	ImGui::Text("Legacy back-end");
	#endif

	// Draw a seperator
	ImGui::Separator();

	#if __linux__
	// Display memory usage
	ImGui::Text("Memory usage: %.3f MB", vsize);
	#endif

	// End ImGui window
	ImGui::End();
    }

    // Check if the console window needs to be displayed
    if (showConsole) {

	// Show console
	Console::show(&showConsole);
    }

    // Render ImGui windows
    ImGui::Render();
}
#endif
