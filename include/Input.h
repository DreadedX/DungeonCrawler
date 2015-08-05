#ifndef INPUT_H
#define INPUT_H


namespace Input {

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    bool isPressed(int key);
    void setState(int key, bool state);
};

namespace Key {

    const int UP = GLFW_KEY_W;
    const int LEFT = GLFW_KEY_A;
    const int DOWN = GLFW_KEY_S;
    const int RIGHT = GLFW_KEY_D;
    const int JUMP = GLFW_KEY_SPACE;
    // const int DASH = GLFW_KEY_W;
    const int PAUSE = GLFW_KEY_ESCAPE;

#if DEBUG_MODE
    const int DEBUG = GLFW_KEY_F3;
    const int CONSOLE = GLFW_KEY_F4;
#endif
};

#endif
