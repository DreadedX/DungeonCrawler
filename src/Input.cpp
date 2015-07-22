#include "Input.h"
#include "util/Log.h"

#include "GLFW/glfw3.h"

bool keys[1000] = {0};

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
	keys[key] = true;
    }

    if (action == GLFW_RELEASE) {
	keys[key] = false;
    }

    if (window || scancode || mods) {

    }
}

bool Input::isPressed(int key) {
    return keys[key];
}

void Input::setState(int key, bool state) {
    keys[key] = state;
}
