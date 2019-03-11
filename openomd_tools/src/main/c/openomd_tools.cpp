#include <iostream>
#include <fstream>
#include "cxxopts.hpp"
#include "openomd/linearbitration.h"
#include "openomd/nooplinearbitration.h"
#include "openomd/recoverypolicy.h"
#include "omdprintprocessor.h"
#include "pcaprunner.h"
#include "multicastrunner.h"

using RefreshLineArbitration = openomd::LineArbitration<openomd::MapBasedCache, openomd::RefreshChannelRecoveryPolicy<openomd::MulticastReceiver>>;

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
        ("n,networkconf", "network configuration file", cxxopts::value<string>())
        ("s,sll","1,0", cxxopts::value<int32_t>());
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
            bool sll = false;
            if (result.count("s") == 1 && result["s"].as<int32_t>() == 1)
            {
                sll = true;
            }
            auto protocol = result["p"].as<string>();
            auto pcapFile = result["c"].as<string>();
            auto networkCfg = result["n"].as<string>();
            cout << "function=" << function << " p=" << protocol << " pcap=" << pcapFile << " netconf=" << networkCfg << " sll=" << sll << endl;
            if (protocol == "omdc")
            {
                OmdPcapRunner<OmdcPrintProcessor<PcapLineArbitration>, OmdcParser> runner{ getChannelConfig(networkCfg), pcapFile, sll };
                runner.run();
            }
            else if (protocol == "omdd")
            {
                OmdPcapRunner<OmddPrintProcessor<NoopLineArbitration>, OmddParser> runner{ getChannelConfig(networkCfg), pcapFile, sll };
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
                OmdMulticastRunner<OmdcPrintProcessor<RefreshLineArbitration>, OmdcParser> runner{ getChannelConfig(networkCfg) };
                runner.init();
                runner.start();
                runner.run();
                runner.stop();
            }
            else if (protocol == "omdd")
            {
                OmdMulticastRunner<OmddPrintProcessor<RefreshLineArbitration>, OmddParser> runner{ getChannelConfig(networkCfg)};
                runner.init();
                runner.start();
                runner.run();
                runner.stop();
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
