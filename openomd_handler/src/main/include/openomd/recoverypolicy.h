#pragma once
#include "openomd/omddef.h"

namespace openomd
{
struct NoopRecoveryPolicy
{
    void recover(PktHdr const& pktHdr, int32_t partition, uint32_t& nextSeqNum)
    {
    }
};

struct PcapRecoveryPolicy
{
    void recover(PktHdr const& pktHdr, int32_t partition, uint32_t& nextSeqNum)
    {
        // special case for first message in Pcap
        if (nextSeqNum == 1)
        {
            nextSeqNum = pktHdr.seqNum + 1;
        }
    }
};

struct RefreshChannelRecoveryPolicy
{
public:
    void recover(PktHdr const& pktHdr, int32_t partition, uint32_t nextSeqNum)
    {
        // initial refresh channel

    }
};
}