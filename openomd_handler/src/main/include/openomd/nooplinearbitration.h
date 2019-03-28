#pragma once
#include "openomd/omddef.h"
#include "openomd/recoverypolicy.h"
#include "openomd/msgcache.h"

namespace openomd
{
class NoopLineArbitration : public NoopRecoveryPolicy, protected MapBasedCache, protected NoopLogger
{
public:
    inline bool checkPktSeq(int32_t channel, openomd::PktHdr const& pktHdr, char* pos)
    {
        return true;
    }
    inline bool checkPktSeqWithtouRecovery(int32_t channel, openomd::PktHdr const& pktHdr, char* pos)
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
    inline uint32_t nextSeqNum() const
    {
        return 0;
    }
};
}
