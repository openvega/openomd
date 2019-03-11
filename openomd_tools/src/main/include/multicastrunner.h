#pragma once
#include <vector>
#include "openomd/multicastutil.h"
#include "channelconfig.h"

namespace openomd
{
template <typename _Processor, typename _Parser>
class OmdMulticastRunner
{
public:
    struct Runner
    {
        MulticastReceiver& _receiver;
        _Processor _processor;
        _Parser _parser;

        Runner(MulticastReceiver& receiver) : _receiver{receiver}, _processor{receiver}
        {
        }

        void init()
        {
            _receiver.init();
            _receiver.subscribeRefresh();
            _receiver.registerAsyncReceive(&Runner::processData, this);
        }

        void stop()
        {
            _receiver.stop();
        }

        void processData(const boost::system::error_code& error, size_t bytesRecvd, char* data, size_t maxLength)
        {
            if (error)
            {
                //LOG_WARN(_log) << "Multicast receiver failed: " << error.message();
            }
            else
            {
                _parser.parse(data, bytesRecvd, _processor);
                _receiver.registerAsyncReceive(&Runner::processData, this);
            }
        }
        void onReceive(int32_t byteRecvd, uint8_t* data, int32_t max)
        {
            _parser.parse((char*)data, byteRecvd, _processor);
        }
    };

    OmdMulticastRunner(std::vector<ChannelConfig> const& channelConfig)
    {
        for_each(channelConfig.begin(), channelConfig.end(), [&](auto const& c) {
            _receivers.emplace_back(MulticastReceiver{c.channel, c.port, c.listenIpA, c.ipA, c.listenIpB, c.ipB, c.refreshListenIp, c.refreshIp, _ioServiceLC});
            
        });

        int32_t count = 0;
        for_each(channelConfig.begin(), channelConfig.end(), [&](auto const& c) {
            _runner.emplace_back(Runner{ _receivers[count] });
            count++;
        });
    }

    void init()
    {
        _ioServiceLC.init();
        for_each(_runner.begin(), _runner.end(), [](auto& r) { r.init(); });
    }

    void start()
    {
        _ioServiceLC.start();
//        for_each(_receivers.begin(), _receivers.end(), [](auto& r) {
//            r.start();
//        });
    }

    void run()
    {
        _ioServiceLC.run();
//        for_each(_receivers.begin(), _receivers.end(), [](auto& r) {
//            r.run();
//        });
    }

    void stop()
    {
        for_each(_runner.begin(), _runner.end(), [](auto& r) {
            r.stop();
        });
        _ioServiceLC.stop();
    }
private:
    IOServiceLC _ioServiceLC;
    std::vector<MulticastReceiver> _receivers;
    std::vector<Runner> _runner;

};
}
