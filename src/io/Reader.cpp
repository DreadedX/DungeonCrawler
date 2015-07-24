#include "io/Reader.h"

using namespace std;
//
// TODO: Make this allocate the correct size
static Gaff::fileInfo files[255];

void Reader::load(string extension) {
    string fileName = "out." + extension;
    ifstream file (fileName, ios::in | ios::binary);

    byte magic[4] = {0x00};
    file.read(reinterpret_cast<char*>(magic), 4);

    if (magic[0] == Gaff::MAGIC[0] && magic[1] == Gaff::MAGIC[1] && magic[2] == Gaff::MAGIC[2] && magic[3] == Gaff::MAGIC[3]) {
	cout << "Type: Gaff" << endl;
    }

    byte version[1] = {0x00};
    file.read(reinterpret_cast<char*>(version), 1);
    if (version[0] == Gaff::VERSION) {
	cout << "Version: 1" << endl;
    }

    byteInt fileCount;
    file.read(reinterpret_cast<char*>(fileCount.b), 2);
    cout << fileCount.i << endl;

    // Gaff::fileInfo files[fileCount.i];
    for(uint i = 0; i < fileCount.i; i++) {
	files[i].origin = fileName;
	
	// Get name
	byte nameSize[] = {0x00};
	file.read(reinterpret_cast<char*>(nameSize), 1);
	files[i].nameSize = nameSize[0];

	byte name[files[i].nameSize];
	file.read(reinterpret_cast<char*>(name), files[i].nameSize);
	files[i].name.assign(reinterpret_cast<char*>(name), files[i].nameSize);
	
	// Get type
	byte type[1] = {0x00};
	file.read(reinterpret_cast<char*>(type), 1);
	files[i].type = type[0];

	file.read(reinterpret_cast<char*>(files[i].extra.b), 4);
	
	// Get content offset
	file.read(reinterpret_cast<char*>(files[i].offset.b), 4);

	// Get content size
	file.read(reinterpret_cast<char*>(files[i].size.b), 4);

    }

    cout << "name type width height offset size" << endl;
    for(uint i = 0; i < fileCount.i; i++) {
	short width;
	width = (files[i].extra.b[1] << 8) + (files[i].extra.b[0]);
	short height;
	height = (files[i].extra.b[3] << 8) + (files[i].extra.b[2]);

	cout << files[i].name << " " << +files[i].type << " " << width << " " << height << " " << files[i].offset.i << " " << files[i].size.i << endl;
    }
    file.close();
}

uint Reader::getId(string name) {
    for(uint i = 0; i < sizeof(files)/sizeof(Gaff::fileInfo); i++) {
	if (files[i].name == name) {
	    return i;
	}
    }
    // TODO: Find better thing to return when an error has occured
    return 256;
}

size Reader::getImageSize(int id) {
    size imageSize;
    imageSize.width = (files[id].extra.b[1] << 8) + (files[id].extra.b[0]);
    imageSize.height = (files[id].extra.b[3] << 8) + (files[id].extra.b[2]);

    return imageSize;
}

void Reader::read(int id, byte data[]) {
    ifstream file (files[id].origin, ios::in | ios::binary);
    file.seekg(files[id].offset.i, ios::beg);
    file.read(reinterpret_cast<char*>(data), files[id].size.i);

    // for (uint i = 0; i < files[id].size.i; i += 3) {
	// cout << +data[i] << " " << +data[i+1] << " " << +data[i+2] << endl;
    // }

}
