#pragma once
#include <pcap.h>
#include <string>
#include "ethernet.h"

namespace openomd
{
struct TimePolicy
{
    void timeMultiplier(int32_t multiplier)
    {
        _multiplier = multiplier;
    }

    int32_t _multiplier = 1000;
};
struct TimePlaybackPolicy : public TimePolicy
{
    TimePlaybackPolicy(double speed) : _speed{ speed }
    {}

    using TimePolicy::timeMultiplier;
    
    void wait(struct timeval& tv)
    {
    }
private:
    double _speed;
};

struct BestEffectPlaybackPolicy : public TimePolicy
{
    BestEffectPlaybackPolicy(double speed) {}

    using TimePolicy::timeMultiplier;

    void wait(struct timeval& tv)
    {
    }
};

template <typename _CB, typename _PBPolicy = BestEffectPlaybackPolicy>
class PcapUtil : public _PBPolicy
{
    
public:
    PcapUtil(std::string const& pcapFile, _CB& callback, double speed = 1) 
        : _PBPolicy{ speed }, _pcapFile{ pcapFile }, _callback{ callback }
    {
    }

    virtual ~PcapUtil()
    {
        if (_pcapt)
        {
            pcap_close(_pcapt);
            _pcapt = nullptr;
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
    using _PBPolicy::timeMultiplier;
    using _PBPolicy::wait;
private:
    std::string _pcapFile;
    _CB& _callback;
    pcap_t* _pcapt = nullptr;
};

template <typename _CB, typename _PBPolicy>
inline void PcapUtil<_CB, _PBPolicy>::init()
{
}
template <typename _CB, typename _PBPolicy>
inline void PcapUtil<_CB, _PBPolicy>::start()
{
    // Retrive the magic in pcapHdr
    static const int32_t NSEC_TCPDUMP_MAGIC = 0xa1b23c4d;
    
    struct pcap_file_header hdr;
    FILE* pcapFile;
    if (fopen_s(&pcapFile, _pcapFile.c_str(), "rb"))
    {
        throw std::exception("Fail to fopen pcap file");
    }
    size_t readCount = fread((char *)&hdr, 1, sizeof(hdr), pcapFile);
    if (readCount == sizeof(hdr))
    {
        if (hdr.magic == NSEC_TCPDUMP_MAGIC)
        {
            timeMultiplier(1);
        }
    }

    char errMsg[PCAP_ERRBUF_SIZE];
    _pcapt = pcap_open_offline(_pcapFile.c_str(), errMsg);
    if (!_pcapt)
    {
        throw std::exception(errMsg);
    }
    
}

template <typename _CB, typename _PBPolicy>
inline void PcapUtil<_CB, _PBPolicy>::run()
{
    pcap_pkthdr* pkthdr;
    const uint8_t* pktData;
    int32_t retCode;
    while ( (retCode = pcap_next_ex(_pcapt, &pkthdr, &pktData)) == 1)
    {
        wait(pkthdr->ts);
        auto *ipPacket = reinterpret_cast<IpHdr const*>(pktData);
        switch (ipPacket->ip_p)
        {
        case IPPROTO_TCP:
        {
            throw std::exception("TCP pcap replay is not support");
        }
        case IPPROTO_UDP:
        {
            auto * udpPacket = reinterpret_cast<UdpFrame<> const*>(pktData);
            uint32_t byteRecvd = pkthdr->len - sizeof(UdpHdr);
            printf("%x%x %d\n", udpPacket->_hdr.ip_dst.s_addr, udpPacket->_hdr.uh_dport,
                ((udpPacket->_hdr.ip_dst.s_addr & 0xFF000000) >> 8) | udpPacket->_hdr.uh_dport);
            _callback.onReceive(byteRecvd, const_cast<uint8_t*>(&udpPacket->_payload[0]), ETHERNET_MAX_PAYLOAD, 
                ((udpPacket->_hdr.ip_dst.s_addr & 0xFF000000) >> 8) | udpPacket->_hdr.uh_dport);    // Parition = last_byte_in_IP >> 8 | port
        }
        }
    }
}
template <typename _CB, typename _PBPolicy>
inline void PcapUtil<_CB, _PBPolicy>::stop()
{
    if (_pcapt)
    {
        pcap_close(_pcapt);
        _pcapt = nullptr;
    }
}

}