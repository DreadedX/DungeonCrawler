#ifndef DEFINITION_H
#define DEFINITION_H

#include "Standard.h"

typedef unsigned char byte;
typedef unsigned int uint;

union byteInt {
    byte b[4] = {0x00};
    uint i;
};
union byteShort {
    byte b[2] = {0x00};
    unsigned short s;
};

struct size {
    int width;
    int height;
};

struct i2 {
    float x;
    float y;
};
struct f3 {
    float x;
    float y;
    float z;
};

class Gaff {

    public:
	struct fileInfo {
	    std::string origin = "";
	    byte nameSize = 0x00;
	    std::string name = "";
	    byte type = 0x00;
	    // Example:
	    // Image = 0001 0000 | Text = 0010 0000 | Audio = 0011 0000
	    // Tile: 0010 | Solid: 0001
	    // => ImageSolidTile = 0001 0011 | 0xA3
	    byteInt extra;
	    byteInt offset;
	    byteInt size;
	};

	static constexpr byte MAGIC[5] = {"GAFF"};
	static const byte VERSION = 0x01;
};

#endif
