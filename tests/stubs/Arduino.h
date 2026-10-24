#pragma once
#include <algorithm>
#include <cstring>
#include <cmath>
using std::max;
using byte = unsigned char;
constexpr int HEX = 16, INPUT = 0;
inline long random(long low, long) { return low; }
inline unsigned long millis() { return 3000; }
inline int digitalRead(int) { return 1; }
inline void pinMode(int, int) {}
struct SerialStub {
    void begin(int) {}
    int available() { return 0; }
    char read() { return '1'; }
    template<class T> void print(T) {}
    template<class T> void println(T) {}
    template<class T> void println(T, int) {}
    void println() {}
};
static SerialStub Serial;
