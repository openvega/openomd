#pragma once
#include <vector>
#include "openomd/multicastutil.h"
#include "openomd/channelconfig.h"

namespace openomd
{
template <typename _Processor, typename _RefreshProcessor, typename _Parser>
class OmdMulticastRunner
{
public:
    struct Runner
    {
        MulticastReceiver _receiverA;
        MulticastReceiver _receiverB;
        MulticastReceiver _refreshReceiver;
        _Processor _processor;
        _RefreshProcessor _refreshProcessor;
        _Parser _parser;

        Runner(IOServiceLC& ioService, ChannelConfig const& c)
            : _receiverA{ c.channel, c.port, c.listenIpA, c.ipA, ioService }, 
              _receiverB{ c.channel, c.port, c.listenIpB, c.ipB, ioService },
              _refreshReceiver{ c.channel, c.port, c.refreshListenIp, c.refreshIp, ioService },
              _processor{ _refreshReceiver }
        {
        }

        void init()
        {
            _receiverA.init();
            _receiverB.init();
            _refreshReceiver.init();
            _receiverA.registerAsyncReceive(&Runner::processDataA, this);
            _receiverB.registerAsyncReceive(&Runner::processDataB, this);
            _refreshReceiver.registerAsyncReceive(&Runner::processRefresh, this);
        }
        void start()
        {
            _receiverA.start();
            _receiverB.start();
            _refreshReceiver.start();
        }

        void stop()
        {
            _receiverA.stop();
            _receiverB.stop();
            _refreshReceiver.stop();
        }

        void processDataA(const boost::system::error_code& error, size_t bytesRecvd, char* data, size_t maxLength)
        {
            if (error)
            {
                std::cout << "processDataA error: " << error.message();
            }
            else
            {
                _parser.parse(data, bytesRecvd, _processor);
                _receiverA.registerAsyncReceive(&Runner::processDataA, this);
            }
        }
        void processDataB(const boost::system::error_code& error, size_t bytesRecvd, char* data, size_t maxLength)
        {
            if (error)
            {
                std::cout << "processDataB error: " << error.message();
            }
            else
            {
                _parser.parse(data, bytesRecvd, _processor);
                _receiverB.registerAsyncReceive(&Runner::processDataB, this);
            }
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
                    // process all refresh msg
                    _refreshProcessor.consumeAll([&](char* d, size_t s) {
                        _parser.parseRefresh(d, s, _processor);
                    });
                    _processor.resetSeqNum(_refreshProcessor.nextSeqNum());
                    // process stored realtime msg
                    _parser.processCachedMsg(_processor);
                    std::cout << _refreshReceiver.name() << " Refresh Completed seq=" << _processor.nextSeqNum() << std::endl;
                    _refreshProcessor.reset();
                    _refreshReceiver.stop();
                }
                _refreshReceiver.registerAsyncReceive(&Runner::processRefresh, this);
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
            _runner.emplace_back(std::make_unique<Runner>( _ioServiceLC , c));
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
//        for_each(_receivers.begin(), _receivers.end(), [](auto& r) {
//            r.run();
//        });
    }

    void stop()
    {
        for_each(_runner.begin(), _runner.end(), [](auto& r) {
            r->stop();
        });
        _ioServiceLC.stop();
    }
private:
    IOServiceLC _ioServiceLC;
    std::vector<std::unique_ptr<Runner>> _runner;

};
}
