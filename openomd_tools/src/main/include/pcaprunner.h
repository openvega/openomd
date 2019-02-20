#pragma once
#if defined(__linux__)
#include <arpa/inet.h>
#endif
#include <map>
#include "openomd/pcaputil.h"
#include "channelconfig.h"

namespace openomd
{
uint32_t convertIp(std::string const& ip)
{
    struct in_addr addr;
    if (inet_pton(AF_INET, ip.c_str(), &addr))
    {
        return addr.s_addr;
    }
    throw std::runtime_error("wrong ip");
}

template <typename _Processor, typename _Parser>
class OmdPcapRunner
{
public:
    struct Callback
    {
        std::map<std::pair<uint32_t, uint16_t>, int32_t> _addressToChannel;
        std::map<int32_t, _Processor> _processors;
        _Parser _parser;

        Callback(std::vector<ChannelConfig> const& channelConfig)
        {
            for_each(channelConfig.begin(), channelConfig.end(), [&](auto const& c) {
                _addressToChannel.emplace(std::make_pair(convertIp(c.ipA), c.portA), c.channel);
                _addressToChannel.emplace(std::make_pair(convertIp(c.ipB), c.portB), c.channel);
                _processors.emplace(c.channel, _Processor{});
            });
        }

        void onReceive(int32_t byteRecvd, uint8_t* data, int32_t max, uint32_t ip, uint16_t port)
        {
            auto pos = _addressToChannel.find({ ip, port });
            if (pos != _addressToChannel.end())
            {
                _parser.parse((char*)data, byteRecvd, _processors[pos->second]);
            }
        }
    };

    OmdPcapRunner(std::vector<ChannelConfig> const& channelConfig, std::string const& pcapFile)
        : _callback{ channelConfig }, _pcapFile{ pcapFile }
    {
    }

    void run()
    {
        openomd::PcapUtil<Callback> pcapUtil{ _pcapFile, _callback };
        pcapUtil.init();
        pcapUtil.start();
        pcapUtil.run();
        pcapUtil.stop();
    }

private:
    Callback _callback;
    std::string _pcapFile;
};
}
