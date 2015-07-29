#ifndef READER_H
#define READER_H

class Reader {

    public:
	static void load(std::string*);
	static void getWithType(byte type, uint *idList);
	static std::string getName(uint id);
	static uint getId(std::string);
	static v2i getImageSize(int id);
	static void read(int id, byte*);
	static void freeReader();
};

#endif
