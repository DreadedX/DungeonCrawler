#include "Standard.h"

namespace Game {

    double lastTick;

    int ticks  = 0;
    int frames = 0;

    int actualTPS = 0;
    int actualFPS = 0;
    double minFT   = 10;
    double maxFT   = 0;
    double avgFT   = 0;

    bool paused = false;
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
    inline void control();
    inline void tick();
    inline void render();

    void renderDebug();

    void main() {

	// Initalize the game
	init();

	// Set lastTick to current time
	lastTick = glfwGetTime();

	// Run the game loop
	gameLoop();

	// Deinitalize the game
	end();
    }

    void stop(int exitCode) {
	end();

	exit(exitCode);
    }

    void init() {

	// Load the gaff files
	std::string fileName[] = {"test.gaff"};
	IO::Reader::load(fileName, sizeof(fileName)/sizeof(std::string));

	// Create GLFW window with OpenGL context
	Window::create();
	
	// Print debug information about the system
	Log::print(String::format("Vendor: %s", glGetString(GL_VENDOR)), DEBUG);
	Log::print(String::format("GPU: %s", glGetString(GL_RENDERER)), DEBUG);
	Log::print(String::format("OpenGL: %s", glGetString(GL_VERSION)), DEBUG);

	Randomizer::init();

	// Initialize the renderer
	Render::init();

	// Initalize the level controller
	Level::init();

	// Initialize the camera controller
	Camera::init();

	// Initalize the font system
	// Font::init();
    }

    void end() {

#if DEBUG_MODE
	// Shutdown the debug ui
	ImGui_ImplGlfwGL3_Shutdown();
#endif

	// Close the game window
	Window::destroy();

	// Deinitialize level
	Level::end();

#if DEBUG_MODE
	// stb_leakcheck_dumpmem();
#endif

	// Free allocated memory
	// Function does not yet exist
    }

    void gameLoop() {

	// Run the game as long as the window does not have to be closed
	while (!Window::shouldClose()) {
	    
	    // Run the control function every second
	    if (glfwGetTime() - lastTick > 1) {

		control();
	    }

	    // Run a tick every 1/TPS seconds
	    for (double delta = glfwGetTime() - lastTick; delta > FT*ticks; delta -= FT) {

		tick();
	    }

	    // Start frametime timer
	    double timerStart = glfwGetTime();

	    // Render frame
	    render();

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
	}
    }

    void control() {

	// Reset variables used to check game performance
	actualTPS = ticks;
	actualFPS = frames;
	minFT     = 10;
	avgFT     = 1.0f/frames;
	maxFT     = 0;
	ticks     = 0;
	frames    = 0;

#if DEBUG_MODE && __linux__
	// Check the memory usage of the game
	look_up_our_self(&proc);
	vsize = proc.vsize / 1000000;
#endif

	// Set lastTick to current time
	lastTick = glfwGetTime();
    }

    void tick() {

	// If the game is not paused execute the game logic
	if (!paused) {

	    Level::tick();
	}

	// If the pause key is pressed toggle the paused state
	if (Input::isPressed(Key::PAUSE)) {

	    Input::setState(Key::PAUSE, false);
	    paused = !paused;
	}

#if DEBUG_MODE
	// If the debug key is pressed toggle the debug window
	if (Input::isPressed(Key::DEBUG)) {

	    Input::setState(Key::DEBUG, false);
	    showDebug = !showDebug;
	}

	// If the console key is pressed toggle the console window
	if (Input::isPressed(Key::CONSOLE)) {

	    Input::setState(Key::CONSOLE, false);
	    showConsole = !showConsole;
	    switchInput = true;
	}
#endif

	// Increment the tick counter
	ticks++;
    }

    void render() {
	// Clear the current buffer
	Render::clear();

	// // TODO: Clean this code up
	// Draw the floor
	// static GLuint floor = Texture::load("background/mountain_floor");
	// Render::floor(vec4(0,0,0,1), floor);
	// Render::floor(vec4(-170,0,0,1), floor);
	// Render::floor(vec4(170,0,0,1), floor);

	// Draw background layer 0, furthest away
	// static GLuint background_0 = Texture::load("background/mountain_0");
	// Render::background(vec4(0,0,-60, 1), background_0);
	// Render::background(vec4(-170,0,-60, 1), background_0);
	// Render::background(vec4(170,0,-60, 1), background_0);

	// Draw backfround layer 1
	// static GLuint background_1 = Texture::load("background/mountain_1");
	// Render::background(vec4(0,0,-50, 1), background_1);
	// Render::background(vec4(-170,0,-50, 1), background_1);
	// Render::background(vec4(170,0,-50, 1), background_1);

	// Draw background layer 2
	// static GLuint background_2 = Texture::load("background/mountain_2");
	// Render::background(vec4(0,0,-40, 1), background_2);
	// Render::background(vec4(-170,0,-40, 1), background_2);
	// Render::background(vec4(170,0,-40, 1), background_2);

	// Draw background layer 3
	// static GLuint background_3 = Texture::load("background/mountain_3");
	// Render::background(vec4(0,0,-30, 1), background_3);
	// Render::background(vec4(-170,0,-30, 1), background_3);
	// Render::background(vec4(170,0,-30, 1), background_3);

	// Draw background layer 4
	// static GLuint background_4 = Texture::load("background/mountain_4");
	// Render::background(vec4(0,0,-20, 1), background_4);
	// Render::background(vec4(-170,0,-20, 1), background_4);
	// Render::background(vec4(170,0,-20, 1), background_4);

	// Draw background layer 5, closest
	// static GLuint background_5 = Texture::load("background/mountain_5");
	// Render::background(vec4(0,0,-10, 1), background_5);
	// Render::background(vec4(-170,0,-10, 1), background_5);
	// Render::background(vec4(170,0,-10, 1), background_5);

	// Render the level
	Level::render();

#if DEBUG_MODE
	// Render the debug interface
	renderDebug();
#endif

	// Swap framebuffers
	Window::swap();

	// Increment frame counter
	frames++;
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
	ImGui_ImplGlfwGL3_NewFrame();

	// Check if the debug window needs to be displayed
	if (showDebug) {

	    // Begin a new ImGui window
	    ImGui::Begin("Debug infomation", &showDebug, ImVec2(0,0), 0.3f, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoInputs);
	    
	    // Display fps and tps information
	    ImGui::Text("FPS: %i, TPS: %i", actualFPS, actualTPS);

	    // Display frametime information
	    ImGui::Text("minFT: %.4f, avgFT: %.4f, maxFT: %.4f", minFT, avgFT, maxFT);

	    // Draw a seperator
	    ImGui::Separator();
	    //
	    // Draw the frametime graph
	    ImGui::PlotLines("avgFT", values.Data, values.Size, values_offset, "avgFT", 0.0f, FT*2, ImVec2(0, 100));

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
}
