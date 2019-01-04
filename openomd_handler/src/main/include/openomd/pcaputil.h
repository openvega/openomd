#pragma once
#include <pcap.h>
#include "ethernet.h"

namespace openomd
{
struct TimePlaybackPolicy
{
    TimePlaybackPolicy(double speed) : _speed{ speed }
    {}

    void wait(struct timeval& tv)
    {
    }
private:
    double _speed;
};

struct BestEffectPlaybackPolicy
{
    BestEffectPlaybackPolicy(double speed) {}
    void wait(struct timeval& tv)
    {
    }
};

template <typename _CB, typename _PBPolicy = BestEffectPlaybackPolicy>
class PcapUtil : public _PBPolicy
{
public:
    PcapUtil(std::string const& pcapFile, _CB& callback, double speed = 1) : _PBPolicy{ speed }, _callback{ callback }
    {
        char errMsg[PCAP_ERRBUF_SIZE];
        _pcapt = pcap_open_offline(pcapFile.c_str(), errMsg);
        if (!_pcapt)
        {
            throw std::exception(errMsg);
        }
    }

    virtual ~PcapUtil()
    {
        if (_pcapt)
        {
            pcap_close(_pcapt);
        }
    }

    std::string const& name() const
    {
        static std::string name{"PcapUtil"};
        return name;
    }

    void init();
    void start();
    void run();
    void stop();
private:
    _CB& _callback;
    pcap_t* _pcapt;
    pcap_pkthdr _pkthdr;
};

template <typename _CB, typename _PBPolicy>
inline void PcapUtil<_CB, _PBPolicy>::init()
{
}
template <typename _CB, typename _PBPolicy>
inline void PcapUtil<_CB, _PBPolicy>::start()
{
}
template <typename _CB, typename _PBPolicy>
inline void PcapUtil<_CB, _PBPolicy>::run()
{
    while (const unsigned char* rawData = pcap_next(_pcapt, &_pkthdr))
    {
        wait(_pkthdr.ts);
        auto *ipPacket = reinterpret_cast<IpHdr const*>(rawData);
        switch (ipPacket->ip_p)
        {
        case IPPROTO_TCP:
        {
            auto * tcpPacket = reinterpret_cast<TcpFrame<> const*>(rawData);
            uint32_t byteRecvd = _pkthdr.len - sizeof(TcpHdr);
            _callback.onReceive(byteRecvd, const_cast<uint8_t*>(&tcpPacket->_payload[0]), ETHERNET_MAX_PAYLOAD, 0);
        }
        case IPPROTO_UDP:
        {
            auto * udpPacket = reinterpret_cast<UdpFrame<> const*>(rawData);
            uint32_t byteRecvd = _pkthdr.len - sizeof(UdpHdr);
            _callback.onReceive(byteRecvd, const_cast<uint8_t*>(&udpPacket->_payload[0]), ETHERNET_MAX_PAYLOAD, 0);
        }
        }
    }
}
template <typename _CB, typename _PBPolicy>
inline void PcapUtil<_CB, _PBPolicy>::stop()
{
}
}