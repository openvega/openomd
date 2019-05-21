#pragma once
#include "openomd/omddef.h"
#include "openomd/recoverypolicy.h"
#include "openomd/msgcache.h"

namespace openomd
{
class NoopLineArbitration : public NoopRecoveryPolicy, protected MapBasedCache
{
public:
    template <typename _Processor>
    inline bool checkPktSeq(_Processor&, openomd::PktHdr const& pktHdr, char* pos)
    {
        return true;
    }
    template <typename _Processor>
    inline bool checkPktSeqWithtouRecovery(_Processor&, openomd::PktHdr const& pktHdr, char* pos)
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
