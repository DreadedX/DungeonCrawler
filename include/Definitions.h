#ifndef DEFINITION_H
#define DEFINITION_H

#define MAX_SHADER_SIZE 1000
#define MAX_FILE_SIZE 4000000
#define FILE_NOT_FOUND 65536

#define BUFFER_COUNT_GL 8
#define BUFFER_COUNT_AL 8

#define INVENTORY_SIZE 16

typedef unsigned char byte;
typedef unsigned int uint;

// TODO: Make this work on all endianessess
union byteInt {
    byte b[4] = {0x00};
    uint i;
};
union byteShort {
    byte b[2] = {0x00};
    unsigned short s;
};

struct FileInfo {
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


#ifdef TPS
const float VT = 60.0f/TPS;
const float FT = 1.0f/TPS;

const int WIDTH = 640;
const int HEIGHT = (WIDTH / 16) * 9;
const char NAME[] = "Dungeon Crawler";

const glm::mat4 IDENTITY = glm::mat4(1.0f);
#endif

// File types
const byte TYPE_UNDEF = 0x00;
const byte TYPE_TILE = 0x01;
const byte TYPE_SOLID = 0x02;
const byte TYPE_ENTITY = 0x04;
const byte TYPE_SHADER = 0x08;

// Log types
const int DEBUG = 0x00;
const int INFO = 0x02;
const int WARNING = 0x03;
const int ERROR = 0x04;

// Exitcodes
enum {
    ERROR_UNDEF = -1,
    ERROR_NONE,
    ERROR_GLFW,
    ERROR_WINDOW,
    ERROR_GLEW,
    ERROR_SHADER_COMPILE,
    ERROR_ZLIB,
    ERROR_FRAMEBUFFER,
    ERROR_FT
};

enum {
    themeNone = 0,
    themeDungeon
};

#endif
