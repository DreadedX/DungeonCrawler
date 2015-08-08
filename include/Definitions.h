#ifndef DEFINITION_H
#define DEFINITION_H

#define MAX_SHADER_SIZE 1000
#define MAX_FILE_SIZE 4000000
#define FILE_NOT_FOUND 65536

#define BUFFER_COUNT_GL 8
#define BUFFER_COUNT_AL 8

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

const float VT = 60.0f/TPS;
const float FT = 1.0f/TPS;

const int WIDTH = 608;
const int HEIGHT = (WIDTH / 4 * 3);
const char NAME[] = "Platformer";

const mat4 IDENTITY = mat4(1.0f);

// File types
// 0000 0001
const byte TYPE_UNDEF = 0x00;
// 0000 0001
const byte TYPE_TILE = 0x01;
// 0000 0010
const byte TYPE_SOLID = 0x02;
// 0000 0100
const byte TYPE_ENTITY = 0x04;
// 1000 0000
// byte HAS_ALPHA = 0x80;

// Log types
const int DEBUG = 0x00;
const int INFO = 0x02;
const int WARNING = 0x03;
const int ERROR = 0x04;

// Exitcodes
const int ERROR_UNDEF = -1;
const int ERROR_GLFW = 1;
const int ERROR_WINDOW = 2;
const int ERROR_GLEW = 3;
const int ERROR_SHADER_COMPILE = 4;
const int ERROR_ZLIB = 5;
const int ERROR_LEVEL = 5;

#endif
