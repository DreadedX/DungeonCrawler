#ifndef WINDOW_H
#define WINDOW_H

const int WIDTH = 608;
const int HEIGHT = (WIDTH / 4 * 3);
const char NAME[] = "Platformer";

class Window {

    public:
	static bool create();
	static bool shouldClose();
	static void terminate();
	static void destroy();
	static void swap();
	static void poll();
};


#endif
