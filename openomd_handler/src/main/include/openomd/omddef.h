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
    uint8_t filler;
    uint32_t seqNum;
    uint64_t sendTime;
};
struct MsgHdr
{
    uint16_t size;
    uint16_t type;
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
}

static inline void trim(std::string& s)
{
    ltrim(s);
    rtrim(s);
}
#ifndef ONMESSAGE
#define ONMESSAGE(_MSG) void onMessage(_MSG const&, uint32_t){}
#endif

class BaseProcessor
{
public:
    inline int32_t channel() const {
        return _channel;
    }
    inline void channel(int32_t channel) {
        _channel = channel;
    }
private:
    int32_t _channel;
};

struct NoopLogger
{
    inline void info(std::string const& str) const
    {
    }
    inline void warn(std::string const& str) const
    {
    }
    inline void error(std::string const& str) const
    {
    }
};
}
