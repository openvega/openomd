#pragma once
#include "openomd/recoverypolicy.h"
#include "openomd/msgcache.h"

namespace openomd
{
class NoopLineArbitration : public NoopRecoveryPolicy, protected MapBasedCache
{
public:
    inline bool checkPktSeq(openomd::PktHdr const& pktHdr, char* pos)
    {
        return true;
    }
    inline bool checkPktSeqWithtouRecovery(openomd::PktHdr const& pktHdr, char* pos)
    {
        return true;
    }
    inline bool checkMsgSeq(uint32_t)
    {
        return true;
    }
    inline void resetSeqNum(uint32_t newSeqNum)
    {
    }
    template <typename _Func>
    inline void processCache(_Func func)
    {
    }
};
}