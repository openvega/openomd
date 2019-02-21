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
    std::string listenIpA;

    std::string ipB;
    uint16_t portB;
    std::string listenIpB;

    static ChannelConfig convert(std::string const& line);
};
}