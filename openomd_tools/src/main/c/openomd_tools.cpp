#include <iostream>
#include <fstream>
#include "cxxopts.hpp"
#include "openomd/linearbitration.h"
#include "openomd/nooplinearbitration.h"
#include "openomd/recoverypolicy.h"
#include "openomd/refreshprocessor.h"
#include "openomd/instrumentprocessor.h"
#include "openomd/omdinstrumentdownload.h"
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

template <typename _Runner>
void run(_Runner& runner)
{
    runner.init();
    runner.start();
    runner.run();
    runner.stop();
}

struct OMDDTranslatePolicy
{
    static std::string code(uint8_t country, uint8_t market, uint8_t instrumentGroup, uint8_t modifier, uint16_t commodityCode, uint16_t expiration, uint32_t strikePrice)
    {
        return "";
    }
    static const std::string Option;
    static const std::string Future;
    static const std::string FX;
    static const std::string Call;
    static const std::string Put;
    static const std::string American;
    static const std::string European;
};

const std::string OMDDTranslatePolicy::Option{"Option"};
const std::string OMDDTranslatePolicy::Future{"Future"};
const std::string OMDDTranslatePolicy::FX{"FX"};
const std::string OMDDTranslatePolicy::Call{"C"};
const std::string OMDDTranslatePolicy::Put{"P"};
const std::string OMDDTranslatePolicy::American{"A"};
const std::string OMDDTranslatePolicy::European{"E"};

struct OMDCTranslatePolicy
{
    static const std::string Equity;
    static const std::string Warrant;
    static const std::string Cbbc;
    static const std::string ETF;
    static const std::string Call;
    static const std::string Put;
    static const std::string American;
    static const std::string European;
};
const std::string OMDCTranslatePolicy::Equity{"Equity"};
const std::string OMDCTranslatePolicy::Warrant{"Warrant"};
const std::string OMDCTranslatePolicy::Cbbc{"CBBC"};
const std::string OMDCTranslatePolicy::ETF{"ETF"};
const std::string OMDCTranslatePolicy::Call{"C"};
const std::string OMDCTranslatePolicy::Put{"P"};
const std::string OMDCTranslatePolicy::American{"A"};
const std::string OMDCTranslatePolicy::European{"E"};
int main(int32_t argc, char* argv[])
{
    using namespace std;
    using namespace openomd;
    cxxopts::Options options("openomd_tools", "Openomd Tools");
    options.add_options()
        ("f,function", "pcapdump,udpdump,instrument", cxxopts::value<string>())
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
                run(runner);
            }
            else if (protocol == "omdd")
            {
                OmdPcapRunner<OmddPrintProcessor<NoopLineArbitration>, OmddParser> runner{ getChannelConfig(networkCfg), pcapFile, sll };
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
            cout << "function=" << function << " p=" << protocol << " netconf=" << networkCfg << endl;
            if (protocol == "omdc")
            {
                OmdMulticastRunner<OmdcPrintProcessor<RefreshLineArbitration>, OmdcRefreshProcessor, OmdcParser> runner{ getChannelConfig(networkCfg) };
                run(runner);
            }
            else if (protocol == "omdd")
            {
                OmdMulticastRunner<OmddPrintProcessor<RefreshLineArbitration>, OmddRefreshProcessor, OmddParser> runner{ getChannelConfig(networkCfg)};
                run(runner);
            }
        }
        else if (function == "instrument")
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
                OmdInstrumentDownload<OMDCInstrumentProcessor<OMDCTranslatePolicy>, OmdcRefreshProcessor, OmdcParser> runner{ getChannelConfig(networkCfg) };
                run(runner);
            }
            else if (protocol == "omdd")
            {
                OmdInstrumentDownload<OMDDInstrumentProcessor<OMDDTranslatePolicy>, OmddRefreshProcessor, OmddParser> runner{ getChannelConfig(networkCfg) };
                run(runner);
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
