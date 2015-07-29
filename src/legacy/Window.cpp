#if LEGACY
#include "Standard.h"

GLFWwindow* window;

void Window::create() {

    if(!glfwInit()) {
	std::cerr << "Failed to initialize glfw!" << std::endl;
	exit(-1);
	return;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    window = glfwCreateWindow(WIDTH*SCALE, HEIGHT*SCALE, NAME, NULL, NULL);
    if (!window) {
	std::cerr << "Failed to create window!" << std::endl;
	terminate();
	exit(-1);
	return;
    }

    glfwMakeContextCurrent(window);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowPos(window, (mode->width-WIDTH)/2, (mode->height-HEIGHT)/2);

    glfwSetKeyCallback(window, keyCallback);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool Window::shouldClose() {

    return glfwWindowShouldClose(window);
}

void Window::terminate() {

    glfwTerminate();
}

void Window::destroy() {

    glfwDestroyWindow(window);
}

void Window::swap() {

    glfwSwapBuffers(window);
}

void Window::poll() {

    glfwPollEvents();
}
#endif
