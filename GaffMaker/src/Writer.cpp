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

    makeFile("brickDark", 0xA3, imageSize(gimp_image.width, gimp_image.height), sizeof(gimp_image.pixel_data), gimp_image.pixel_data);

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

// Just to test
#define PNGSIGSIZE 8

bool validate(istream& source) {

    //Allocate a buffer of 8 bytes, where we can put the file signature.
    png_byte pngsig[PNGSIGSIZE];
    int is_png = 0;

    //Read the 8 bytes from the stream into the sig buffer.
    source.read((char*)pngsig, PNGSIGSIZE);

    //Check if the read worked...
    if (!source.good()) return false;

    //Let LibPNG check the sig. If this function returns 0, everything is OK.
    is_png = png_sig_cmp(pngsig, 0, PNGSIGSIZE);
    return (is_png == 0);
}
///////////////

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

