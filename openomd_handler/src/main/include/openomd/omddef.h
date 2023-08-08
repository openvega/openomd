#pragma once
#include <cstdint>
#include <cctype>
#include <string>
#include <algorithm>

namespace openomd
{
struct PktHdr
{
    uint16_t size;
    uint8_t msgCnt;
    uint8_t compressionMode;
    uint32_t seqNum;
    uint64_t sendTime;
};
struct MsgHdr
{
    uint16_t size;
    uint16_t type;
};

enum AOBAction
{
    New = 0,
    Change,
    Delete,
    Clear = 74
};
static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    auto pos = s.find('\0');
    if (pos != std::string::npos)
    {
        s.erase(pos);
    }
}

static inline void trim(std::string& s)
{
    ltrim(s);
    rtrim(s);
}
#ifndef ONMESSAGE
#define ONMESSAGE(_MSG) void onMessage(_MSG const&, uint32_t){}
#endif
}
