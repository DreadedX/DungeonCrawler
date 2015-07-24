#include "Standard.h"

using namespace std;

struct fileAll {
    Gaff::fileInfo info;
    byte *data;
};

fileAll files[255];
int counter = 0;
byteInt offset;

void makeFile(string name, byte type, int extra, int size, byte data[]);
int imageSize(int width, int height);

int main() {
    // TODO: Make this all not hardcoded
    byte data1[] = {
	0x00, 0x00, 0xFF,  0x00, 0xFF, 0x00,  0xFF, 0x00, 0x00,  0xFF, 0xFF, 0xFF,
	0x00, 0xFF, 0x00,  0xFF, 0x00, 0x00,  0xFF, 0xFF, 0xFF,  0x00, 0x00, 0xFF,
	0xFF, 0x00, 0x00,  0xFF, 0xFF, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0xFF, 0x00,
	0xFF, 0xFF, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0xFF, 0x00,  0xFF, 0x00, 0x00
    };
    makeFile("testTexture", 0xA3, imageSize(4, 4), sizeof(data1), data1);
    byte data2[] = {
	0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF,  0xFF, 0x00, 0x00,  0x00, 0xFF, 0x00,  0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF,  0x00, 0x00, 0x00,  0x00, 0x00, 0xFF,  0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF
    };
    makeFile("demo", 0xA3, imageSize(4, 4), sizeof(data2), data2);

    byteShort fileCount;
    fileCount.s = counter;

    ofstream file ("out.gaff", ios::out | ios::binary);
    if (file.is_open()) {
	file << Gaff::MAGIC[0] << Gaff::MAGIC[1] << Gaff::MAGIC[2] << Gaff::MAGIC[3];
	file << Gaff::VERSION;
	for(int i = 0; i < 2; i++) {file << fileCount.b[i];}
    }

    offset.i = 4 + 1 + 2;
    for(int p = 0; p < counter; p++) {
	offset.i += 1 + files[p].info.name.length() + 1 + 4 + 4 + 4;
    }

    for(int p = 0; p < counter; p++) {
	files[p].info.offset = offset;
	offset.i += files[p].info.size.i;
    }

    for(int p = 0; p < counter; p++) {
	file << files[p].info.nameSize << files[p].info.name << files[p].info.type;
	for(int i = 0; i < 4; i++) {file << files[p].info.extra.b[i];}
	for(int i = 0; i < 4; i++) {file << files[p].info.offset.b[i];}
	for(int i = 0; i < 4; i++) {file << files[p].info.size.b[i];}
        
    }
    for(int p = 0; p < counter; p++) {
	for(int i = 0; i < 4*4*3; i++) {file << files[p].data[i];}
    }

    file.close();
}

int imageSize(int width, int height) {
    byteShort w;
    w.s = (short)width;
    byteShort h;
    h.s = (short)height;

    byteInt extra;
    extra.b[0] = w.b[0];
    extra.b[1] = w.b[1];
    extra.b[2] = h.b[0];
    extra.b[3] = h.b[1];

    return extra.i;
}

void makeFile(string name, byte type, int extra, int size, byte data[]) {
    files[counter].info.nameSize = name.length();
    files[counter].info.name = name;
    files[counter].info.type = type;
    files[counter].info.extra.i = extra;
    files[counter].info.size.i = size;
    files[counter].data = data;

    counter++;
}

