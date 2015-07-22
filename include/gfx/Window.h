#ifndef WINDOW_H
#define WINDOW_H

#include "GLFW/glfw3.h"

bool createWindow();
bool shouldCloseWindow();
void destroyWindow();
void pollWindow();
void swapWindow();

#endif
