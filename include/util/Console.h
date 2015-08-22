#if DEBUG_MODE
#ifndef CONSOLE_H
#define CONSOLE_H
#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))

namespace Console {

    void show(bool *opened);
    void log(std::string text);
}

#endif
#endif

