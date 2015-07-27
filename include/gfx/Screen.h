#ifndef SCREEN_H
#define SCREEN_H

class Screen {

    public:
	static void clear();
	static void drawTile(int x, int y, GLuint tex);
};

#endif
