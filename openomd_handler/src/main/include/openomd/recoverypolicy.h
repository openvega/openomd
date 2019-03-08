#pragma once
#include "openomd/omddef.h"

namespace openomd
{
struct NoopRecoveryPolicy
{
    void recover(PktHdr const& pktHdr, uint32_t& nextSeqNum)
    {
    }
    void stopRecovery()
    {
    }
};

struct PcapRecoveryPolicy
{
    void recover(PktHdr const& pktHdr, uint32_t& nextSeqNum)
    {
        // special case for first message in Pcap
        if (nextSeqNum == 1)
        {
            nextSeqNum = pktHdr.seqNum + 1;
        }
    }
    void stopRecovery()
    {
    }
};

struct RefreshChannelRecoveryPolicy
{
public:
    void recover(PktHdr const& pktHdr, uint32_t nextSeqNum)
    {
        // initial refresh channel

    }
    void stopRecovery()
    {

    }
};
}
