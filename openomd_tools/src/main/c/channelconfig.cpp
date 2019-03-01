#include <boost/tokenizer.hpp>
#include "channelconfig.h"

namespace openomd
{
ChannelConfig ChannelConfig::convert(std::string const & s)
{
    boost::escaped_list_separator<char> delimiters{'\\', ',', '"'};
    boost::tokenizer<boost::escaped_list_separator<char>> tk{s, delimiters};

    std::vector<std::string> vs;
    std::copy(tk.begin(), tk.end(), std::back_inserter(vs));

    int32_t i= 0;
    ChannelConfig config{
        atol(vs[i++].c_str()),  // channel id
        vs[i++],                // ipA
        atol(vs[i++].c_str()),  // portA
        vs[i++],                // refresh ipA
        atol(vs[i++].c_str()),  // refresh portA
        vs[i++],                // listen ipA
        vs[i++],                // ipB
        atol(vs[i++].c_str()),  // portB
        vs[i++],                // refresh ipB
        atol(vs[i++].c_str()),  // refresh portB
        vs[i++]                 // listen ipB
    };
    return config;
}
}
