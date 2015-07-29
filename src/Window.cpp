#include "Standard.h"

GLFWwindow* window;

bool Window::create() {

    Log::print("Initializing glfw");
    if(!glfwInit()) {
	return false;
    }

    Log::print("Creating glfw window");
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(WIDTH*SCALE, HEIGHT*SCALE, NAME, NULL, NULL);
    if (!window) {
	terminate();
	return false;
    }

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowPos(window, (mode->width-WIDTH)/2, (mode->height-HEIGHT)/2);

    Log::print("Setting keyCallback");
    glfwSetKeyCallback(window, keyCallback);

    Log::print("Setting context to current");
    glfwMakeContextCurrent(window);
    glewInit();

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

    return true;
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

