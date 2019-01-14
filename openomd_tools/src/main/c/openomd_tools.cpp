#include <iostream>
#include "cxxopts.hpp"
#include "omdprintprocessor.h"

int main(int32_t argc, char* argv[])
{
    using namespace std;
    cxxopts::Options options("openomd_tools", "Openomd Tools");
    options.add_options()
        ("f,function", "pcapdump,udpdump", cxxopts::value<string>())
        ("p,protocol", "omdc,omdd", cxxopts::value<string>())
        ("c,pcap", "Pcap file", cxxopts::value<string>())
        ("i,ip", "IP address", cxxopts::value<string>())
        ("t,port", "Ports", cxxopts::value<uint16_t>());
    try
    {
        auto result = options.parse(argc, argv);
        auto function = result["f"].as<string>();
        if (function == "pcapdump")
        {
            if (result.count("p") == 0 || result.count("c") == 0)
            {
                cerr << options.help();
                return -1;
            }
            auto protocol = result["p"].as<string>();
            auto pcapFile = result["c"].as<string>();
            cout << "function=" << function << " p=" << protocol << " pcap=" << pcapFile << " " << endl;
            if (protocol == "omdc")
            {
                set<int32_t> config{ 0 };
                openomd::OmdcPrintProcessor processor{ config };
                openomd::OmdPcapRunner<openomd::OmdcPrintProcessor, openomd::OmdcParser> runner;
                runner.run(pcapFile, processor);
            }
            else if (protocol == "omdd")
            {
                set<int32_t> config{ 0 };
                openomd::OmddPrintProcessor processor{ config };
                openomd::OmdPcapRunner<openomd::OmddPrintProcessor, openomd::OmddParser> runner;
                runner.run(pcapFile, processor);
            }

        }
        else if (function == "udpdump")
        {

        }
        else
        {
            cerr << options.help();
            return -1;
        }
    }
    catch (exception const& ex)
    {
        cerr << ex.what();
        cerr << options.help();
        return -1;
    }
}
