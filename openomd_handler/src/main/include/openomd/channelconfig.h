#pragma once
#pragma once
#include <vector>
#include <boost/tokenizer.hpp>
#include <fstream>

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

    uint16_t refreshPort;
    std::string refreshListenIp;
    std::string refreshIp;

    static inline ChannelConfig convert(std::string const& line)
    {
        boost::escaped_list_separator<char> delimiters{ '\\', ',', '"' };
        boost::tokenizer<boost::escaped_list_separator<char>> tk{ line, delimiters };

        std::vector<std::string> vs;
        std::copy(tk.begin(), tk.end(), std::back_inserter(vs));

        int32_t i = 0;
        ChannelConfig config{
            atol(vs[i++].c_str()),  // channel id
            (uint16_t)atol(vs[i++].c_str()),  // port
            vs[i++],                // listen ipA
            vs[i++],                // ipA
            vs[i++],                // listen ipB
            vs[i++],                // ipB
            (uint16_t)atol(vs[i++].c_str()),  // refresh port
            vs[i++],                // refresh listen ip
            vs[i++]                 // refresh ip
        };
        return config;
    }

    static inline std::vector<ChannelConfig> getChannelConfig(std::string const& filename)
    {
        std::ifstream istrm(filename);
        if (istrm.is_open())
        {
            std::vector<ChannelConfig> channels;
            std::string line;
            while (std::getline(istrm, line) && !line.empty())
            {
                channels.emplace_back(openomd::ChannelConfig::convert(line));
            }
            return channels;
        }
        throw std::runtime_error("Fail to open config file");
    }
};
}
