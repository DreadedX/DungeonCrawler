#ifndef INPUT_H
#define INPUT_H

namespace Input {

    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    void mousePosCallback(GLFWwindow *window, double xPos, double yPos);

    bool isPressed(int key);
    void setState(int key, bool state);
    glm::vec4 getMousePos();
};

namespace Key {

    const int UP = GLFW_KEY_W;
    const int LEFT = GLFW_KEY_A;
    const int DOWN = GLFW_KEY_S;
    const int RIGHT = GLFW_KEY_D;
    const int ATTACK = GLFW_KEY_SPACE;
    // const int DASH = GLFW_KEY_W;
    const int PAUSE = GLFW_KEY_ESCAPE;
    const int CONTINUE = GLFW_KEY_SPACE;

    const int DEBUG_ZOOM_IN = GLFW_KEY_Q;
    const int DEBUG_ZOOM_OUT = GLFW_KEY_E;
    const int DEBUG_NEW_LEVEL = GLFW_KEY_R;

#if DEBUG_MODE
    const int DEBUG_NOCLIP = GLFW_KEY_SPACE;
    const int DEBUG_BOOST = GLFW_KEY_LEFT_SHIFT;

    const int DEBUG_INFO = GLFW_KEY_F3;
    const int DEBUG_CONSOLE = GLFW_KEY_F4;
    const int DEBUG_ITEM = GLFW_KEY_I;
#endif
};

#endif
