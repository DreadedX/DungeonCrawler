#if !LEGACY
#include "Standard.h"

namespace Window {

    GLFWwindow* window;

    void create() {

	if(!glfwInit()) {
	    Log::print("Failed to initialize glfw!", ERROR);
	    exit(-1);
	    return;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(WIDTH*SCALE, HEIGHT*SCALE, NAME, NULL, NULL);
	if (!window) {
	    std::cerr << "Failed to create window!" << std::endl;
	    terminate();
	    exit(-1);
	    return;
	}

	glfwMakeContextCurrent(window);
	glewExperimental=true;
	if(glewInit() != GLEW_OK) {
	    Log::print("Failed to initialize glew!", ERROR);
	    exit(-1);
	    return;
	}

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(window, (mode->width-WIDTH*SCALE)/2, (mode->height-HEIGHT*SCALE)/2);

	glfwSetKeyCallback(window, Input::keyCallback);

	glfwSwapInterval(0);
    }

    bool shouldClose() {

	return glfwWindowShouldClose(window);
    }

    void terminate() {

	glfwTerminate();
    }

    void destroy() {

	glfwDestroyWindow(window);
    }

    void swap() {

	glfwSwapBuffers(window);
    }

    void poll() {

	glfwPollEvents();
    }
}
#endif
