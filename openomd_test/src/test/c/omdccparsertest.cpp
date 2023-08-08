#include <gtest/gtest.h>
#include "openomd/omdccprocessor.h"
#include "openomd/nooplinearbitration.h"
#include "openomd/omdbaseprocessor.h"

namespace omdcc
{
template <typename _Processor>
void processMsg(char* msg, size_t size, int32_t msgCount = 1)
{
    _Processor processor;
    openomd::OmdccParser parser;
    parser.parse(msg, size, processor);
    EXPECT_EQ(msgCount, processor.msgCount());
}

class OMDCCP : public openomd::OMDCCProcessor<openomd::NoopLineArbitration, openomd::BaseProcessor>
{
public:
    int32_t msgCount() const
    {
        return _count;
    }
protected:
    int32_t _count = 0;
};

TEST(OMDCC_TEST, DisasterRecoverySignal)
{
    char msg[] = "\x18\x00\x01\x00\xe4\x01\x00\x00\x40\x1c\xe4\x8e\xff\xfd\x3c\x14" \
        "\x08\x00\x69\x00\x02\x00\x00\x00";

    struct Processor : public OMDCCP
    {
        using OMDCCP::OMDCCP;
        void onMessage(sbe::DisasterRecoverySignal const& dr, uint32_t)
        {
            EXPECT_EQ(2, dr.drStatus());
            _count++;
        }
        using OMDCCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDCC_TEST, SequenceReset)
{
    char msg[] = "\x18\x00\x01\x02\x01\x00\x00\x00\x80\x73\x01\x12\xc8\xf4\x12\x15" \
        "\x08\x00\x64\x00\x01\x00\x00\x00";
    struct Processor : public OMDCCP
    {
        using OMDCCP::OMDCCP;
        void onMessage(sbe::SequenceReset const& sr, uint32_t)
        {
            EXPECT_EQ(1, sr.newSeqNo());
            _count++;
        }
        using OMDCCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDCC_TEST, MarketSecurityDefinitionRefreshComplete)
{
    char msg[] =
        "\x1c\x01\x03\x98\x06\xfb" \
        "\x00\x00\x80\x09\x9b\x05\x8b\x7a\x77\x17\xdc\x00\x63\x02\x52\x94" \
        "\x04\x00\x41\x53\x5a\x52\x43\x4e\x45\x31\x30\x30\x30\x30\x30\x54" \
        "\x30\x38\x45\x51\x54\x59\x00\x00\x5a\x45\x4d\x49\x43\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x43\x4e\x59\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x2d" \
        "\x4e\x2a\x82\x35\x75\x4b\x6d\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x00\x00\x00\xd8" \
        "\xcc\x00\x00\x00\x59\x00\x00\x00\x00\x00\x00\xdb\xb6\x32\x01\x00" \
        "\x00\x00\x00\x00\x00\x00\x28\x00\x62\x02\x41\x53\x5a\x52\x58\x53" \
        "\x48\x45\x20\x53\x48\x45\x4e\x5a\x48\x45\x4e\x20\x53\x45\x47\x4d" \
        "\x45\x4e\x54\x00\x00\x00\x00\x43\x4e\x59\x5b\x00\x00\x00\x08\x00" \
        "\xcb\x00\x5c\x00\x00\x00";

    struct Processor : public OMDCCP
    {
        using OMDCCP::OMDCCP;
        void onMessage(sbe::SecurityDefinition& sd, uint32_t)
        {
            EXPECT_EQ(300114, sd.securityCode());
            auto marketCode = sd.getMarketCodeAsString();
            openomd::trim(marketCode);
            EXPECT_EQ("ASZR", marketCode);
            auto isin = sd.getIsinCodeAsString();
            openomd::trim(isin);
            EXPECT_EQ("CNE100000T08", isin);
            auto instType = sd.getInstrumentTypeAsString();
            openomd::trim(instType);
            EXPECT_EQ("EQTY", instType);
            auto shortName = sd.getSecurityShortNameAsString();
            openomd::trim(shortName);
            EXPECT_EQ("ZEMIC", shortName);
            auto currency = sd.getCurrencyCodeAsString();
            openomd::trim(currency);
            EXPECT_EQ("CNY", currency);
            EXPECT_EQ(100, sd.lotSize());
            EXPECT_EQ(52440, sd.previousClosingPrice());
            EXPECT_EQ(89, sd.shortSellFlag());
            EXPECT_EQ(20100827, sd.listingDate());
            _count++;
        }
        void onMessage(sbe::MarketDefinition const& md, uint32_t)
        {
            auto marketCode = md.getMarketCodeAsString();
            openomd::trim(marketCode);
            EXPECT_EQ("ASZR", marketCode);
            auto marketName = md.getMarketNameAsString();
            openomd::trim(marketName);
            EXPECT_EQ("XSHE SHENZHEN SEGMENT", marketName);
            auto currency = md.getCurrencyCodeAsString();
            openomd::trim(currency);
            EXPECT_EQ("CNY", currency);
            EXPECT_EQ(91, md.numberOfSecurities());
            _count++;
        }
        void onMessage(sbe::RefreshComplete const& rc, uint32_t)
        {
            EXPECT_EQ(92, rc.lastSeqNum());
            _count++;
        }
        using OMDCCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1, 3);
}
TEST(OMDCC_TEST, SecurityStatus)
{
    char msg[] = "\x2c\x00\x02\x01\x04\x7d" \
        "\x02\x00\x00\xad\xc3\xff\x8a\x7a\x77\x17\x14\x00\x6d\x02\xfc\x70" \
        "\x02\x00\x03\x00\x00\x00\x54\x30\x20\x20\x20\x20\x20\x20\x08\x00" \
        "\xcb\x00\x72\x67\x00\x00";

    struct Processor : public OMDCCP
    {
        using OMDCCP::OMDCCP;
        void onMessage(sbe::SecurityStatus const& ss, uint32_t)
        {
            EXPECT_EQ(159996, ss.securityCode());
            EXPECT_EQ(3, ss.securityTradingStatus());
            auto tradingPhase = ss.getTradingPhaseCodeAsString();
            openomd::trim(tradingPhase);
            EXPECT_EQ("T0", tradingPhase);
            _count++;
        }
        void onMessage(sbe::RefreshComplete const& rc, uint32_t)
        {
            EXPECT_EQ(26482, rc.lastSeqNum());
            _count++;
        }
        using OMDCCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1, 2);
}
TEST(OMDCC_TEST, Statistics)
{
    char msg[] = "\x44\x00\x01\x00\x74\x67" \
        "\x00\x00\x80\x1a\x99\xaf\x8b\x7a\x77\x17\x34\x00\x94\x02\xbb\x09" \
        "\x00\x00\x85\x0b\x00\x00\x00\x00\x00\x00\xf0\x3c\x13\x01\x00\x00" \
        "\x00\x00\x2e\x18\x00\x00\x5c\x17\x00\x00\xfc\x17\x00\x00\x2e\x18" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

    struct Processor : public OMDCCP
    {
        using OMDCCP::OMDCCP;
        void onMessage(sbe::Statistics const& s, uint32_t)
        {
            EXPECT_EQ(2491, s.securityCode());
            EXPECT_EQ(2949, s.sharesTraded());
            EXPECT_EQ(18038000, s.turnover());
            EXPECT_EQ(6190, s.highPrice());
            EXPECT_EQ(5980, s.lowPrice());
            EXPECT_EQ(6140, s.lastPrice());
            EXPECT_EQ(6190, s.openingPrice());
            _count++;
        }
        using OMDCCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDCC_TEST, TopOfBook)
{
    char msg[] = "\x38\x00\x01\x00\x73\x67" \
        "\x00\x00\x80\x1a\x99\xaf\x8b\x7a\x77\x17\x28\x00\x8f\x02\xbb\x09" \
        "\x00\x00\x85\x02\x00\x00\x00\x00\x00\x00\xa4\x00\x00\x00\x00\x00" \
        "\x00\x00\xfc\x17\x00\x00\x2e\x18\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00";

    struct Processor : public OMDCCP
    {
        using OMDCCP::OMDCCP;
        void onMessage(sbe::TopOfBook const& t, uint32_t)
        {
            EXPECT_EQ(2491, t.securityCode());
            EXPECT_EQ(645, t.aggregateBidQuantity());
            EXPECT_EQ(164, t.aggregateAskQuantity());
            EXPECT_EQ(6140, t.bidPrice());
            EXPECT_EQ(6190, t.askPrice());
            _count++;
        }
        using OMDCCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
}