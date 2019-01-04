#include <cstdio>
#include <gtest/gtest.h>
#include "openomd/omdcparser.h"
#include "openomd/omdtest.h"
#include "openomd/pcaputil.h"

namespace omdc
{
struct PrintProcessor : OMDCProcessor
{
    void onMessage(sbe::SequenceReset const& sr, int32_t)
    {
        _count++;
    }
    using OMDCProcessor::onMessage;
    int32_t _count = 0;
};

TEST(OMDCHandler, pcap)
{
    EXPECT_EQ(14, sizeof(openomd::EthernetHdr));
    EXPECT_EQ(34, sizeof(openomd::IpHdr));
    EXPECT_EQ(42, sizeof(openomd::UdpHdr));
    EXPECT_EQ(54, sizeof(openomd::TcpHdr));
    
    struct Callback
    {
        PrintProcessor _processor;
        openomd::OmdcParser _parser;

    public:
        void onReceive(int32_t byteRecvd, uint8_t* data, int32_t max, int32_t partition)
        {
            _parser.parse((char*)data, byteRecvd, _processor, 0);
        }
    };
    
    uint8_t pcapData[] = "\xa1\xb2\xc3\xd4\x00\x02\x00\x04\x00\x00\x00\x00\x00\x00\x00\x00"\
        "\x00\x00\xff\xff\x00\x00\x00\x01\x59\x01\x91\xed\x00\x0d\xe5\x65" \
        "\x00\x00\x00\x42\x00\x00\x00\x42\x01\x00\x5e\x01\x01\x79\xe8\x39" \
        "\x35\xeb\x97\xf2\x08\x00\x45\x00\x00\x34\x00\x00\x40\x00\x64\x11" \
        "\x13\xe6\x0a\x01\x08\x58\xef\x01\x01\x79\xbf\xda\xc7\x38\x00\x20" \
        "\xf2\x1b\x18\x00\x01\x0c\x01\x00\x00\x00\x80\x81\xf4\xda\xce\x2d" \
        "\xb9\x14\x08\x00\x64\x00\x01\x00\x00\x00\x59\x01\x91\xed\x00\x0d" \
        "\xe5\x7d\x00\x00\x00\x42\x00\x00\x00\x42\x01\x00\x5e\x01\x7f\x79" \
        "\xf4\xce\x46\xaa\x22\x7c\x08\x00\x45\x00\x00\x34\x00\x00\x40\x00" \
        "\x64\x11\x94\xe5\x0a\x01\x09\x58\xef\x01\x7f\x79\xbb\xc0\xc7\x38" \
        "\x00\x20\x77\x35\x18\x00\x01\x0c\x01\x00\x00\x00\x80\x81\xf4\xda" \
        "\xce\x2d\xb9\x14\x08\x00\x64\x00\x01\x00\x00\x00\x0a";

    char tmpFilename[64];
    tmpnam_s(tmpFilename, sizeof(tmpFilename));
    FILE* pcapFile;
    fopen_s(&pcapFile, tmpFilename, "wb+");

    Callback callback;
    try
    {
        fwrite(pcapData, sizeof(pcapData), 1, pcapFile);
        fflush(pcapFile);
        fclose(pcapFile);
        openomd::PcapUtil<Callback> pcapUtil{ tmpFilename, callback};
        pcapUtil.init();
        pcapUtil.start();
        pcapUtil.run();
        pcapUtil.stop();
    }
    catch (std::exception const& ex)
    {
        printf("exception %s\n", ex.what());
    }
    remove(tmpFilename);

    EXPECT_EQ(2, callback._processor._count);
}
}