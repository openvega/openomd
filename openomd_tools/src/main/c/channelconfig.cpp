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
        atol(vs[i++].c_str()),  // port
        vs[i++],                // listen ipA
        vs[i++],                // ipA
        vs[i++],                // listen ipB
        vs[i++],                // ipB
        vs[i++],                // refresh listen ip
        vs[i++]                 // refresh ip
    };
    return config;
}
}
