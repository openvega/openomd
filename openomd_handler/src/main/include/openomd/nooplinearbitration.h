#pragma once
#include "openomd/recoverypolicy.h"
#include "openomd/msgcache.h"

namespace openomd
{
class NoopLineArbitration : public NoopRecoveryPolicy, protected MapBasedCache
{
public:
    bool checkPktSeq(openomd::PktHdr const& pktHdr, char* pos)
    {
        return true;
    }
    bool checkPktSeqWithtouRecovery(openomd::PktHdr const& pktHdr, char* pos)
    {
        return true;
    }
    bool checkMsgSeq(uint32_t)
    {
        return true;
    }
    void resetSeqNum(uint32_t newSeqNum)
    {
    }
    template <typename _Func>
    void processCache(_Func func)
    {
    }
};
}