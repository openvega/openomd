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

    ChannelConfig config{
        atol(vs[0].c_str()),
        vs[1],
        atol(vs[2].c_str()),
        vs[3],
        vs[4],
        atol(vs[5].c_str()),
        vs[6]
    };
    return config;
}
}