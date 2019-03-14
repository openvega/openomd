#pragma once
#pragma once
#include <vector>

namespace openomd
{
struct ChannelConfig
{
    int32_t channel;
    uint16_t port;

    std::string listenIpA;
    std::string ipA;

    std::string listenIpB;
    std::string ipB;

    std::string refreshListenIp;
    std::string refreshIp;

    static ChannelConfig convert(std::string const& line);
};
}
