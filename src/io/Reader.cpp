#include "Standard.h"

using namespace std;

namespace IO {
    namespace Reader {

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
	// TODO: Make this allocate the correct size
	static FileInfo files[256];
	// TODO: Give this variable a better name;
	uint rG = 0;

	static void loadFile(std::string fileName);

	void load(string fileName[], int count) {

	    // TODO: Add error handeling to opening files
	    for (int i = 0; i < count; i++) {
		Log::print(String::format("Loading: %s", fileName[i].c_str()), DEBUG);
		loadFile(fileName[i]);
	    }
	}

	void loadFile(std::string fileName) {

	    ifstream file(fileName, ios::in | ios::binary);

	    byte magic[4] = {0x00};
	    file.read(reinterpret_cast<char*>(magic), 4);

	    if (magic[0] != MAGIC[0] || magic[1] != MAGIC[1] || magic[2] != MAGIC[2] || magic[3] != MAGIC[3]) {
		Log::print(String::format("File is not in the gaff format: %s", fileName.c_str()), ERROR);
		return;
	    }

	    byte version[1] = {0x00};
	    file.read(reinterpret_cast<char*>(version), 1);
	    if (version[0] != VERSION) {
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

	// TODO: Make this work without setting the size of the array
	void getWithType(byte type, uint *idList) {

	    int counter = 0;
	    for (uint i = 0; i < sizeof(files)/sizeof(FileInfo); i++) {
		if ((files[i].type | type) == files[i].type) {
		    idList[counter] = i;
		    counter++;
		}
	    }
	}

	int countWithType(byte type) {

	    int counter = 0;
	    for (uint i = 0; i < sizeof(files)/sizeof(FileInfo); i++) {
		if ((files[i].type | type) == files[i].type) {
		    counter++;
		}
	    }
	    
	    return counter;
	}

	string getName(uint id) {

	    return files[id].name;
	}

	byte getType(uint id) {

	    return files[id].type;
	}

	uint getId(string name) {

	    for(uint i = 0; i < sizeof(files)/sizeof(FileInfo); i++) {
		if (files[i].name == name) {
		    return i;
		}
	    }
	    return FILE_NOT_FOUND;
	}

	vec2 getImageSize(int id) {

	    vec2 imageSize;
	    imageSize.x = (files[id].extra.b[1] << 8) + (files[id].extra.b[0]);
	    imageSize.y = (files[id].extra.b[3] << 8) + (files[id].extra.b[2]);

	    return imageSize;
	}

	// TODO: Make this work without setting the size of the array
	void read(int id, byte *data) {

	    ifstream file (files[id].origin, ios::in | ios::binary);
	    file.seekg(files[id].offset.i, ios::beg);
	    byte compressedData[files[id].size.i];
	    // TODO: Make the size adjust automatically
	    byte uncompressedData[MAX_FILE_SIZE];
	    file.read(reinterpret_cast<char*>(compressedData), files[id].size.i);
	    long unsigned int length = MAX_FILE_SIZE;
	    long unsigned int lengthSource = files[id].size.i;
	    int result = uncompress(uncompressedData, &length, compressedData, lengthSource);
	    if (result != Z_OK) {
		Log::print(String::format("Decompression of: %s failed: %i", files[id].name.c_str(), result), ERROR);
		Game::stop(ERROR_ZLIB);
	    }
	    for (uint i = 0; i < length; i++) {
	    	data[i] = uncompressedData[i];
	    }

	    Log::print(String::format("Decompressed file: %s", files[id].name.c_str()), DEBUG);
	}
    }
}
