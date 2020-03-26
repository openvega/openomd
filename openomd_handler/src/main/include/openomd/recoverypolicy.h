#pragma once
#include "openomd/omddef.h"

namespace openomd
{
struct NoopRecoveryPolicy
{
    NoopRecoveryPolicy()
    {
    }

    template <typename _MulticastHandler, typename _RefreshProcessor>
    NoopRecoveryPolicy(_MulticastHandler&, _RefreshProcessor&)
    {
    }

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

template <typename _MulticastHandler, typename _RefreshProcessor>
struct RefreshChannelRecoveryPolicy
{
public:
    RefreshChannelRecoveryPolicy(_MulticastHandler& multicastHandler, _RefreshProcessor& refreshProcessor) 
        : _multicastHandler{ multicastHandler }
        , _refreshProcessor{ refreshProcessor }
    {
    }

    void recover(PktHdr const& pktHdr, uint32_t nextSeqNum)
    {
        if (_refreshProcessor.refreshEnded())
        {
            _refreshProcessor.start();
            _multicastHandler.start();
        }
    }
    void stopRecovery()
    {
        _multicastHandler.stop();
    }

private:
    _MulticastHandler& _multicastHandler;
    _RefreshProcessor& _refreshProcessor;
};
}
