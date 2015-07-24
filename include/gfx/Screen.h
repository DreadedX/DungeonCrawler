#ifndef SCREEN_H
#define SCREEN_H

#include "Standard.h"

class Screen {

    public:
	static void clear();
	static void drawRectangle(int x1, int y1, int x2, int y2, GLuint tex);
};

#endif
