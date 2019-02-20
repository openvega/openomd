#pragma once
#pragma once
#include <vector>

namespace openomd
{
struct ChannelConfig
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

    static ChannelConfig convert(std::string const& line);
};
}