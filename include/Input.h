#ifndef INPUT_H
#define INPUT_H

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

namespace Input {

    bool isPressed(int key);
    void setState(int key, bool state);
};

#endif
