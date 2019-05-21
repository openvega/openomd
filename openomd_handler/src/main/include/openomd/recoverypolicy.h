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

template <typename _MulticastHandler>
struct RefreshChannelRecoveryPolicy
{
public:
    RefreshChannelRecoveryPolicy(_MulticastHandler& multicastHandler) : _multicastHandler{multicastHandler}{}

    void recover(PktHdr const& pktHdr, uint32_t nextSeqNum)
    {
        _multicastHandler.start();
    }
    void stopRecovery()
    {
        _multicastHandler.stop();
    }

private:
    _MulticastHandler& _multicastHandler;
};
}
