#include "Standard.h"

namespace Window {

    GLFWwindow* window;
    
    inline void glfw();
    inline void alut();

    void create() {

	// Initalize glfw
	glfw();

	// Intalize alut
	// alut();
    }

    void glfw() {

	// Check if glfw initialized
	if(!glfwInit()) {

	    // Print error
	    Log::print("Failed to initialize glfw!", ERROR);

	    // Stop the game
	    Game::stop(ERROR_GLFW);
	}

	// Make the window not resizable
	// glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	// Set antialiasing to 4x
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Set OpenGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// This is for mac compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Use the OpenGL core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the window
	window = glfwCreateWindow(WIDTH*SCALE, HEIGHT*SCALE, NAME, NULL, NULL);

	// Check if the window was created
	if (!window) {
	    
	    // Print error
	    Log::print("Failed to create window", ERROR);

	    // Stop game
	    Game::stop(ERROR_WINDOW);
	}

	// Set the OpenGL context to the window
	glfwMakeContextCurrent(window);

	// Enable glew experimental
	glewExperimental=true;

	// Check if glew initalized
	if(glewInit() != GLEW_OK) {

	    // Print error
	    Log::print("Failed to initialize glew!", ERROR);

	    // Stop game
	    Game::stop(ERROR_GLEW);
	}

	// Get primary monitor
	GLFWmonitor *monitor = glfwGetPrimaryMonitor();

	// Get the video mode of the primary monitor
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	// Set the window position to the center of the primary monitor
	glfwSetWindowPos(window, (mode->width-WIDTH*SCALE)/2, (mode->height-HEIGHT*SCALE)/2);

	// Setup the key callback
	glfwSetKeyCallback(window, Input::keyCallback);

#if DEBUG_MODE
	// Initalize ImGui
	ImGui_ImplGlfwGL3_Init(Window::window, false);

	// Setup ImGui callbacks
        glfwSetMouseButtonCallback(window, ImGui_ImplGlfwGL3_MouseButtonCallback);
        glfwSetScrollCallback(window, ImGui_ImplGlfwGL3_ScrollCallback);
        glfwSetCharCallback(window, ImGui_ImplGlfwGL3_CharCallback);
#endif

	// Set swap interval
	glfwSwapInterval(SWAP);

    }

    void alut() {

	// Initialize alut
	alutInit(0, NULL);

	// Clear the alut error buffer
	alGetError();
    }

    bool shouldClose() {

	// Return whether or not the window should close
	return glfwWindowShouldClose(window);
    }

    void terminate() {

	// Terminate the glfw window
	glfwTerminate();
    }

    void destroy() {

	// Close the glfw window
	glfwDestroyWindow(window);
    }

    void swap() {

	// Swap framebuffers
	glfwSwapBuffers(window);
    }

    void poll() {

	// Poll the window for events
	glfwPollEvents();
    }
}
