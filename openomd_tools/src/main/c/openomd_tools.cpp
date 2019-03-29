#include <iostream>
#include <fstream>
#include "cxxopts.hpp"
#include "openomd/linearbitration.h"
#include "openomd/nooplinearbitration.h"
#include "openomd/recoverypolicy.h"
#include "openomd/refreshprocessor.h"
#include "openomd/instrumentprocessor.h"
#include "openomd/omdinstrumentdownload.h"
#include "openomd/pcaprunner.h"
#include "openomd/multicastrunner.h"
#include "omdprintprocessor.h"

template <typename _Runner>
void run(_Runner& runner)
{
    runner.init();
    runner.start();
    runner.run();
    runner.stop();
}

struct BaseTranslatePolicy
{
    static const std::string Call;
    static const std::string Put;
    static const std::string American;
    static const std::string European;

    static const std::string HSI;
    static const std::string HSCEI;

    template <typename _Symbol, typename _Date>
    void write(std::ostream& os, _Symbol const& symbol, std::string const& code, std::string const& name, std::string const& secType, std::string const& currency,
            std::string const& exchange, uint32_t lotSize, std::string const& tickRule, int32_t unitValue, int32_t priceDenom, uint32_t mdid, std::string const& underlying, std::string const& underlyingExchange,
            _Date const& listing, _Date const& expiry, std::string const& optionClass, double strike, std::string const& optionType, std::string const& exerciseStyle,
            int64_t mNum, int64_t mDenom, int64_t contractSize, int64_t decimalInContractSize, double callPrice, double strike2) const
    {
        os << symbol << ","
            << code << ","
            << name << ","
            << secType << ","
            << currency << ","
            << exchange << ","
            << lotSize << ","
            << tickRule << ","
            << unitValue << ","
            << priceDenom << ","
            << mdid << ","
            << underlying << ","
            << underlyingExchange << ","
            << listing << ","
            << expiry << ","
            << optionClass << ","
            << strike << ","
            << optionType << ","
            << exerciseStyle << ","
            << mNum << ","
            << mDenom << ","
            << contractSize << ","
            << decimalInContractSize << ","
            << callPrice << ","
            << strike2;
    }
};
const std::string BaseTranslatePolicy::Call{"C"};
const std::string BaseTranslatePolicy::Put{"P"};
const std::string BaseTranslatePolicy::American{"A"};
const std::string BaseTranslatePolicy::European{"E"};
const std::string BaseTranslatePolicy::HSI{"HSI"};
const std::string BaseTranslatePolicy::HSCEI{"HSCEI"};

struct OMDCTranslatePolicy : public BaseTranslatePolicy
{
    static const std::pair<std::string, int32_t> Index;
    static const std::pair<std::string, int32_t> Equity;
    static const std::pair<std::string, int32_t> ETF;
    static const std::pair<std::string, int32_t> Warrant;
    static const std::pair<std::string, int32_t> Cbbc;
};
const std::pair<std::string, int32_t> OMDCTranslatePolicy::Index{"Index", 0};
const std::pair<std::string, int32_t> OMDCTranslatePolicy::Equity{"Equity", 1};
const std::pair<std::string, int32_t> OMDCTranslatePolicy::ETF{"Equity", 2};
const std::pair<std::string, int32_t> OMDCTranslatePolicy::Warrant{"Equity", 3};
const std::pair<std::string, int32_t> OMDCTranslatePolicy::Cbbc{"Equity", 4};

struct OMDDTranslatePolicy : public BaseTranslatePolicy
{
    static std::string code(uint8_t country, uint8_t market, uint8_t instrumentGroup, uint8_t modifier, uint16_t commodityCode, uint16_t expiration, uint32_t strikePrice)
    {
        return "";
    }
    static const std::string Option;
    static const std::string Future;
    static const std::string FX;
};

const std::string OMDDTranslatePolicy::Option{"Option"};
const std::string OMDDTranslatePolicy::Future{"Future"};
const std::string OMDDTranslatePolicy::FX{"FX"};

using RefreshLineArbitration = openomd::LineArbitration<openomd::MapBasedCache, openomd::RefreshChannelRecoveryPolicy<openomd::MulticastReceiver>>;

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
                OmdPcapRunner<OmdcPrintProcessor<PcapLineArbitration>, OmdcParser> runner{ ChannelConfig::getChannelConfig(networkCfg), pcapFile, sll };
                run(runner);
            }
            else if (protocol == "omdd")
            {
                OmdPcapRunner<OmddPrintProcessor<NoopLineArbitration>, OmddParser> runner{ ChannelConfig::getChannelConfig(networkCfg), pcapFile, sll };
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
                OmdMulticastRunner<OmdcPrintProcessor<RefreshLineArbitration>, OmdcRefreshProcessor<CoutBaseProcessor>, OmdcParser> runner{ ChannelConfig::getChannelConfig(networkCfg) };
                run(runner);
            }
            else if (protocol == "omdd")
            {
                OmdMulticastRunner<OmddPrintProcessor<RefreshLineArbitration>, OmddRefreshProcessor<CoutBaseProcessor>, OmddParser> runner{ ChannelConfig::getChannelConfig(networkCfg)};
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
                OmdInstrumentDownload<OMDCInstrumentProcessor<OMDCTranslatePolicy, CoutBaseProcessor>, OmdcRefreshProcessor<CoutBaseProcessor>, OmdcParser> runner{ ChannelConfig::getChannelConfig(networkCfg), std::cout };
                run(runner);
            }
            else if (protocol == "omdd")
            {
                OmdInstrumentDownload<OMDDInstrumentProcessor<OMDDTranslatePolicy, CoutBaseProcessor>, OmddRefreshProcessor<CoutBaseProcessor>, OmddParser> runner{ ChannelConfig::getChannelConfig(networkCfg), std::cout };
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
