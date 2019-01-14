#pragma once
#include <cstdint>

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
}