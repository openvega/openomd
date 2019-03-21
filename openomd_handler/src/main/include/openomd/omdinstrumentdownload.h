#pragma once
#include "openomd/multicastutil.h"
#include "openomd/channelconfig.h"

namespace openomd
{
template <typename _Processor, typename _RefreshProcessor, typename _Parser>
class OmdInstrumentDownload
{
public:
    struct Runner
    {
        MulticastReceiver _refreshReceiver;
        _RefreshProcessor _refreshProcessor;
        _Parser _parser;
        bool _completed = false;

        Runner(IOServiceLC& ioService, ChannelConfig const& c)
            : _refreshReceiver{c.channel, c.port, c.refreshListenIp, c.refreshIp, ioService }
        {
        }

        void init()
        {
            _refreshReceiver.init();
            _refreshReceiver.registerAsyncReceive(&Runner::processRefresh, this);
        }

        void start()
        {
            _refreshReceiver.start();
        }

        void stop()
        {
            _refreshReceiver.stop();
        }

        void processRefresh(const boost::system::error_code& error, size_t bytesRecvd, char* data, size_t maxLength)
        {
            if (error)
            {
                std::cout << "processRefresh error: " << error.message();
            }
            else
            {
                _parser.parse(data, bytesRecvd, _refreshProcessor);
                if (_refreshProcessor.refreshCompleted())
                {
                    _refreshProcessor.consumeAll([&](char* d, size_t s) {
                        _parser.parseRefresh(d, s, OmdInstrumentDownload::_processor);
                    });
                    _refreshReceiver.stop();
                    _completed = true;
                }
                _refreshReceiver.registerAsyncReceive(&Runner::processRefresh, this);
            }

        }
    };

    OmdInstrumentDownload(std::vector<ChannelConfig> const& channelConfig)
    {
        for_each(channelConfig.begin(), channelConfig.end(), [&](auto const& c) {
            _runner.emplace_back(std::make_unique<Runner>(_ioServiceLC, c));
        });
    }

    void init()
    {
        _ioServiceLC.init();
        for_each(_runner.begin(), _runner.end(), [](auto& r) { r->init(); });
    }

    void start()
    {
        _ioServiceLC.start();
        for_each(_runner.begin(), _runner.end(), [](auto& r) { r->start(); });
    }

    void run()
    {
        _ioServiceLC.run();
        bool allCompleted = true;
        for_each(_runner.begin(), _runner.end(), [&](auto& r) { allCompleted &= r->_completed; });
        if (allCompleted)
        {
            stop();
            _processor.dump();
        }
    }

    void stop()
    {
        for_each(_runner.begin(), _runner.end(), [](auto& r) { r->stop(); });
        _ioServiceLC.stop();
    }

private:
    IOServiceLC _ioServiceLC;
    std::vector<std::unique_ptr<Runner>> _runner;
    _Processor _processor;
};
}