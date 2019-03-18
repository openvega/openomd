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
        std::string const& listenIp, std::string const& multicastIp,
        IOServiceLC& ioServiceLC,
        std::string const& bindIp = "",
        std::string const& outboundIp = "")
        : _ioService{ioServiceLC.ioService()}
        , _socket{ioServiceLC.ioService()}
        , _channel{channel}
        , _port{port}
        , _listenIp{listenIp}
        , _multicastIp{multicastIp}
        , _bindIp{bindIp}
        , _outboundIp{outboundIp}
    {
        _name.append("MulticastReceiver-").append(std::to_string(_port)).append("-").append(_multicastIp);
        //LOG_INFO(_log) << _name << " listening on " << listenIp;
    }

    ~MulticastReceiver();

    inline std::string const& name() const
    {
        return _name;
    }
    void init();
    void start();
    void run();
    void stop();

    // Call registerAsyncReceive to receive multicast message. need to call this in the callback
    template <typename _F, typename _O>
    void registerAsyncReceive(_F&& f, _O&& o)
    {
        using namespace boost::asio;
        _socket.async_receive_from(buffer(_data, maxLength), _senderEp,
            boost::bind(f, o, placeholders::error, placeholders::bytes_transferred, _data, maxLength));
    }

private:
    void joinGroup(boost::asio::ip::udp::socket& socket, std::string const& listenIp, std::string const& multicastIp);
    void leaveGroup(boost::asio::ip::udp::socket& socket, std::string const& listenIp, std::string const& multicastIp);

    void do_close();

    boost::asio::io_service& _ioService;
    boost::asio::ip::udp::socket _socket;
    int32_t _channel;
    uint16_t _port;
    std::string _listenIp;
    std::string _multicastIp;
    std::string _bindIp;
    std::string _outboundIp;
    std::string _name;
    bool _started = false;

    boost::asio::ip::udp::endpoint _senderEp;
    enum {
        maxLength = 65536
    };
    char _data[maxLength];
};

inline void MulticastReceiver::init()
{
    if (_multicastIp.empty())
    {

        return;
    }
    try
    {
        using namespace boost::asio;
        boost::asio::ip::udp::endpoint bindEp(boost::asio::ip::address_v4::from_string(_multicastIp), _port);

        _socket.open(bindEp.protocol());
        std::cout << _name << " _socket.open" << std::endl;
        _socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
        _socket.set_option(boost::asio::ip::multicast::enable_loopback(true));
        _socket.set_option(boost::asio::ip::multicast::hops(255));
        if (!_outboundIp.empty())
        {
            _socket.set_option(boost::asio::ip::multicast::outbound_interface(boost::asio::ip::address_v4::from_string(_outboundIp)));
        }
        _socket.bind(bindEp);
        std::cout << _name << " init success" <<std::endl;
        //LOG_INFO(_log) << "MulticastReceiver join multicast group successfully";
    }
    catch (std::exception const& e)
    {
        std::cout << _name << " failed to init " << e.what() << std::endl;
        //LOG_ERROR(_log) << "fail to join multicast " << _multicastIp << " error:" << e.what();
        throw e;
    }
}

inline MulticastReceiver::~MulticastReceiver()
{
    _ioService.post(boost::bind(&MulticastReceiver::do_close, this));
}

inline void MulticastReceiver::start()
{
    if (!_started)
    {
        joinGroup(_socket, _listenIp, _multicastIp);
        _started = true;
    }
}

inline void MulticastReceiver::run()
{
}

inline void MulticastReceiver::stop()
{
    if (_started)
    {
        leaveGroup(_socket, _listenIp, _multicastIp);
        _started = false;
    }
}

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
    std::cout << _name << " joined " << multicastIp << "@" << listenIp << std::endl;
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
    std::cout << _name << " left " << multicastIp << "@" << listenIp << std::endl;
}

void MulticastReceiver::do_close()
{
    _socket.close();
}

}
