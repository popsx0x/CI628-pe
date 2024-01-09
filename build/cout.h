
#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <Windows.h>


class debugStreambuf : public std::streambuf {
public:
    virtual int_type overflow(int_type c = EOF) {
        if (c != EOF) {
            TCHAR buf[] = { c, '\0' };
            OutputDebugString(buf);
        }
        return c;
    }
};

class Cout2VisualStudioDebugOutput {

    debugStreambuf dbgstream;
    std::streambuf* default_stream;

public:
    Cout2VisualStudioDebugOutput() {
        default_stream = std::cout.rdbuf(&dbgstream);
    }

    ~Cout2VisualStudioDebugOutput() {
        std::cout.rdbuf(default_stream);
    }
};
#endif
//https://gist.github.com/takashyx/937f3a794ad36cd98ec3
