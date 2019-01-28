#pragma once
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace openomd
{
class IOServiceLC
{
public:
    boost::asio::io_service& ioService() {
        return _ioService;
    }

    std::string const& name() const
    {
        static std::string name{"IOServiceLC"};
        return name;
    }
    void init() {
    }
    void start() {}
    void run() {
        _ioService.run();
    }
    void stop() {}

private:
    boost::asio::io_service _ioService;
};

template <typename _CB>
class MulticastReceiver
{
public:
    explicit MulticastReceiver(std::string const& bindIp,
        std::string const& listenIp,
        std::string const& multicastIp,
        std::string const& outboundIp,
        uint16_t port, int32_t channel, _CB& callback, IOServiceLC& ioServiceLC)
        : _callback{callback}
        , _ioService{ioServiceLC.ioService()}
        , _socket{ioServiceLC.ioService()}
        , _bindIp{bindIp}
        , _listenIp{listenIp}
        , _multicastIp{multicastIp}
        , _outboundIp{outboundIp}
        , _port{port}
        , _channel{channel}
    {
        _name.append("MulticastReceiver-").append(multicastIp).append("-").append(std::to_string(_port));
        //LOG_INFO(_log) << _name << " listening on " << listenIp;
    }

    std::string const& name() const
    {
        return _name;
    }
    void init();
    void start();
    void run();
    void stop();

    void processData(const boost::system::error_code& error, size_t bytesRecvd, char* data, size_t maxLength);

private:
    template <typename _F, typename _O>
    void registerAsyncReceive(_F&& f, _O&& o)
    {
        using namespace boost::asio;
        _socket.async_receive_from(buffer(_data, maxLength), _senderEp,
            boost::bind(f, o, placeholders::error, placeholders::bytes_transferred, _data, maxLength));
    }

    void do_close();

    _CB& _callback;
    boost::asio::io_service& _ioService;
    boost::asio::ip::udp::socket _socket;
    std::string _bindIp;
    std::string _listenIp;
    std::string _multicastIp;
    std::string _outboundIp;
    uint16_t _port;
    int32_t _channel;
    std::string _name;

    boost::asio::ip::udp::endpoint _senderEp;
    enum {
        maxLength = 65536
    };
    char _data[maxLength];
};

template<typename _CB>
inline void MulticastReceiver<_CB>::init()
{
    try
    {
        using namespace boost::asio;
        ip::udp::endpoint bindEp(_bindIp.empty() ? ip::address_v4::any() : ip::address_v4::from_string(_bindIp), _port);

        _socket.open(bindEp.protocol());
        _socket.set_option(ip::udp::socket::reuse_address(true));
        _socket.set_option(ip::multicast::enable_loopback(true));
        _socket.set_option(ip::multicast::hops(255));
        if (!_outboundIp.empty())
        {
            _socket.set_option(ip::multicast::outbound_interface(ip::address_v4::from_string(_outboundIp)));
        }
        _socket.bind(bindEp);
        //LOG_INFO(_log) << "MulticastReceiver bind successfully";
        boost::system::error_code ec;
        if (_listenIp.empty())
        {
            _socket.set_option(ip::multicast::join_group(ip::address_v4::from_string(_multicastIp)));
        }
        else
        {
            _socket.set_option(ip::multicast::join_group(ip::address_v4::from_string(_multicastIp), ip::address_v4::from_string(_listenIp)));
        }
        //LOG_INFO(_log) << "MulticastReceiver join multicast group successfully";
    }
    catch (std::exception const& e)
    {
        //LOG_ERROR(_log) << "fail to join multicast " << _multicastIp << " error:" << e.what();
        throw e;
    }
    registerAsyncReceive(&MulticastReceiver::processData, this);
}

template<typename _CB>
inline void MulticastReceiver<_CB>::start()
{
}

template<typename _CB>
inline void MulticastReceiver<_CB>::run()
{
}

template<typename _CB>
inline void MulticastReceiver<_CB>::stop()
{
    _ioService.post(boost::bind(&MulticastReceiver<_CB>::do_close, this));
}

template<typename _CB>
void MulticastReceiver<_CB>::processData(const boost::system::error_code& error, size_t bytesRecvd, char* data, size_t maxLength)
{
    if (error)
    {
        //LOG_WARN(_log) << "Multicast receiver failed: " << error.message();
    }
    else
    {
        _callback.onReceive(bytesRecvd, data, maxLength);
        registerAsyncReceive(&MulticastReceiver::processData, this);
    }
}

template<typename _CB>
void MulticastReceiver<_CB>::do_close()
{
    _socket.close();
}

}
