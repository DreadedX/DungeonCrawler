#ifndef LOG_H
#define LOG_H

const int DEBUG = 0x00;
const int INFO = 0x02;
const int WARNING = 0x03;
const int ERROR = 0x04;

namespace Log {

    void print(std::string msg, int type);
};

#endif
