#pragma once
#include <map>
#include "openomd/pcaputil.h"

namespace openomd
{
struct PcapChannelConfig
{
    int32_t channel;
    uint32_t ipA;
    uint16_t portA;
    uint32_t ipB;
    uint16_t portB;
};

template <typename _Processor, typename _Parser>
class OmdPcapRunner
{
public:
    struct Callback
    {
        std::map<std::pair<uint32_t, uint16_t>, int32_t> _addressToChannel;
        std::map<int32_t, _Processor> _processors;
        _Parser _parser;

        Callback(std::vector<PcapChannelConfig> const& channelConfig)
        {
            for_each(channelConfig.begin(), channelConfig.end(), [&](auto const& c) {
                _addressToChannel.emplace(std::make_pair(c.ipA, c.portA), c.channel);
                _addressToChannel.emplace(std::make_pair(c.ipB, c.portB), c.channel);
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

    OmdPcapRunner(std::vector<PcapChannelConfig> const& channelConfig, std::string const& pcapFile)
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