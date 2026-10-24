#pragma once
#include "Arduino.h"
#include <vector>
constexpr int CAN_OK=0, MCP_ANY=0, CAN_500KBPS=0, MCP_8MHZ=0, MCP_NORMAL=0;
struct Frame { unsigned long id; byte length; float first; float second; };
static std::vector<Frame> sent;
class MCP_CAN {
public:
    MCP_CAN(int) {}
    int begin(int,int,int) { return CAN_OK; }
    void setMode(int) {}
    int readMsgBuf(unsigned long*, unsigned char*, unsigned char*) { return CAN_OK; }
    int sendMsgBuf(unsigned long id, int, byte len, byte* data) {
        Frame frame{id,len,0,0};
        std::memcpy(&frame.first,data,4);
        std::memcpy(&frame.second,data+4,4);
        sent.push_back(frame);
        return CAN_OK;
    }
};
