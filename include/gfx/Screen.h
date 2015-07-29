#ifndef SCREEN_H
#define SCREEN_H

class Screen {

    public:
	static void init();
	static void drawTest();
	static void clear();
	static void drawTile(int x, int y, GLuint tex);
	static void drawOutline(int x1, int y1, int x2, int y2);
};

#endif
