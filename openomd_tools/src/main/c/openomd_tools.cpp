#include <iostream>
#include <fstream>
#include "cxxopts.hpp"
#include "openomd/linearbitration.h"
#include "openomd/nooplinearbitration.h"
#include "omdprintprocessor.h"
#include "pcaprunner.h"
#include "multicastrunner.h"

std::vector<openomd::ChannelConfig> getChannelConfig(std::string filename)
{
    std::ifstream istrm(filename);
    if (istrm.is_open())
    {
        std::vector<openomd::ChannelConfig> channels;
        std::string line;
        while (std::getline(istrm, line) && !line.empty())
        {
            channels.emplace_back(openomd::ChannelConfig::convert(line));
        }   
        return channels;
    }
    throw std::runtime_error("Fail to open config file");
}

int main(int32_t argc, char* argv[])
{
    using namespace std;
    using namespace openomd;
    cxxopts::Options options("openomd_tools", "Openomd Tools");
    options.add_options()
        ("f,function", "pcapdump,udpdump", cxxopts::value<string>())
        ("p,protocol", "omdc,omdd", cxxopts::value<string>())
        ("c,pcap", "Pcap file", cxxopts::value<string>())
        ("n,networkconf", "network configuration file", cxxopts::value<string>());
    try
    {
        auto result = options.parse(argc, argv);
        auto function = result["f"].as<string>();
        if (function == "pcapdump")
        {
            if (result.count("p") == 0 || result.count("c") == 0 || result.count("n") == 0)
            {
                cerr << options.help() << endl;
                return -1;
            }
            auto protocol = result["p"].as<string>();
            auto pcapFile = result["c"].as<string>();
            auto networkCfg = result["n"].as<string>();
            cout << "function=" << function << " p=" << protocol << " pcap=" << pcapFile << " netconf=" << networkCfg << endl;
            if (protocol == "omdc")
            {
                
                OmdPcapRunner<OmdcPrintProcessor<PcapLineArbitration>, OmdcParser> runner{ getChannelConfig(networkCfg), pcapFile };
                runner.run();
            }
            else if (protocol == "omdd")
            {
                OmdPcapRunner<OmddPrintProcessor<PcapLineArbitration>, OmddParser> runner{ getChannelConfig(networkCfg), pcapFile };
                runner.run();
            }

        }
        else if (function == "udpdump")
        {
            if (result.count("p") == 0 || result.count("n") == 0)
            {
                cerr << options.help() << endl;
                return -1;
            }
            auto protocol = result["p"].as<string>();
            auto networkCfg = result["n"].as<string>();
            cout << "function=" << function << " p=" << protocol << " netconf=" << networkCfg << endl;
            if (protocol == "omdc")
            {
                OmdMulticastRunner<OmdcPrintProcessor<NoopLineArbitration>, OmdcParser> runner{ getChannelConfig(networkCfg) };
                runner.run();
            }
            else if (protocol == "omdd")
            {
                OmdMulticastRunner<OmddPrintProcessor<NoopLineArbitration>, OmddParser> runner{ getChannelConfig(networkCfg)};
                runner.run();
            }
        }
        else
        {
            cerr << options.help() << endl;
            return -1;
        }
    }
    catch (exception const& ex)
    {
        cerr << ex.what() << endl;
        cerr << options.help() << endl;
        return -1;
    }
}
