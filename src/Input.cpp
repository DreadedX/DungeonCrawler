#include "Standard.h"

bool keys[1000] = {0};
glm::vec4 mousePos = glm::vec4(0, 0, 0, 1);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

#if DEBUG_MODE
    // This is input capture code for ImGui and only for debugging
    ImGuiIO& io = ImGui::GetIO();
    if(io.WantCaptureKeyboard) {

	for (uint i = 0; i < sizeof(keys); i++) {

	    if(isPressed(i)) {

		keys[i] = false;
	    }

	}

	if (action == GLFW_PRESS) {

	    io.KeysDown[key] = true;
	}

	if (action == GLFW_RELEASE) {

	    io.KeysDown[key] = false;
	}

	(void)mods; // Modifiers are not reliable across systems
	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    } else {
#endif
	// Check if the key is pressed
	if (action == GLFW_PRESS) {

	    // Set the key to true
	    keys[key] = true;
	}

	// Check if the key is released
	if (action == GLFW_RELEASE) {

	    // Set the key to false
	    keys[key] = false;
	}
#if DEBUG_MODE
    }
#endif
}
#pragma GCC diagnostic pop

void Input::mousePosCallback(GLFWwindow* window, double xPos, double yPos) {

    mousePos = glm::vec4(xPos, yPos, 0, 1);
}

bool Input::isPressed(int key) {

    // Return the key status
    return keys[key];
}

void Input::setState(int key, bool state) {

    // Set the key state
    keys[key] = state;
}

glm::vec4 Input::getMousePos() {

    return mousePos;
}

