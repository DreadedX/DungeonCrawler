#ifndef READER_H
#define READER_H

namespace Reader {

    void load(std::string *fileName, int count);
    void getWithType(byte type, uint *idList);
    int countWithType(byte type);
    std::string getName(uint id);
    byte getType(uint id);
    uint getId(std::string);
    glm::vec2 getImageSize(int id);
    void read(int id, byte*);
};

#endif
