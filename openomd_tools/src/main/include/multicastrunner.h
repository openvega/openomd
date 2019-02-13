#pragma once
#include <vector>
#include "openomd/multicastutil.h"

namespace openomd
{
struct MulticastChannelConfig
{
    int32_t channel;
    std::string ipA;
    uint16_t portA;
    std::string bindIpA;
    std::string outboundIpA;
    std::string listenIpA;

    std::string ipB;
    uint16_t portB;
    std::string bindIpB;
    std::string outboundIpB;
    std::string listenIpB;
};
template <typename _Processor, typename _Parser>
class OmdMulticastRunner
{
public:
    struct Callback
    {
        _Processor _processor;
        _Parser _parser;

        void onReceive(int32_t byteRecvd, uint8_t* data, int32_t max)
        {
            _parser.parse((char*)data, byteRecvd, _processor);
        }
    };

    OmdMulticastRunner(std::vector<MulticastChannelConfig> const& channelConfig)
    {
        for_each(channelConfig.begin(), channelConfig.end(), [&](auto const& c) {
            _callbacks.emplace_back(Callback{});
            Callback& callback = _callbacks.back();
            _receivers.emplace_back(MulticastReceiver<Callback>{c.bindIpA, c.listenIpA, c.ipA, c.outboundIpA, c.portA, c.channel, callback, _ioServiceLC});
            _receivers.emplace_back(MulticastReceiver<Callback>{c.bindIpB, c.listenIpB, c.ipB, c.outboundIpB, c.portB, c.channel, callback, _ioServiceLC});
        });
    }

    void init()
    {
        _ioServiceLC.init();
        for_each(_receivers.begin(), _receivers.end(), [](auto& r) {
            r.init();
        });
    }

    void start()
    {
        _ioServiceLC.start();
        for_each(_receivers.begin(), _receivers.end(), [](auto& r) {
            r.start();
        });
    }

    void run()
    {
        _ioServiceLC.run();
        for_each(_receivers.begin(), _receivers.end(), [](auto& r) {
            r.run();
        });
    }

    void stop()
    {
        for_each(_receivers.begin(), _receivers.end(), [](auto& r) {
            r.stop();
        });
        _ioServiceLC.stop();
    }
private:
    IOServiceLC _ioServiceLC;
    std::vector<Callback> _callbacks;
    std::vector<MulticastReceiver<Callback>> _receivers;
};
}