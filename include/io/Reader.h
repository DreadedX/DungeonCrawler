#ifndef READER_H
#define READER_H

#include "Standard.h"

class Reader {
    public:
	static void load(std::string);
	static uint getId(std::string);
	static size getImageSize(int id);
	static void read(int id, byte*);
};

#endif
