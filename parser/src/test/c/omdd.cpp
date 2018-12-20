#include <gtest/gtest.h>
#include "openomd/omddparser.h"

namespace omdd
{
namespace sbe
{
class OMDDProcessor
{
#define ONMESSAGE(_MSG) virtual void onMessage(_MSG const&, int32_t){}

public:
    ONMESSAGE(AddOrder)
    ONMESSAGE(AggregateOrderBookUpdate)
    ONMESSAGE(CalculatedOpeningPrice)
    ONMESSAGE(ClassDefinition)
    ONMESSAGE(CombinationDefinition)
    ONMESSAGE(CommodityDefinition)
    ONMESSAGE(CommodityStatus)
    ONMESSAGE(DeleteOrder)
    ONMESSAGE(DisasterRecoverySignal)
    ONMESSAGE(EstimatedAverageSettlementPrice)
    ONMESSAGE(ImpliedVolatility)
    ONMESSAGE(LogonResponse)
    ONMESSAGE(MarketAlert)
    ONMESSAGE(ModifyOrder)
    ONMESSAGE(OpenInterest)
    ONMESSAGE(OrderbookClear)
    ONMESSAGE(QuoteRequest)
    ONMESSAGE(RefreshComplete)
    ONMESSAGE(RetransmissionResponse)
    ONMESSAGE(SequenceReset)
    ONMESSAGE(SeriesDefinitionBase)
    ONMESSAGE(SeriesDefinitionExtended)
    ONMESSAGE(SeriesStatistics)
    ONMESSAGE(SeriesStatus)
    ONMESSAGE(Trade)
    ONMESSAGE(TradeAmendment)
    ONMESSAGE(TradeStatistics)
    void onUnknownMessage(uint16_t, uint16_t)
    {
    }
    void onError(std::exception const& ex)
    {
        printf("OMDDProcessor error %s\n", ex.what());
    }
};

template <typename _Processor>
void processMsg(char* msg, size_t size)
{
    _Processor processor;
    openomd::OmddParser parser;
    parser.parse(msg, size, processor, 0);
}

//struct Processor : public OMDDProcessor
//{
//    void onMessage(, int32_t)
//    {
//    }
//    using OMDDProcessor::onMessage;
//};
//processMsg<Processor>(msg, sizeof(msg) - 1);

TEST(OMDD_TEST, SequenceReset)
{
    char msg[] = "\x18\x00\x01\x01\x01\x00\x00\x00\x00\xae\x43\x78\xa6\x3f\x69\x14" \
        "\x08\x00\x64\x00\x01\x00\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::SequenceReset const& sr, int32_t)
        {
            EXPECT_EQ(1, sr.newSeqNo());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDD_TEST, RefreshComplete)
{
    char msg[] = "\x18\x00\x01\x0b\x01\x00\x00\x00\x00\x84\xdc\x89\xad\x3f\x69\x14" \
        "\x08\x00\xcb\x00\x00\x00\x00\x00";
    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::RefreshComplete const& rc, int32_t)
        {
            EXPECT_EQ(0, rc.lastSeqNum());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDD_TEST, CommodityDefinition)
{
    char msg[] = "\x90\x05\x10\x0b\xce\x28\x03\x00\x00\x1c\xeb\x50\x06\x42\x69\x14" \
        "\x58\x00\x2d\x01\x0c\x10\x02\x00\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x48\x4b\x44\x01\x48\x4b\x47\x20\x43\x41\x50\x2e" \
        "\x20\x41\x44\x4a\x2e\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x30\x30\x30\x30\x33\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x01\x00\x00\x00\x58\x00\x2d\x01\x0d\x10";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::CommodityDefinition const& comm, int32_t)
        {
            EXPECT_EQ(4127, comm.commodityCode());
            EXPECT_EQ(2, comm.decimalInUnderlyingPrice());
            EXPECT_EQ("            ", comm.getIsinCodeAsString());
            EXPECT_EQ("HKD", comm.baseCurrency());
            EXPECT_EQ(1, comm.underlyingPriceUnit());
            EXPECT_EQ("GWM CAP. ADJ.                   ", comm.getCommodityNameAsString());
            EXPECT_EQ(0, comm.nominalValue());
            EXPECT_EQ("02333               ", comm.getUnderlyingCodeAsString());
            EXPECT_EQ(1, comm.underlyingType());
            EXPECT_EQ(0, comm.effectiveTomorrow());
            EXPECT_EQ("       ", comm.commodityID());
        }
        using OMDDProcessor::onMessage;
    };
    //processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDD_TEST, ClassDefinition)
{

}

TEST(OMDD_TEST, SeriesDefinitionBase)
{
    char msg[] = "\xb0\x05\x18\x00\x68\x00\x00\x00\x80\xdf\xd9\x83\xb2\x3f\x69\x14" \
        "\x3c\x00\x2f\x01\x5f\x09\x03\x00\x58\x49\x43\x32\x2e\x35\x30\x46" \
        "\x37\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x01\x03\x00\x00\xfa\x00\x00\x00" \
        "\x32\x30\x31\x37\x30\x36\x32\x39\x03\x00\x01\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::SeriesDefinitionBase const& sdb, int32_t)
        {
            EXPECT_EQ(199007, sdb.orderbookID());
            EXPECT_EQ("XIC2.50F7                       ", sdb.getSymbolAsString());
            EXPECT_EQ(1, sdb.financialProduct());
            EXPECT_EQ(3, sdb.numberOfDecimalsPrice());
            EXPECT_EQ(0, sdb.numberOfLegs());
            EXPECT_EQ(250, sdb.strikePrice());
            EXPECT_EQ("20170629", sdb.getExpirationDateAsString());
            EXPECT_EQ(1, sdb.putOrCall());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDD_TEST, SeriesDefinitionExtended)
{

}

TEST(OMDD_TEST, CombinationDefinition)
{

}

TEST(OMDD_TEST, MarketStatus)
{

}

TEST(OMDD_TEST, SeriesStatus)
{

}

TEST(OMDD_TEST, CommodityStatus)
{

}

}
}