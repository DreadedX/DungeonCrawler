#ifndef DEFINITION_H
#define DEFINITION_H

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

// 0000 0001
const byte TYPE_TILE = 0x01;
// 0000 0010
const byte TYPE_SOLID = 0x02;
// 0000 0100
const byte TYPE_ENTITY = 0x04;
// 1000 0000
// byte HAS_ALPHA = 0x80;

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
