#include <gtest/gtest.h>
#if defined(__linux__)
#include <codecvt>
#endif
#include "openomd/omdtest.h"

namespace omdd
{
template <typename _Processor>
void processMsg(char* msg, size_t size)
{
    _Processor processor;
    openomd::OmddParser parser;
    parser.parse(msg, size, processor);
}

TEST(OMDD_TEST, SequenceReset)
{
    char msg[] = "\x18\x00\x01\x01\x01\x00\x00\x00\x00\xae\x43\x78\xa6\x3f\x69\x14" \
        "\x08\x00\x64\x00\x01\x00\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::SequenceReset const& sr, uint32_t)
        {
            EXPECT_EQ(1, sr.newSeqNo());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, DisasterRecoverySignal)
{
    char msg[] = "\x18\x00\x01\x00\x6e\x02\x00\x00\x80\x7f\x5e\x0a\xfd\x68\x6d\x14" \
        "\x08\x00\x69\x00\x02\x00\x00\x00";
    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::DisasterRecoverySignal const& dr, uint32_t)
        {
            EXPECT_EQ(2, dr.drStatus());
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
        void onMessage(sbe::RefreshComplete const& rc, uint32_t)
        {
            EXPECT_EQ(0, rc.lastSeqNum());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, CommodityDefinition)
{
    char msg[] = "\x92\x05\x0f\xe1\xab\x09\x00\x00\x40\xbc\x55\x98\x90\xc3\xf2\x14" \
        "\x5e\x00\x2d\x01\xd6\x07\x02\x00\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x48\x4b\x44\x01\x50\x4f\x57\x45\x52\x20\x41\x53" \
        "\x53\x45\x54\x53\x20\x48\x4f\x4c\x44\x49\x4e\x47\x53\x20\x4c\x49" \
        "\x4d\x49\x54\x45\x44\x20\x20\x20\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x30\x30\x30\x30\x36\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x01\x00\x48\x45\x48\x20\x20\x20\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::CommodityDefinition const& comm, uint32_t)
        {
            EXPECT_EQ(2006, comm.commodityCode());
            EXPECT_EQ(2, comm.decimalInUnderlyingPrice());
            EXPECT_EQ("            ", comm.getIsinCodeAsString());
            EXPECT_EQ("HKD", comm.getBaseCurrencyAsString());
            EXPECT_EQ(1, comm.underlyingPriceUnit());
            EXPECT_EQ("POWER ASSETS HOLDINGS LIMITED   ", comm.getCommodityNameAsString());
            EXPECT_EQ(0, comm.nominalValue());
            EXPECT_EQ("00006               ", comm.getUnderlyingCodeAsString());
            EXPECT_EQ(1, comm.underlyingType());
            EXPECT_EQ(0, comm.effectiveTomorrow());
            EXPECT_EQ("HEH   ", comm.getCommodityIDAsString());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, ClassDefinition)
{
    char msg[] = "\x98\x05\x0c\xe1\x77\x0a\x00\x00\xc0\xf9\x22\xa4\x90\xc3\xf2\x14" \
        "\x76\x00\x2e\x01\x0c\x14\x06\x00\x55\x04\x00\x00\xd0\x07\x00\x00" \
        "\xd0\x07\x00\x00\x02\x00\x00\x00\x02\x00\x01\x00\x01\x01\x48\x4b" \
        "\x44\x43\x52\x4c\x43\x41\x4c\x4c\x20\x20\x20\x20\x20\x20\x20\x43" \
        "\x52\x4c\x20\x2d\x20\x43\x41\x4c\x4c\x20\x4f\x50\x54\x49\x4f\x4e" \
        "\x53\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x4e" \
        "\x48\x4b\x44\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x00\x01\x00\x00\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::ClassDefinition const& cdef, uint32_t)
        {
            EXPECT_EQ(12, cdef.country());
            EXPECT_EQ(20, cdef.market());
            EXPECT_EQ(6, cdef.instrumentGroup());
            EXPECT_EQ(0, cdef.modifier());
            EXPECT_EQ(1109, cdef.commodityCode());
            EXPECT_EQ(2000, cdef.priceQuotationFactor());
            EXPECT_EQ(2, cdef.decimalInStrikePrice());
            EXPECT_EQ(0, cdef.decimalInContractSize());
            EXPECT_EQ(2, cdef.decimalInPremium());
            EXPECT_EQ(1, cdef.rankingType());
            EXPECT_EQ(1, cdef.tradable());
            EXPECT_EQ(1, cdef.premiumUnit4Price());
            EXPECT_EQ("HKD", cdef.getBaseCurrencyAsString());
            EXPECT_EQ("CRLCALL       ", cdef.getInstrumentClassIDAsString());
            EXPECT_EQ("CRL - CALL OPTIONS              ", cdef.getInstrumentClassNameAsString());
            EXPECT_EQ('N', cdef.isFractions());
            EXPECT_EQ("HKD                             ", cdef.getSettlementCurrencyIDAsString());
            EXPECT_EQ(0, cdef.effectiveTomorrow());
            EXPECT_EQ(1, cdef.tickStepSize());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, SeriesDefinitionBase)
{
    char msg[] = "\xb0\x05\x18\x00\xc7\x24\x26\x00\x80\xdf\xe3\x86\xe9\x11\x5c\x15" \
        "\x3c\x00\x2f\x01\x35\x10\xd5\x00\x48\x45\x42\x37\x33\x2e\x31\x34" \
        "\x4f\x39\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x01\x02\x00\x00\x92\x1c\x00\x00" \
        "\x32\x30\x31\x39\x30\x33\x32\x38\x02\x00\x02\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::SeriesDefinitionBase const& sdb, uint32_t)
        {
            EXPECT_EQ(13963317, sdb.orderbookID());
            EXPECT_EQ("HEB73.14O9                      ", sdb.getSymbolAsString());
            EXPECT_EQ(1, sdb.financialProduct());
            EXPECT_EQ(2, sdb.numberOfDecimalsPrice());
            EXPECT_EQ(0, sdb.numberOfLegs());
            EXPECT_EQ(7314, sdb.strikePrice());
            EXPECT_EQ("20190328", sdb.getExpirationDateAsString());
            EXPECT_EQ(2, sdb.decimalInStrikePrice());
            EXPECT_EQ(2, sdb.putOrCall());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, SeriesDefinitionExtended)
{
    char msg[] = "\x58\x05\x0d\x00\xb3\xf0\x26\x00\x80\xdf\xe3\x86\xe9\x11\x5c\x15" \
        "\x68\x00\x30\x01\xa8\x0a\xa6\x00\x43\x54\x43\x34\x2e\x30\x30\x4a" \
        "\x38\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x0c\x14\x06\x00\xa8\x0a\x5e\x3b" \
        "\x90\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x01\x00\x00\x00\x00\x00\x00\x00" \
        "\x32\x30\x31\x38\x31\x30\x33\x30\x00\x00\x3b\x4f\x04\x54\x62\x15" \
        "\x00\x00\x00\x00\x00\x00\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::SeriesDefinitionExtended const& sde, uint32_t)
        {
            EXPECT_EQ(10881704, sde.orderbookID());
            EXPECT_EQ("CTC4.00J8                       ", sde.getSymbolAsString());
            EXPECT_EQ(12, sde.country());
            EXPECT_EQ(20, sde.market());
            EXPECT_EQ(6, sde.instrumentGroup());
            EXPECT_EQ(0, sde.modifier());
            EXPECT_EQ(2728, sde.commodityCode());
            EXPECT_EQ(15198, sde.expirationDate());
            EXPECT_EQ(400, sde.strikePrice());
            EXPECT_EQ(0, sde.contractSize());
            EXPECT_EQ("            ", sde.getIsinCodeAsString());
            EXPECT_EQ(1, sde.seriesStatus());
            EXPECT_EQ(0, sde.effectiveTomorrow());
            EXPECT_EQ(0, sde.priceQuotationFactor());
            EXPECT_EQ(0, sde.priceMethod());
            EXPECT_EQ("20181030", sde.getEffectiveExpDateAsString());
            EXPECT_EQ(1540886400000000000, sde.dateTimeLastTrading());
            EXPECT_EQ(0, sde.dateTimeFirstTrading());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, CombinationDefinition)
{
    char msg[] = "\xb0\x05\x48\xe1\x05\xec\x06\x00\x00\x31\x6f\xfb\xdd\xce\xf2\x14" \
        "\x14\x00\x31\x01\xed\x13\x52\x00\xed\x13\x0b\x00\x00\x00\x00\x42" \
        "\x01\x00\x00\x00";
    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::CombinationDefinition const& cd, uint32_t)
        {
            EXPECT_EQ(5379053, cd.comboOrderbookID());
            EXPECT_EQ(725997, cd.legOrderbookID());
            EXPECT_EQ(66, cd.legSide());
            EXPECT_EQ(1, cd.legRatio());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, MarketStatus)
{
    char msg[] = "\xc0\x05\x1c\xe1\xd5\xde\x0a\x00\x40\x0e\x92\xc6\x53\xd5\xf2\x14" \
        "\x34\x00\x40\x01\x01\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x00\x00\x02\x00" \
        "\x73\x00\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::MarketStatus const& ms, uint32_t)
        {
            EXPECT_EQ(1, ms.stateLevel());
            EXPECT_EQ(3, ms.market());
            EXPECT_EQ(0, ms.instrument());
            EXPECT_EQ(0, ms.orderbookID());
            EXPECT_EQ(0, ms.commodityCode());
            EXPECT_EQ("        ", ms.actualStartDate());
            EXPECT_EQ("      ", ms.actualStartTime());
            EXPECT_EQ("        ", ms.plannedStartDate());
            EXPECT_EQ("      ", ms.plannedStartTime());
            EXPECT_EQ(0, ms.secondsToStateChange());
            EXPECT_EQ(2, ms.state());
            EXPECT_EQ(115, ms.priority());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, SeriesStatus)
{
    char msg[] = "\xbc\x05\x79\x00\x91\x4e\x26\x00\x40\x94\x97\x86\xe9\x11\x5c\x15" \
        "\x0c\x00\x41\x01\xd6\x07\x2e\x01\x02\x01\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::SeriesStatus const& ss, uint32_t)
        {
            EXPECT_EQ(19793878, ss.orderbookID());
            EXPECT_EQ(2, ss.suspensionIndicator());
            EXPECT_EQ(1, ss.seriesStatus());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, CommodityStatus)
{
    char msg[] = "\x18\x00\x01\xb9\x0f\x1c\x00\x00\x80\xa4\x71\x0f\xff\x2a\x5c\x15" \
        "\x08\x00\x42\x01\x88\x14\x59\x01";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::CommodityStatus const& cs, uint32_t)
        {
            EXPECT_EQ(5256, cs.commodityCode());
            EXPECT_EQ('Y', cs.suspended());
            EXPECT_EQ(1, cs.locked());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, AddOrder)
{
    char msg[] = "\x30\x00\x01\xc8\x9b\xc2\x00\x00\xc0\xd5\xca\x46\x67\xe4\xf2\x14" \
        "\x20\x00\x4a\x01\xa4\x0f\x27\x00\xaf\x96\x02\x00\xc1\x4b\xf8\x5f" \
        "\x20\x4e\x00\x00\x01\x00\x00\x00\x00\x02\x00\x00\x01\x00\x00\x00";
    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::AddOrder const& ao, uint32_t)
        {
            EXPECT_EQ(2559908, ao.orderbookID());
            EXPECT_EQ(6915360520128337583, ao.orderID());
            EXPECT_EQ(20000, ao.price());
            EXPECT_EQ(1, ao.quantity());
            EXPECT_EQ(0, ao.side());
            EXPECT_EQ(2, ao.lotType());
            EXPECT_EQ(0, ao.orderType());
            EXPECT_EQ(1, ao.orderBookPosition());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, ModifyOrder)
{
    // handcraft
    char msg[] = "\x30\x00\x01\xc8\x9b\xc2\x00\x00\xc0\xd5\xca\x46\x67\xe4\xf2\x14" \
        "\x20\x00\x4b\x01\xa4\x0f\x27\x00\xaf\x96\x02\x00\xc1\x4b\xf8\x5f" \
        "\x20\x4e\x00\x00\x01\x00\x00\x00\x00\x02\x00\x00\x01\x00\x00\x00";
    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::ModifyOrder const& mo, uint32_t)
        {
            EXPECT_EQ(2559908, mo.orderbookID());
            EXPECT_EQ(6915360520128337583, mo.orderID());
            EXPECT_EQ(20000, mo.price());
            EXPECT_EQ(1, mo.quantity());
            EXPECT_EQ(0, mo.side());
            EXPECT_EQ(0, mo.orderType());
            EXPECT_EQ(1, mo.orderBookPosition());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, DeleteOrder)
{
    char msg[] = "\x74\x00\x04\x00\x44\xfe\x27\x00\x80\xe8\xf1\x53\x9d\x4f\x69\x14" \
        "\x12\x00\x4c\x01\x0e\x09\x9c\x01\x71\xb8\x0c\x00\x41\x3e\x82\x5d" \
        "\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::DeleteOrder const& dl, uint32_t)
        {
            EXPECT_EQ(27003150, dl.orderbookID());
            EXPECT_EQ(6738016441394313329, dl.orderID());
            EXPECT_EQ(0, dl.side());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);

}
TEST(OMDD_TEST, AggregateOrderBookUpdate)
{
    char msg[] = "\x24\x01\x01\xc8\xfa\x00\x00\x00\x40\xeb\x2b\x96\x53\xd5\xf2\x14" \
        "\x14\x01\x61\x01\xd5\x07\xc5\x01\x49\xb7\x64\x0b" \
        "\x0a\x00\x00\x00\x00\x00\x00\x00\x64\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00" \
        "\x0a\x00\x00\x00\x00\x00\x00\x00\x63\x00\x00\x00\x01\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00" \
        "\x0a\x00\x00\x00\x00\x00\x00\x00\x62\x00\x00\x00\x01\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00" \
        "\x0a\x00\x00\x00\x00\x00\x00\x00\x61\x00\x00\x00\x01\x00\x00\x00\x00\x00\x04\x00\x00\x00\x00\x00" \
        "\x0a\x00\x00\x00\x00\x00\x00\x00\x60\x00\x00\x00\x01\x00\x00\x00\x00\x00\x05\x00\x00\x00\x00\x00" \
        "\x0a\x00\x00\x00\x00\x00\x00\x00\x5f\x00\x00\x00\x01\x00\x00\x00\x00\x00\x06\x00\x00\x00\x00\x00" \
        "\x0a\x00\x00\x00\x00\x00\x00\x00\x5e\x00\x00\x00\x01\x00\x00\x00\x00\x00\x07\x00\x00\x00\x00\x00" \
        "\x0a\x00\x00\x00\x00\x00\x00\x00\x5d\x00\x00\x00\x01\x00\x00\x00\x00\x00\x08\x00\x00\x00\x00\x00" \
        "\x0a\x00\x00\x00\x00\x00\x00\x00\x5c\x00\x00\x00\x01\x00\x00\x00\x00\x00\x09\x00\x00\x00\x00\x00" \
        "\x0a\x00\x00\x00\x00\x00\x00\x00\x5b\x00\x00\x00\x01\x00\x00\x00\x00\x00\x0a\x00\x00\x00\x00\x00" \
        "\x14\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x02\x00\x00\x00\x00\x00\xff\x00\x00\x00\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::AggregateOrderBookUpdate& aob, uint32_t)
        {
            EXPECT_EQ(29689813, aob.orderbookID());
            auto& entries = aob.noEntries();
            EXPECT_EQ(11, entries.count());
            entries.next();
            EXPECT_EQ(10, entries.aggregateQuantity());
            EXPECT_EQ(100, entries.price());
            EXPECT_EQ(1, entries.numberOfOrders());
            EXPECT_EQ(0, entries.side());
            EXPECT_EQ(1, entries.priceLevel());
            EXPECT_EQ(0, entries.updateAction());
            entries.next();
            EXPECT_EQ(10, entries.aggregateQuantity());
            EXPECT_EQ(99, entries.price());
            EXPECT_EQ(1, entries.numberOfOrders());
            EXPECT_EQ(0, entries.side());
            EXPECT_EQ(2, entries.priceLevel());
            EXPECT_EQ(0, entries.updateAction());
            while (entries.hasNext())
            {
                entries.next();
            }
            EXPECT_EQ(20, entries.aggregateQuantity());
            EXPECT_EQ(SBE_NULLVALUE_INT32, entries.price());
            EXPECT_EQ(2, entries.numberOfOrders());
            EXPECT_EQ(0, entries.side());
            EXPECT_EQ(255, entries.priceLevel());
            EXPECT_EQ(0, entries.updateAction());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);

}
TEST(OMDD_TEST, OrderbookClear)
{
    // handcraft
    char msg[] = "\x74\x00\x04\x00\x44\xfe\x27\x00\x80\xe8\xf1\x53\x9d\x4f\x69\x14" \
        "\x08\x00\x4f\x01\x0e\x09\x9c\x01";
    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::OrderbookClear const& obc, uint32_t)
        {
            EXPECT_EQ(27003150, obc.orderbookID());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, QuoteRequest)
{
    char msg[] = "\x20\x00\x01\x00\x5d\x17\x00\x00\x00\x88\xc7\x54\x9d\x4f\x69\x14" \
        "\x10\x00\x50\x01\x44\x0a\x56\x01\x00\x00\x00\x00\x02\x00\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onmessage(sbe::QuoteRequest const& qr, uint32_t)
        {
            EXPECT_EQ(22415940, qr.orderbookID());
            EXPECT_EQ(0, qr.numberOfLots());
            EXPECT_EQ(2, qr.bidAskFlag());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, Trade)
{
    char msg[] = "\x48\x00\x01\x00\xb1\x97\x00\x00\x40\xf1\x35\x94\x79\x7b\x69\x14" \
        "\x38\x00\x5e\x01\xa4\x0f\x04\x00\x17\x55\x66\x00\x41\x3e\x82\x5d" \
        "\x80\x57\x00\x00\x63\xc6\x00\x00\x01\xd3\x59\x09\x00\x00\x00\x00" \
        "\x03\x01\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\xaf\x26\x94\x79\x7b\x69\x14";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::Trade const& t, uint32_t)
        {
            EXPECT_EQ(266148, t.orderbookID());
            EXPECT_EQ(6738016441400186135, t.orderID());
            EXPECT_EQ(22400, t.price());
            EXPECT_EQ(673801620517078627, t.tradeID());
            EXPECT_EQ(0, t.comboGroupID());
            EXPECT_EQ(3, t.side());
            EXPECT_EQ(1, t.dealType());
            EXPECT_EQ(0, t.tradeCondition());
            EXPECT_EQ(0, t.dealInfo());
            EXPECT_EQ(1, t.quantity());
            EXPECT_EQ(1470842515420000000, t.tradeTime());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, TradeAmendment)
{
    // handcraft
    char msg[] = "\x48\x00\x01\x00\xb1\x97\x00\x00\x40\xf1\x35\x94\x79\x7b\x69\x14" \
        "\x28\x00\x64\x01\x63\xc6\x00\x00\x01\xd3\x59\x09\x00\x00\x00\x00" \
        "\x80\x57\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\xaf\x26\x94" \
        "\x79\x7b\x69\x14\x01\x00\x00\x00";
    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::TradeAmendment const& ta, uint32_t)
        {
            EXPECT_EQ(673801620517078627, ta.tradeID());
            EXPECT_EQ(0, ta.comboGroupID());
            EXPECT_EQ(22400, ta.price());
            EXPECT_EQ(1, ta.quantity());
            EXPECT_EQ(1470842515420000000, ta.tradeTime());
            EXPECT_EQ(1, ta.tradeState());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, TradeStatistics)
{
    char msg[] = "\xb0\x05\x18\xe1\xe3\x54\x63\x00\x80\xef\xf3\xac\x3f\xda\xf2\x14" \
        "\x3c\x00\x68\x01\x18\x09\x23\x01\x00\x00\x00\x80\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x80" \
        "\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::TradeStatistics const& ts, uint32_t)
        {
            EXPECT_EQ(19073304, ts.orderbookID());
            EXPECT_EQ(INT_MIN, ts.price());
            EXPECT_EQ(0, ts.dealSource());
            EXPECT_EQ(0, ts.session());
            EXPECT_EQ(0, ts.aggregateQuantity());
            EXPECT_EQ(INT_MIN, ts.open());
            EXPECT_EQ(INT_MIN, ts.high());
            EXPECT_EQ(INT_MIN, ts.low());
            EXPECT_EQ(0, ts.tradeReportVolume());
            EXPECT_EQ(0, ts.dealCount());
            EXPECT_EQ(0, ts.turnover());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, SeriesStatistics)
{
    char msg[] = "\x40\x00\x01\xe1\x76\x9e\x0a\x00\x00\xd5\xbf\xc6\x53\xd5\xf2\x14" \
        "\x30\x00\x6b\x01\x12\x08\x0e\x01\x00\x00\x00\x00\x00\x00\x00\x80" \
        "\x00\x00\x00\x80\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::SeriesStatistics const& ss, uint32_t)
        {
            EXPECT_EQ(17696786, ss.orderbookID());
            EXPECT_EQ(0, ss.session());
            EXPECT_EQ(INT_MIN, ss.open());
            EXPECT_EQ(INT_MIN, ss.high());
            EXPECT_EQ(INT_MIN, ss.low());
            EXPECT_EQ(0, ss.tradeReportVolume());
            EXPECT_EQ(0, ss.dealCount());
            EXPECT_EQ(INT_MIN, ss.price());
            EXPECT_EQ(0, ss.turnover());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, CalculatedOpeningPrice)
{
    char msg[] = "\xb0\x05\x3c\xe1\x96\x1c\x00\x00\x80\x3e\x27\xc6\x53\xd5\xf2\x14" \
        "\x18\x00\x6c\x01\xa1\x0f\x02\x00\x00\x00\x00\x80\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00";
    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::CalculatedOpeningPrice const& cop, uint32_t)
        {
            EXPECT_EQ(135073, cop.orderbookID());
            EXPECT_EQ(INT_MIN, cop.calculatedOpeningPrice());
            EXPECT_EQ(0, cop.quantity());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
TEST(OMDD_TEST, EstimatedAverageSettlementPrice)
{
    char msg[] = "\x34\x00\x01\xc8\x7a\x42\x00\x00\x00\xad\x13\x3f\x78\xe4\xf2\x14" \
        "\x24\x00\x6d\x01\x45\x31\x32\x31\x31\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x23\x0d\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00";
    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::EstimatedAverageSettlementPrice const& eas, uint32_t)
        {
            EXPECT_EQ(69, eas.easType());
            EXPECT_EQ("1211                ", eas.getInstrumentCodeAsString());
            EXPECT_EQ(3363, eas.eas());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);

}
TEST(OMDD_TEST, MarketAlert)
{
    char msg[] = "\x1c\x05\x01\xe1\x63\x01" \
        "\x00\x00\x80\x50\xa1\xc6\x53\xd5\xf2\x14\x0c\x05\x43\x01\x01\x00" \
        "\x48\x00\x53\x00\x74\x00\x61\x00\x72\x00\x74\x00\x20\x00\x6f\x00" \
        "\x66\x00\x20\x00\x56\x00\x6f\x00\x6c\x00\x61\x00\x74\x00\x69\x00" \
        "\x6c\x00\x69\x00\x74\x00\x79\x00\x20\x00\x43\x00\x6f\x00\x6e\x00" \
        "\x74\x00\x72\x00\x6f\x00\x6c\x00\x20\x00\x4d\x00\x65\x00\x63\x00" \
        "\x68\x00\x61\x00\x6e\x00\x69\x00\x73\x00\x6d\x00\x20\x00\x63\x00" \
        "\x6f\x00\x6f\x00\x6c\x00\x2d\x00\x6f\x00\x66\x00\x66\x00\x20\x00" \
        "\x70\x00\x65\x00\x72\x00\x69\x00\x6f\x00\x64\x00\x3a\x00\x20\x00" \
        "\x5b\x00\x48\x00\x53\x00\x49\x00\x51\x00\x37\x00\x5d\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x4e\x02\x04\x03\x54\x00\x72\x00\x69\x00\x67\x00\x67\x00" \
        "\x65\x00\x72\x00\x20\x00\x74\x00\x69\x00\x6d\x00\x65\x00\x3a\x00" \
        "\x20\x00\x5b\x00\x32\x00\x30\x00\x31\x00\x37\x00\x31\x00\x31\x00" \
        "\x30\x00\x31\x00\x20\x00\x30\x00\x39\x00\x3a\x00\x33\x00\x39\x00" \
        "\x3a\x00\x32\x00\x34\x00\x5d\x00\x2c\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x52\x00\x65\x00\x66\x00\x65\x00\x72\x00" \
        "\x65\x00\x6e\x00\x63\x00\x65\x00\x20\x00\x70\x00\x72\x00\x69\x00" \
        "\x63\x00\x65\x00\x3a\x00\x20\x00\x5b\x00\x32\x00\x30\x00\x30\x00" \
        "\x30\x00\x30\x00\x5d\x00\x2c\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x55\x00\x70\x00\x70\x00\x65\x00\x72\x00" \
        "\x20\x00\x70\x00\x72\x00\x69\x00\x63\x00\x65\x00\x20\x00\x6c\x00" \
        "\x69\x00\x6d\x00\x69\x00\x74\x00\x3a\x00\x20\x00\x5b\x00\x32\x00" \
        "\x31\x00\x30\x00\x30\x00\x30\x00\x5d\x00\x2c\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::MarketAlert& ma, uint32_t)
        {
            EXPECT_EQ(1, ma.alertID());
            EXPECT_EQ(72, ma.source());
#if defined(__linux__)
            std::u16string headeru16(reinterpret_cast<const char16_t*>(ma.header()));
            std::string header = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(headeru16);
            EXPECT_EQ("Start of Volatility Control Mechanism cool-off period: [HSIQ7]", header);
#else
            std::wstring header(reinterpret_cast<const wchar_t*>(ma.header()));
            EXPECT_EQ(L"Start of Volatility Control Mechanism cool-off period: [HSIQ7]", header);
#endif
            EXPECT_EQ('N', ma.lastFragment());
            EXPECT_EQ(2, ma.infoType());
            EXPECT_EQ(4, ma.priority());
            auto &lines = ma.noLines();
            EXPECT_EQ(3, lines.count());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);

}
TEST(OMDD_TEST, OpenInterest)
{
    char msg[] = "\xb0\x05\x24\xa8\x9c\x3b\x45\x00\x00\x76\x4d\x54\x9d\x4f\x69\x14" \
        "\x28\x00\x6e\x01\x01\x00\x00\x00\x00\x00\x00\x00\x0c\x0b\x02\x01" \
        "\x01\x00\x00\x00\x00\x00\x00\x00\x1e\x00\x00\x00\x1e\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::OpenInterest const& oi, uint32_t)
        {
            EXPECT_EQ(1, oi.dayIndicator());
            EXPECT_EQ(16911116, oi.orderbookID());
            EXPECT_EQ(1, oi.settlement());
            EXPECT_EQ(0, oi.dealCount());
            EXPECT_EQ(30, oi.grossOI());
            EXPECT_EQ(30, oi.netOI());
            EXPECT_EQ(0, oi.turnover());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);

}
TEST(OMDD_TEST, ImpliedVolatility)
{
    char msg[] = "\xbc\x05\x79\xa8\xe5\xec\x34\x00\x00\x00\xe1\x39\x20\x74\x69\x14" \
        "\x0c\x00\x6f\x01\x7d\x0b\x2f\x02\x70\x82\x03\x00";

    struct Processor : public OMDDProcessor
    {
        void onMessage(sbe::ImpliedVolatility const& iv, uint32_t)
        {
            EXPECT_EQ(36637565, iv.orderbookID());
            EXPECT_EQ(230000, iv.impliedVolatility());
        }
        using OMDDProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}
}
