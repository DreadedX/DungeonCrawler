#ifndef SCREEN_H
#define SCREEN_H

#include "util/Math.h"
#include "GLFW/glfw3.h"

class Screen {

    public:
	static void clear();
	static void drawRectangle(int x1, int y1, int x2, int y2, vec3f colour);
};

#endif
