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

class MulticastReceiver
{
public:
    inline explicit MulticastReceiver(int32_t channel, uint16_t port,
        std::string const& listenIpA, std::string const& multicastIpA,
        std::string const& listenIpB, std::string const& multicastIpB,
        std::string const& refreshListenIp, std::string const& refreshIp,
        IOServiceLC& ioServiceLC,
        std::string const& bindIp = "",
        std::string const& outboundIp = "")
        : _ioService{ioServiceLC.ioService()}
        , _socket{ioServiceLC.ioService()}
        , _refreshSocket{ ioServiceLC.ioService() }
        , _channel{channel}
        , _port{port}
        , _listenIpA{listenIpA}
        , _multicastIpA{multicastIpA}
        , _listenIpB{listenIpB}
        , _multicastIpB{multicastIpB}
        , _refreshListenIp{refreshListenIp}
        , _refreshIp{refreshIp}
        , _bindIp{bindIp}
        , _outboundIp{outboundIp}
    {
        _name.append("MulticastReceiver-").append(std::to_string(_port)).append("-").append(_multicastIpA).append("-").append(_multicastIpB).append("-").append(_refreshIp);
        //LOG_INFO(_log) << _name << " listening on " << listenIp;
    }

    inline std::string const& name() const
    {
        return _name;
    }
    void init();
    void start();
    void run();
    void stop();

    void subscribeRefresh();
    void stopSubscribeRefresh();

    // Call registerAsyncReceive to receive multicast message. need to call this in the callback
    template <typename _F, typename _O>
    void registerAsyncReceive(_F&& f, _O&& o)
    {
        using namespace boost::asio;
        _socket.async_receive_from(buffer(_data, maxLength), _senderEp,
            boost::bind(f, o, placeholders::error, placeholders::bytes_transferred, _data, maxLength));
    }

    template <typename _F, typename _O>
    void registerRefreshAsyncReceive(_F&& f, _O&& o)
    {
        using namespace boost::asio;
        _refreshSocket.async_receive_from(buffer(_refreshData, maxLength), _senderEp,
            boost::bind(f, o, placeholders::error, placeholders::bytes_transferred, _refreshData, maxLength));
    }

private:
    void joinGroup(boost::asio::ip::udp::socket& socket, std::string const& listenIp, std::string const& multicastIp);
    void leaveGroup(boost::asio::ip::udp::socket& socket, std::string const& listenIp, std::string const& multicastIp);

    void do_close();

    boost::asio::io_service& _ioService;
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::socket _refreshSocket;
    int32_t _channel;
    uint16_t _port;
    std::string _listenIpA;
    std::string _multicastIpA;
    std::string _listenIpB;
    std::string _multicastIpB;
    std::string _refreshListenIp;
    std::string _refreshIp;
    std::string _bindIp;
    std::string _outboundIp;
    std::string _name;

    boost::asio::ip::udp::endpoint _senderEp;
    enum {
        maxLength = 65536
    };
    char _data[maxLength];
    char _refreshData[maxLength];
};

inline void MulticastReceiver::init()
{
    try
    {
        using namespace boost::asio;
        boost::asio::ip::udp::endpoint bindEp(_bindIp.empty() ? boost::asio::ip::address_v4::any() : boost::asio::ip::address_v4::from_string(_bindIp), _port);

        _socket.open(bindEp.protocol());
        _socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
        _socket.set_option(boost::asio::ip::multicast::enable_loopback(true));
        _socket.set_option(boost::asio::ip::multicast::hops(255));
        if (!_outboundIp.empty())
        {
            _socket.set_option(boost::asio::ip::multicast::outbound_interface(boost::asio::ip::address_v4::from_string(_outboundIp)));
        }
        _socket.bind(bindEp);

        _refreshSocket.open(bindEp.protocol());
        _refreshSocket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
        _refreshSocket.set_option(boost::asio::ip::multicast::enable_loopback(true));
        _refreshSocket.set_option(boost::asio::ip::multicast::hops(255));
        if (!_outboundIp.empty())
        {
            _refreshSocket.set_option(boost::asio::ip::multicast::outbound_interface(boost::asio::ip::address_v4::from_string(_outboundIp)));
        }
        _refreshSocket.bind(bindEp);
        //LOG_INFO(_log) << "MulticastReceiver join multicast group successfully";
    }
    catch (std::exception const& e)
    {
        //LOG_ERROR(_log) << "fail to join multicast " << _multicastIp << " error:" << e.what();
        throw e;
    }
}

inline void MulticastReceiver::start()
{
    joinGroup(_socket, _listenIpA, _multicastIpA);
    joinGroup(_socket, _listenIpB, _multicastIpB);
}

inline void MulticastReceiver::run()
{
}

inline void MulticastReceiver::stop()
{

    leaveGroup(_socket, _listenIpA, _multicastIpA);
    leaveGroup(_socket, _listenIpB, _multicastIpB);
    _ioService.post(boost::bind(&MulticastReceiver::do_close, this));
}

inline void MulticastReceiver::subscribeRefresh()
{
    joinGroup(_refreshSocket, _refreshListenIp, _refreshIp);
}

inline void MulticastReceiver::stopSubscribeRefresh()
{
    leaveGroup(_refreshSocket, _refreshListenIp, _refreshIp);
}

/*
void MulticastReceiver::processData(const boost::system::error_code& error, size_t bytesRecvd, char* data, size_t maxLength)
{
    if (error)
    {
        //LOG_WARN(_log) << "Multicast receiver failed: " << error.message();
    }
    else
    {
        _callback.onReceive(bytesRecvd, reinterpret_cast<uint8_t*>(data), maxLength);
        registerAsyncReceive(&MulticastReceiver::processData, this);
    }
}
*/

inline void MulticastReceiver::joinGroup(boost::asio::ip::udp::socket& socket, std::string const& listenIp, std::string const& multicastIp)
{
    if (multicastIp.empty())
    {
        return;
    }
    if (listenIp.empty())
    {
        socket.set_option(boost::asio::ip::multicast::join_group(boost::asio::ip::address_v4::from_string(multicastIp)));
    }
    else
    {
        socket.set_option(boost::asio::ip::multicast::join_group(boost::asio::ip::address_v4::from_string(multicastIp), boost::asio::ip::address_v4::from_string(listenIp)));
    }
}

inline void MulticastReceiver::leaveGroup(boost::asio::ip::udp::socket& socket, std::string const& listenIp, std::string const& multicastIp)
{
    if (multicastIp.empty())
    {
        return;
    }
    if (listenIp.empty())
    {
        socket.set_option(boost::asio::ip::multicast::leave_group(boost::asio::ip::address_v4::from_string(multicastIp)));
    }
    else
    {
        socket.set_option(boost::asio::ip::multicast::leave_group(boost::asio::ip::address_v4::from_string(multicastIp), boost::asio::ip::address_v4::from_string(listenIp)));
    }
}

void MulticastReceiver::do_close()
{
    _socket.close();
    _refreshSocket.close();
}

}
