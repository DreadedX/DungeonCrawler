# include "Standard.h"

namespace String {

    // TODO: Improve this code!
    // NOTE: Not commented
    std::string format(const char *fmt, ...) {
	int size = 512;
	char *buffer = 0;
	buffer = new char[size];
	va_list vl;
	va_start(vl, fmt);
	int nsize = vsnprintf(buffer, size, fmt, vl);
	if(size <= nsize) {
	    delete[] buffer;
	    buffer = 0;
	    buffer = new char[nsize+1];
	    nsize = vsnprintf(buffer, size, fmt, vl);
	}
	std::string ret(buffer);
	va_end(vl);
	delete[] buffer;
	return ret;
    }
};
