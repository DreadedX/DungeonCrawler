#ifndef WINDOW_H
#define WINDOW_H

const int SCALE = 1;
const int WIDTH = 608 * SCALE;
const int HEIGHT = (WIDTH / 4 * 3) * SCALE;
const char NAME[] = "Platformer";

bool createWindow();
bool shouldCloseWindow();
void destroyWindow();
void pollWindow();
void swapWindow();

#endif
