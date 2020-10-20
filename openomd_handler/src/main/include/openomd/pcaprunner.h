#pragma once
#include <map>
#include <boost/asio.hpp>
#include "openomd/pcaputil.h"
#include "openomd/channelconfig.h"

namespace openomd
{
uint32_t convertIp(std::string const& ip)
{
    boost::system::error_code ec;
    auto address = boost::asio::ip::make_address_v4(ip.c_str(), ec);
    if (!ec)
    {
        return htonl(address.to_uint());
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
                _addressToChannel.emplace(std::make_pair(convertIp(c.ipA), c.port), c.channel);
                _addressToChannel.emplace(std::make_pair(convertIp(c.ipB), c.port), c.channel);
                _processors.emplace(c.channel, _Processor{});
            });
        }

        void onReceive(struct timeval& ts, int32_t byteRecvd, uint8_t* data, int32_t max, uint32_t ip, uint16_t port)
        {
            auto pos = _addressToChannel.find({ ip, port });
            if (pos != _addressToChannel.end())
            {
                _parser.parse((char*)data, byteRecvd, _processors[pos->second]);
            }
        }
    };

    OmdPcapRunner(std::vector<ChannelConfig> const& channelConfig, std::string const& pcapFile, bool sll)
        : _callback{ channelConfig }, _pcapUtil{pcapFile, _callback, sll}
    {
    }

    void init()
    {
        _pcapUtil.init();
    }

    void start()
    {
        _pcapUtil.start();
    }

    void run()
    {
        _pcapUtil.run();
    }

    void stop()
    {
        _pcapUtil.stop();
    }

private:
    Callback _callback;
    openomd::PcapUtil<Callback> _pcapUtil;
};
}
