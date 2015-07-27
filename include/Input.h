#ifndef INPUT_H
#define INPUT_H

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Input {

    public:
	static bool isPressed(int key);
	static void setState(int key, bool state);
};

#endif
