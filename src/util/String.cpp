# include "Standard.h"

// TODO: Improve this code!
// NOTE: This is not my code
std::string String::format(const char *fmt, ...) {
    int size = 512;
    char *buffer = 0;
    buffer = new char[size];
    va_list vl;
    va_start(vl, fmt);
    int nsize = vsnprintf(buffer, size, fmt, vl);
    if(size <= nsize) {
	delete[] buffer;
	buffer = nullptr;
	buffer = new char[nsize+1];
	nsize = vsnprintf(buffer, size, fmt, vl);
    }
    std::string ret(buffer);
    va_end(vl);
    delete[] buffer;
    buffer = nullptr;
    return ret;
}
