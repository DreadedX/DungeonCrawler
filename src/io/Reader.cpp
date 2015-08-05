#include "Standard.h"

using namespace std;

namespace IO {
    namespace Reader {

	// TODO: Make this allocate the correct size
	static Gaff::fileInfo files[256];
	// TODO: Give this variable a better name;
	uint rG = 0;

	static void loadFile(std::string fileName);

	void load(string fileName[]) {

	    // TODO: Add error handeling to opening files
	    // TODO: Make this not hardcoded
	    int count = 1;
	    for (int i = 0; i < count; i++) {
		Log::print(String::format("Loading: %s", fileName[i].c_str()), DEBUG);
		loadFile(fileName[i]);
	    }
	}

	void loadFile(std::string fileName) {

	    ifstream file(fileName, ios::in | ios::binary);

	    byte magic[4] = {0x00};
	    file.read(reinterpret_cast<char*>(magic), 4);

	    if (magic[0] != Gaff::MAGIC[0] || magic[1] != Gaff::MAGIC[1] || magic[2] != Gaff::MAGIC[2] || magic[3] != Gaff::MAGIC[3]) {
		Log::print(String::format("File is not in the gaff format: %s", fileName.c_str()), ERROR);
		return;
	    }

	    byte version[1] = {0x00};
	    file.read(reinterpret_cast<char*>(version), 1);
	    if (version[0] != Gaff::VERSION) {
		Log::print(String::format("File is a unknown version: %s", fileName.c_str()), ERROR);
		return;
	    }

	    byteInt fileCount;
	    file.read(reinterpret_cast<char*>(fileCount.b), 2);

	    // Gaff::fileInfo files[fileCount.i];
	    for(uint r = rG; r < rG+fileCount.i; r++) {
		files[r].origin = fileName;

		// Get name
		byte nameSize[] = {0x00};
		file.read(reinterpret_cast<char*>(nameSize), 1);
		files[r].nameSize = nameSize[0];

		byte name[files[r].nameSize];
		file.read(reinterpret_cast<char*>(name), files[r].nameSize);
		files[r].name.assign(reinterpret_cast<char*>(name), files[r].nameSize);

		// Get type
		byte type[1] = {0x00};
		file.read(reinterpret_cast<char*>(type), 1);
		files[r].type = type[0];

		file.read(reinterpret_cast<char*>(files[r].extra.b), 4);

		// Get content offset
		file.read(reinterpret_cast<char*>(files[r].offset.b), 4);

		// Get content size
		file.read(reinterpret_cast<char*>(files[r].size.b), 4);

	    }
	    rG += fileCount.i;

	    file.close();
	}

	void getWithType(byte type, uint *idList) {

	    int counter = 0;
	    for (uint i = 0; i < sizeof(files)/sizeof(Gaff::fileInfo); i++) {
		if ((files[i].type | type) == files[i].type) {
		    idList[counter] = i;
		    counter++;
		}
	    }
	}

	string getName(uint id) {

	    return files[id].name;
	}

	uint getId(string name) {

	    for(uint i = 0; i < sizeof(files)/sizeof(Gaff::fileInfo); i++) {
		if (files[i].name == name) {
		    return i;
		}
	    }
	    // TODO: Find a better way to deal with this
	    return 256;
	}

	vec2 getImageSize(int id) {

	    vec2 imageSize;
	    imageSize.x = (files[id].extra.b[1] << 8) + (files[id].extra.b[0]);
	    imageSize.y = (files[id].extra.b[3] << 8) + (files[id].extra.b[2]);

	    return imageSize;
	}

	void read(int id, byte data[]) {

	    ifstream file (files[id].origin, ios::in | ios::binary);
	    file.seekg(files[id].offset.i, ios::beg);
	    file.read(reinterpret_cast<char*>(data), files[id].size.i);
	}

	void freeReader() {

	    // free(files);
	}
    }
}
