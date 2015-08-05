#include "Standard.h"

namespace Input {

    bool keys[1000] = {0};

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
#if DEBUG_MODE
	ImGuiIO& io = ImGui::GetIO();
	if(io.WantCaptureKeyboard) {

	    for (uint i = 0; i < sizeof(keys); i++) {
		if(isPressed(i)) {
		    keys[i] = false;
		}

	    }

	    if (action == GLFW_PRESS)
		io.KeysDown[key] = true;
	    if (action == GLFW_RELEASE)
		io.KeysDown[key] = false;

	    (void)mods; // Modifiers are not reliable across systems
	    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	} else {
#endif
	    if (action == GLFW_PRESS) {
		keys[key] = true;
	    }
	    if (action == GLFW_RELEASE) {
		keys[key] = false;
	    }
	    if (window || scancode || mods) {

	    }
#if DEBUG_MODE
	}
#endif
    }

    bool isPressed(int key) {
	return keys[key];
    }

    void setState(int key, bool state) {
	keys[key] = state;
    }
}
