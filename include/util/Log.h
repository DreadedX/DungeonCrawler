#ifndef LOG_H
#define LOG_H

const int DEBUG = 0x00;
const int INFO = 0x01;
const int WARNING = 0x02;
const int ERROR = 0x03;

namespace Log {

    void print(int msg);
    void print(std::string msg);
    void print(std::string msg, int type);
};

#endif
