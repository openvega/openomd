#include <iostream>
#include <fstream>
#include "cxxopts.hpp"
#include "openomd/linearbitration.h"
#include "openomd/nooplinearbitration.h"
#include "openomd/recoverypolicy.h"
#include "openomd/refreshprocessor.h"
#include "openomd/pcaprunner.h"
#include "openomd/multicastrunner.h"
#include "omdprintprocessor.h"

static const std::string VERSION{ "2023.5" };

template <typename _Runner>
void run(_Runner& runner)
{
    runner.init();
    runner.start();
    runner.run();
    runner.stop();
}

class CoutBaseProcessor
{
public:
    inline int32_t channel() const {
        return _channel;
    }
    inline void channel(int32_t channel) {
        _channel = channel;
    }
    void onError(std::exception const& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    void info(std::string const& log) const
    {
        std::cout << log << std::endl;
    }
    void warn(std::string const& log) const
    {
        std::cout << log << std::endl;
    }
    void error(std::string const& log) const
    {
        std::cerr << log << std::endl;
    }
private:
    int32_t _channel;
};

using OmdcRefreshLineArbitration = openomd::LineArbitration<openomd::MapBasedCache, openomd::RefreshChannelRecoveryPolicy<openomd::MulticastReceiver, openomd::OmdcRefreshProcessor<CoutBaseProcessor>>>;
using OmddRefreshLineArbitration = openomd::LineArbitration<openomd::MapBasedCache, openomd::RefreshChannelRecoveryPolicy<openomd::MulticastReceiver, openomd::OmddRefreshProcessor<CoutBaseProcessor>>>;
using OmdccRefreshLineArbitration = openomd::LineArbitration<openomd::MapBasedCache, openomd::RefreshChannelRecoveryPolicy<openomd::MulticastReceiver, openomd::OmdccRefreshProcessor<CoutBaseProcessor>>>;

int main(int32_t argc, char* argv[])
{
    using namespace std;
    using namespace openomd;
    cxxopts::Options options("openomd_tools", "Openomd Tools v" + VERSION);
    options.add_options()
        ("f,function", "pcapdump,udpdump", cxxopts::value<string>())
        ("p,protocol", "omdc,omdd,omdcc", cxxopts::value<string>())
        ("c,pcap", "Pcap file", cxxopts::value<string>())
        ("n,networkconf", "network configuration file", cxxopts::value<string>())
        ("r,recovery", "perform recovery:1,0", cxxopts::value<int32_t>())
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
                OmdPcapRunner<OmdcPrintProcessor<PcapLineArbitration>, OmdcParser> runner{ ChannelConfig::getChannelConfig(networkCfg), pcapFile, sll };
                run(runner);
            }
            else if (protocol == "omdd")
            {
                OmdPcapRunner<OmddPrintProcessor<NoopLineArbitration>, OmddCompressParser> runner{ ChannelConfig::getChannelConfig(networkCfg), pcapFile, sll };
                run(runner);
            }
            else if (protocol == "omdcc")
            {
                OmdPcapRunner<OmdccPrintProcessor<NoopLineArbitration>, OmdccParser> runner{ ChannelConfig::getChannelConfig(networkCfg), pcapFile, sll };
                run(runner);
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
            bool recovery = true;
            if (result.count("r") == 1 && result["r"].as<int32_t>() == 0)
            {
                recovery = false;
            }
            cout << "function=" << function << " p=" << protocol << " netconf=" << networkCfg << " recovery=" << recovery << endl;
            if (protocol == "omdc")
            {
                if (recovery)
                {
                    OmdMulticastRunner<OmdcPrintProcessor<OmdcRefreshLineArbitration>, OmdcRefreshProcessor<CoutBaseProcessor>, OmdcParser> runner{ ChannelConfig::getChannelConfig(networkCfg) };
                    run(runner);
                }
                else
                {
                    OmdMulticastRunner<OmdcPrintProcessor<NoopLineArbitration>, OmdcRefreshProcessor<CoutBaseProcessor>, OmdcParser> runner{ ChannelConfig::getChannelConfig(networkCfg) };
                    run(runner);
                }
            }
            else if (protocol == "omdd")
            {
                if (recovery)
                {
                    OmdMulticastRunner<OmddPrintProcessor<OmddRefreshLineArbitration>, OmddRefreshProcessor<CoutBaseProcessor>, OmddCompressParser> runner{ ChannelConfig::getChannelConfig(networkCfg) };
                    run(runner);
                }
                else
                {
                    OmdMulticastRunner<OmddPrintProcessor<NoopLineArbitration>, OmddRefreshProcessor<CoutBaseProcessor>, OmddCompressParser> runner{ ChannelConfig::getChannelConfig(networkCfg) };
                    run(runner);
                }
            }

            else if (protocol == "omdcc")
            {
                if (recovery)
                {
                    OmdMulticastRunner<OmdccPrintProcessor<OmdccRefreshLineArbitration>, OmdccRefreshProcessor<CoutBaseProcessor>, OmdccParser> runner{ ChannelConfig::getChannelConfig(networkCfg) };
                    run(runner);
                }
                else
                {
                    OmdMulticastRunner<OmdccPrintProcessor<NoopLineArbitration>, OmdccRefreshProcessor<CoutBaseProcessor>, OmdccParser> runner{ ChannelConfig::getChannelConfig(networkCfg) };
                    run(runner);
                }
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
