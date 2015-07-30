#ifndef READER_H
#define READER_H

namespace IO {
    namespace Reader {

	void load(std::string*);
	void getWithType(byte type, uint *idList);
	std::string getName(uint id);
	uint getId(std::string);
	vec2 getImageSize(int id);
	void read(int id, byte*);
	void freeReader();
    };
};

#endif
