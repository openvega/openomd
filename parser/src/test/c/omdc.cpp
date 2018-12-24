#include <gtest/gtest.h>
#include "openomd/omdcparser.h"

namespace omdc
{
namespace sbe
{
class OMDCProcessor
{
#define ONMESSAGE(_MSG) virtual void onMessage(_MSG const&, int32_t){}

public:
    ONMESSAGE(AddOddLotOrder)
    ONMESSAGE(AddOrder)
    ONMESSAGE(AggregateOrderBookUpdate)
    ONMESSAGE(BrokerQueue)
    ONMESSAGE(ClosingPrice)
    ONMESSAGE(CurrencyRate)
    ONMESSAGE(DeleteOddLotOrder)
    ONMESSAGE(DeleteOrder)
    ONMESSAGE(DisasterRecoverySignal)
    ONMESSAGE(IndexData)
    ONMESSAGE(IndexDefinition)
    ONMESSAGE(IndicativeEquilibriumPrice)
    ONMESSAGE(LiquidityProvider)
    ONMESSAGE(Logon)
    ONMESSAGE(LogonResponse)
    ONMESSAGE(MarketDefinition)
    ONMESSAGE(MarketTurnover)
    ONMESSAGE(ModifyOrder)
    ONMESSAGE(News)
    ONMESSAGE(NominalPrice)
    ONMESSAGE(OrderImbalance)
    ONMESSAGE(ReferencePrice)
    ONMESSAGE(RefreshComplete)
    ONMESSAGE(RetransmissionReq)
    ONMESSAGE(RetransmissionResp)
    ONMESSAGE(SecurityDefinition)
    ONMESSAGE(SecurityStatus)
    ONMESSAGE(SequenceReset)
    ONMESSAGE(Statistics)
    ONMESSAGE(StockConnectDailyQuotaBalance)
    ONMESSAGE(StockConnectMarketTurnover)
    ONMESSAGE(Trade)
    ONMESSAGE(TradeCancel)
    ONMESSAGE(TradeTicker)
    ONMESSAGE(TradingSessionStatus)
    ONMESSAGE(VCMTrigger)
    ONMESSAGE(Yield)
    void onUnknownMessage(uint16_t, uint16_t)
    {
    }
    void onError(std::exception const& ex)
    {
        printf("OMDCProcessor error %s\n", ex.what());
    }
};

template <typename _Processor>
void processMsg(char* msg, size_t size)
{
    _Processor processor;
    openomd::OmdcParser parser;
    parser.parse(msg, size, processor, 0);
}

//struct Processor : public OMDCProcessor
//{
//    void onMessage(, int32_t)
//    {
//    }
//    using OMDCProcessor::onMessage;
//};
//processMsg<Processor>(msg, sizeof(msg) - 1);

TEST(OMDC_TEST, SequenceReset)
{
    char msg[] = "\x18\x00\x01\x02\x01\x00\x00\x00\x80\x73\x01\x12\xc8\xf4\x12\x15" \
        "\x08\x00\x64\x00\x01\x00\x00\x00";
    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::SequenceReset const& sr, int32_t partition)
        {
            EXPECT_EQ(1, sr.newSeqNo());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, Logon)
{
}

TEST(OMDC_TEST, LogonResponse)
{
}

TEST(OMDC_TEST, DisasterRecoverySignal)
{
    char msg[] = "\x18\x00\x01\x00\xe4\x01\x00\x00\x40\x1c\xe4\x8e\xff\xfd\x3c\x14" \
        "\x08\x00\x69\x00\x02\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::DisasterRecoverySignal const& dr, int32_t)
        {
            EXPECT_EQ(2, dr.drStatus());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, RetransmissionRequest)
{

}

TEST(OMDC_TEST, RetransmissionResponse)
{

}

TEST(OMDC_TEST, RefreshComplete)
{
    char msg[] = "\x18\x00\x01\x5d\x01\x00\x00\x00\x40\x87\x44\xa5\xa2\x10\x45\x15" \
        "\x08\x00\xcb\x00\x00\x00\x00\x00";
    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::RefreshComplete const& rc, int32_t partition)
        {
            EXPECT_EQ(0, rc.lastSeqNum());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, MarketDefinition)
{
    char msg[] = "\x90\x00\x04\x5c\x51\x9a\x00\x00\x80\xc7\x49\x0b\xc4\xfd\x3c\x14" \
        "\x28\x00\x0a\x00\x4e\x41\x53\x44\x4e\x41\x53\x44\x41\x51\x2d\x41" \
        "\x4d\x45\x58\x20\x42\x4f\x41\x52\x44\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x48\x4b\x44\x1f\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::MarketDefinition const& md, int32_t)
        {
            EXPECT_EQ("NASD", md.getMarketCodeAsString());
            EXPECT_EQ("NASDAQ-AMEX BOARD        ", md.getMarketNameAsString());
            EXPECT_EQ("HKD", md.getCurrencyCodeAsString());
            EXPECT_EQ(31, md.numberOfSecurities());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, SecurityDefinition)
{
    // Warrant
    char msg[] = "\x98\x05\x03\x02\x82\x0d\x00\x00\x00\xc8\xb9\xc1\x08\xf5\x12\x15" \
        "\xd8\x01\x0b\x00\x8f\x2c\x00\x00\x4d\x41\x49\x4e\x4e\x4c\x30\x30" \
        "\x31\x32\x34\x38\x34\x35\x31\x33\x57\x52\x4e\x54\x03\x00\x30\x31" \
        "\x42\x50\x2d\x49\x43\x42\x43\x40\x45\x43\x31\x38\x31\x30\x42\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x48\x4b\x44\xe5\x5d\x4c\x88\xd5" \
        "\x6c\xf4\x5d\x6b\x51\x41\x53\xfc\x8c\x22\xff\x00\x30\x00\x30\x00" \
        "\x30\x00\x30\x00\x30\x00\x30\x00\x30\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\xe5\x5d\x4c\x88\xd5\x6c\xf4\x5d\x6b" \
        "\x51\x41\x53\x2d\x8d\x22\xff\x00\x30\x00\x30\x00\x30\x00\x30\x00" \
        "\x30\x00\x30\x00\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\xe8\x03\x00\x00\x00\x00\x00\x00\x44\x02\x00\x00\x4e" \
        "\x4e\x4e\x59\x4e\x4e\x4e\x00\x4d\xc8\x33\x01\x00\x00\x00\x00\x45" \
        "\x58\x45\x52\x20\x44\x41\x54\x45\x3a\x30\x33\x2f\x31\x30\x2f\x31" \
        "\x38\x20\x2a\x4c\x50\x39\x36\x39\x32\x2d\x32\x31\x30\x38\x20\x35" \
        "\x36\x30\x30\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x20\x20\x20\x00\x00\x00\x00\x20\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x64\x19" \
        "\x00\x00\x00\x00\x00\x00\x0b\xf0\x33\x01\x43\x45\x00\x00\x4e\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00" \
        "\x76\x05\x00\x00\xe8\x03\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::SecurityDefinition& sd, int32_t)
        {
            EXPECT_EQ(11407, sd.securityCode());
            EXPECT_EQ("MAIN", sd.getMarketCodeAsString());
            EXPECT_EQ("NL0012484513", sd.getIsinCodeAsString());
            EXPECT_EQ("WRNT", sd.getInstrumentTypeAsString());
            EXPECT_EQ(3, sd.productType());
            EXPECT_EQ("01", sd.getSpreadTableCodeAsString());
            EXPECT_EQ("BP-ICBC@EC1810B                         ", sd.getSecurityShortNameAsString());
            EXPECT_EQ("HKD", sd.getCurrencyCodeAsString());
            EXPECT_EQ(1000, sd.lotSize());
            EXPECT_EQ(580, sd.previousClosingPrice());
            EXPECT_EQ(78, sd.vcmFlag());
            EXPECT_EQ(78, sd.shortSellFlag());
            EXPECT_EQ(78, sd.casFlag());
            EXPECT_EQ(89, sd.ccassFlag());
            EXPECT_EQ(78, sd.dummySecurityFlag());
            EXPECT_EQ(78, sd.stampDutyFlag());
            EXPECT_EQ(20170829, sd.listingDate());
            EXPECT_EQ(0, sd.delistingDate());
            EXPECT_EQ("EXER DATE:03/10/18 *LP9692-2108 5600  ", sd.getFreeTextAsString());
            EXPECT_EQ(0, sd.efnFlag());
            EXPECT_EQ(0, sd.accruedInterest());
            EXPECT_EQ(0, sd.couponRate());
            EXPECT_EQ(1000, sd.conversionRatio());
            EXPECT_EQ(6500, sd.strikePrice1());
            EXPECT_EQ(0, sd.strikePrice2());
            EXPECT_EQ(20181003, sd.maturityDate());
            EXPECT_EQ(67, sd.callPutFlag());
            EXPECT_EQ(69, sd.style());
            EXPECT_EQ(78, sd.warrantType());
            EXPECT_EQ(0, sd.callPrice());
            EXPECT_EQ(0, sd.decimalsInCallPrice());
            EXPECT_EQ(0, sd.entitlement());
            EXPECT_EQ(3, sd.decimalsInEntitlement());
            EXPECT_EQ(0, sd.noWarrantsPerEntitlement());
            auto& underlyings = sd.noUnderlyingSecurities();
            EXPECT_EQ(1, underlyings.count());
            EXPECT_EQ(true, underlyings.hasNext());
            underlyings.next();
            EXPECT_EQ(1398, underlyings.underlyingSecurityCode());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);

    // CBBC
    char cbbcMsg[] = "\x88\x05\x03\x02\x54\x29\x00\x00\xc0\x64\x1d\x34\x0d\xf5\x12\x15" \
        "\xd0\x01\x0b\x00\x06\xed\x00\x00\x4d\x41\x49\x4e\x4e\x41\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x57\x52\x4e\x54\x0b\x00\x30\x31" \
        "\x47\x53\x23\x48\x53\x49\x20\x20\x52\x43\x31\x39\x30\x34\x46\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x48\x4b\x44\x52\x60\x07\x63\xd8" \
        "\x9a\xdb\x76\x5d\x4e\xdb\x56\x5b\x72\x26\xff\x00\x30\x00\x30\x00" \
        "\x30\x00\x30\x00\x30\x00\x30\x00\x30\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x52\x60\x07\x63\xd8\x9a\xdb\x76\x5d" \
        "\x4e\xdb\x56\x5b\x72\x26\xff\x00\x30\x00\x30\x00\x30\x00\x30\x00" \
        "\x30\x00\x30\x00\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x10\x27\x00\x00\x00\x00\x00\x00\xc5\x00\x00\x00\x4e" \
        "\x4e\x4e\x59\x4e\x4e\x4e\x00\xfe\xc8\x33\x01\x00\x00\x00\x00\x43" \
        "\x50\x3d\x32\x37\x36\x34\x32\x2a\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x4c\x50\x39\x37\x32\x32\x2a\x32\x39\x37\x38\x32\x33\x33" \
        "\x33\x2a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x20\x20\x20\x00\x00\x00\x00\x20\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xf0\x41" \
        "\xa4\x01\x00\x00\x00\x00\xdd\x14\x34\x01\x43\x45\x00\x00\x4e\xa8" \
        "\x2d\x2a\x00\x02\x00\x00\x00\x00\x03\x00\x00\x00\x00\x48\x53\x49" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

    struct CbbcProcessor : public OMDCProcessor
    {
        void onMessage(sbe::SecurityDefinition& sd, int32_t)
        {
            EXPECT_EQ(60678, sd.securityCode());
            EXPECT_EQ("MAIN", sd.getMarketCodeAsString());
            EXPECT_EQ("NA          ", sd.getIsinCodeAsString());
            EXPECT_EQ("WRNT", sd.getInstrumentTypeAsString());
            EXPECT_EQ(11, sd.productType());
            EXPECT_EQ("01", sd.getSpreadTableCodeAsString());
            EXPECT_EQ("GS#HSI  RC1904F                         ", sd.getSecurityShortNameAsString());
            EXPECT_EQ("HKD", sd.getCurrencyCodeAsString());
            EXPECT_EQ(10000, sd.lotSize());
            EXPECT_EQ(197, sd.previousClosingPrice());
            EXPECT_EQ(78, sd.vcmFlag());
            EXPECT_EQ(78, sd.shortSellFlag());
            EXPECT_EQ(78, sd.casFlag());
            EXPECT_EQ(89, sd.ccassFlag());
            EXPECT_EQ(78, sd.dummySecurityFlag());
            EXPECT_EQ(78, sd.stampDutyFlag());
            EXPECT_EQ(20171006, sd.listingDate());
            EXPECT_EQ(0, sd.delistingDate());
            EXPECT_EQ("CP=27642*          LP9722*29782333*   ", sd.getFreeTextAsString());
            EXPECT_EQ(0, sd.efnFlag());
            EXPECT_EQ(0, sd.accruedInterest());
            EXPECT_EQ(0, sd.couponRate());
            EXPECT_EQ(0, sd.conversionRatio());
            EXPECT_EQ(27542000, sd.strikePrice1());
            EXPECT_EQ(0, sd.strikePrice2());
            EXPECT_EQ(20190429, sd.maturityDate());
            EXPECT_EQ(67, sd.callPutFlag());
            EXPECT_EQ(69, sd.style());
            EXPECT_EQ(78, sd.warrantType());
            EXPECT_EQ(2764200, sd.callPrice());
            EXPECT_EQ(2, sd.decimalsInCallPrice());
            EXPECT_EQ(0, sd.entitlement());
            EXPECT_EQ(3, sd.decimalsInEntitlement());
            EXPECT_EQ(0, sd.noWarrantsPerEntitlement());
            auto& underlyings = sd.noUnderlyingSecurities();
            EXPECT_EQ(0, underlyings.count());
            EXPECT_EQ(false, underlyings.hasNext());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<CbbcProcessor>(cbbcMsg, sizeof(cbbcMsg) - 1);
}

TEST(OMDC_TEST, LiquidityProvider)
{
    char msg[] = "\xbc\x05\x79\x02\x46\x37\x00\x00\x40\xaa\xe1\x57\x0f\xf5\x12\x15" \
        "\x0c\x00\x0d\x00\x28\x2d\x00\x00\x01\x00\xeb\x25";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::LiquidityProvider& lp, int32_t)
        {
            EXPECT_EQ(11560, lp.securityCode());
            auto& lps = lp.noLiquidityProviders();
            EXPECT_EQ(1, lps.count());
            EXPECT_EQ(true, lps.hasNext());
            lps.next();
            EXPECT_EQ(9707, lps.lpBrokerNumber());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, CurrencyRate)
{
    char msg[] = "\xc0\x05\x06\x2f\x78\x86\x15\x00\xc0\x95\x39\x59\xc8\xf9\x12\x15" \
        "\x10\x00\x0e\x00\x47\x42\x50\x00\x00\x00\x00\x00\xec\xa3\x01\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::CurrencyRate const& cr, int32_t)
        {
            EXPECT_EQ("GBP", cr.getCurrencyCodeAsString());
            EXPECT_EQ(107500, cr.currencyRate());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, TradingSessionStatus)
{
    char msg[] = "\x48\x00\x03\x00\x75\xd6\x08\x00\x00\x09\xda\xdd\x49\x22\x13\x15" \
        "\x20\x00\x14\x00\x4d\x41\x49\x4e\x01\x69\x05\x30\x20\x20\x20\x20" \
        "\x00\x00\x9d\xdd\x49\x22\x13\x15\x00\x8e\x49\x9a\x57\x22\x13\x15";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::TradingSessionStatus const& ts, int32_t partition)
        {
            EXPECT_EQ("MAIN", ts.getMarketCodeAsString());
            EXPECT_EQ(105, ts.tradingSessionSubID());
            EXPECT_EQ(5, ts.tradingSesStatus());
            EXPECT_EQ(48, ts.tradingSesControlFlag());
            EXPECT_EQ(1518595200000000000, ts.startDateTime());
            EXPECT_EQ(1518595259000000000, ts.endDateTime());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, SecurityStatus)
{
    char msg[] = "\x30\x01\x18\xdd\x31\x00\x00\x00\x00\x99\x00\x43\x06\xf5\x12\x15" \
        "\x0c\x00\x15\x00\x46\x62\x00\x00\x02\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::SecurityStatus const& ss, int32_t partition)
        {
            EXPECT_EQ(25158, ss.securityCode());
            EXPECT_EQ(2, ss.suspensionIndicator());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, AddOrder)
{
    char msg[] = "\x30\x00\x01\xdd\xf7\x71\x01\x00\x40\x06\x28\xec\x06\x0d\x13\x15" \
        "\x20\x00\x1e\x00\x1d\x01\x00\x00\x02\xc8\x15\x01\x00\x00\x00\x00" \
        "\x34\x44\x00\x00\xe8\x03\x00\x00\x01\x00\x32\x00\x00\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::AddOrder const& ao, int32_t)
        {
            EXPECT_EQ(285, ao.securityCode());
            EXPECT_EQ(18204674, ao.orderID());
            EXPECT_EQ(17460, ao.price());
            EXPECT_EQ(1000, ao.quantity());
            EXPECT_EQ(1, ao.side());
            EXPECT_EQ(50, ao.orderType());
            EXPECT_EQ(0, ao.orderBookPosition());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
    
}

TEST(OMDC_TEST, ModifyOrder)
{
    char msg[] = "\xb0\x05\x38\x00\x27\x89\x05\x00\xc0\xed\x53\xf9\x24\x0d\x13\x15" \
        "\x1c\x00\x1f\x00\xb3\x4e\x00\x00\x01\xdc\x1d\x03\x00\x00\x00\x00" \
        "\x20\x53\x14\x00\x01\x00\x00\x00\x00\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::ModifyOrder const& mo, int32_t)
        {
            EXPECT_EQ(20147, mo.securityCode());
            EXPECT_EQ(52288513, mo.orderID());
            EXPECT_EQ(1332000, mo.quantity());
            EXPECT_EQ(1, mo.side());
            EXPECT_EQ(0, mo.orderBookPosition());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, DeleteOrder)
{
    char msg[] = "\x44\x00\x02\xba\xe8\xb2\x08\x00\x80\x91\xfe\xec\x45\x0d\x13\x15" \
        "\x14\x00\x20\x00\xbd\x4a\x00\x00\x03\x28\x9e\x04\x00\x00\x00\x00" \
        "\x01\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::DeleteOrder const& d, int32_t)
        {
            EXPECT_EQ(19133, d.securityCode());
            EXPECT_EQ(77473795, d.orderID());
            EXPECT_EQ(1, d.side());            
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, AddOddLotOrder)
{
    char msg[] = "\x08\x02\x12\x01\x49\x01\x00\x00\x00\xff\xed\xbc\x39\x0d\x13\x15" \
        "\x1c\x00\x21\x00\x23\x00\x00\x00\x01\x05\x07\x01\x00\x00\x00\x00" \
        "\x5c\x12\x00\x00\x1c\x01\x00\x00\xec\x11\x01\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::AddOddLotOrder const& oo, int32_t)
        {
            EXPECT_EQ(35, oo.securityCode());
            EXPECT_EQ(17237249, oo.orderID());
            EXPECT_EQ(4700, oo.price());
            EXPECT_EQ(284, oo.quantity());
            EXPECT_EQ(4588, oo.brokerID());
            EXPECT_EQ(1, oo.side());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, DeleteOddLotOrder)
{
    char msg[] = "\x24\x00\x01\x02\x23\x01\x00\x00\xc0\x9c\xfb\x65\x47\x22\x13\x15" \
        "\x14\x00\x22\x00\xbc\x02\x00\x00\x01\x0c\x36\x56\x00\x00\x00\x00" \
        "\x30\x03\x01\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::DeleteOddLotOrder const& dol, int32_t)
        {
            EXPECT_EQ(700, dol.securityCode());
            EXPECT_EQ(1446382593, dol.orderID());
            EXPECT_EQ(816, dol.brokerID());
            EXPECT_EQ(1, dol.side());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, AggregateOrderBookUpdate)
{
    char msg[] = "\xe0\x04\x14\xc6\xd0\x18\x12\x00\x00\x0d\xe0\xec\x45\x0d\x13\x15\xcc\x00\x35\x00\xd5\x49\x00\x00\x05\x01\x00\x08" \
        "\xe0\x93\x04\x00\x00\x00\x00\x00\xe5\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x02\x00\x00\x00\x00" \
        "\xe0\x93\x04\x00\x00\x00\x00\x00\xea\x00\x00\x00\x01\x00\x00\x00\x01\x00\x01\x00\x00\x00\x00\x00" \
        "\xe0\x93\x04\x00\x00\x00\x00\x00\xe4\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x02\x00\x00\x00\x00" \
        "\xe0\x93\x04\x00\x00\x00\x00\x00\xeb\x00\x00\x00\x01\x00\x00\x00\x01\x00\x02\x02\x00\x00\x00\x00" \
        "\xe0\x93\x04\x00\x00\x00\x00\x00\xe3\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x02\x00\x00\x00\x00" \
        "\xe0\x93\x04\x00\x00\x00\x00\x00\xe2\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00" \
        "\xe0\x93\x04\x00\x00\x00\x00\x00\xe1\x00\x00\x00\x01\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00" \
        "\xe0\x93\x04\x00\x00\x00\x00\x00\xe0\x00\x00\x00\x01\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00" ;

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::AggregateOrderBookUpdate& aob, int32_t)
        {
            EXPECT_EQ(18901, aob.securityCode());
            auto& en = aob.noEntries();
            EXPECT_EQ(8, en.count());
            
            en.next();
            EXPECT_EQ(300000, en.aggregateQuantity());
            EXPECT_EQ(229, en.price());
            EXPECT_EQ(1, en.numberOfOrders());
            EXPECT_EQ(0, en.side());
            EXPECT_EQ(1, en.priceLevel());
            EXPECT_EQ(2, en.updateAction());
            
            en.next();
            EXPECT_EQ(300000, en.aggregateQuantity());
            EXPECT_EQ(234, en.price());
            EXPECT_EQ(1, en.numberOfOrders());
            EXPECT_EQ(1, en.side());
            EXPECT_EQ(1, en.priceLevel());
            EXPECT_EQ(0, en.updateAction());

            en.next();
            EXPECT_EQ(300000, en.aggregateQuantity());
            EXPECT_EQ(228, en.price());
            EXPECT_EQ(1, en.numberOfOrders());
            EXPECT_EQ(0, en.side());
            EXPECT_EQ(1, en.priceLevel());
            EXPECT_EQ(2, en.updateAction());

            en.next();
            EXPECT_EQ(300000, en.aggregateQuantity());
            EXPECT_EQ(235, en.price());
            EXPECT_EQ(1, en.numberOfOrders());
            EXPECT_EQ(1, en.side());
            EXPECT_EQ(2, en.priceLevel());
            EXPECT_EQ(2, en.updateAction());
            
            en.next();
            EXPECT_EQ(300000, en.aggregateQuantity());
            EXPECT_EQ(227, en.price());
            EXPECT_EQ(1, en.numberOfOrders());
            EXPECT_EQ(0, en.side());
            EXPECT_EQ(1, en.priceLevel());
            EXPECT_EQ(2, en.updateAction());
            
            en.next();
            EXPECT_EQ(300000, en.aggregateQuantity());
            EXPECT_EQ(226, en.price());
            EXPECT_EQ(1, en.numberOfOrders());
            EXPECT_EQ(0, en.side());
            EXPECT_EQ(1, en.priceLevel());
            EXPECT_EQ(0, en.updateAction());
            
            en.next();
            EXPECT_EQ(300000, en.aggregateQuantity());
            EXPECT_EQ(225, en.price());
            EXPECT_EQ(1, en.numberOfOrders());
            EXPECT_EQ(0, en.side());
            EXPECT_EQ(2, en.priceLevel());
            EXPECT_EQ(0, en.updateAction());

            en.next();
            EXPECT_EQ(300000, en.aggregateQuantity());
            EXPECT_EQ(224, en.price());
            EXPECT_EQ(1, en.numberOfOrders());
            EXPECT_EQ(0, en.side());
            EXPECT_EQ(3, en.priceLevel());
            EXPECT_EQ(0, en.updateAction());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);

}

TEST(OMDC_TEST, BrokerQueue)
{
    char msg[] = "\xc4\x02\x07\x00\x70\x7c" \
        "\x97\x00\x00\x7f\x1e\x12\x47\x22\x13\x15\xac\x00\x36\x00\x74\x0c" \
        "\x00\x00\x28\x02\x00\x59\x01\x21\x42\x00\xd2\x05\x42\x00\xd2\x05" \
        "\x42\x00\x01\x00\x53\x00\xd2\x05\x42\x00\xab\x05\x42\x00\x91\x00" \
        "\x42\x00\x02\x00\x53\x00\xd2\x05\x42\x00\xd2\x05\x42\x00\x91\x00" \
        "\x42\x00\x3c\x21\x42\x00\x3c\x21\x42\x00\xab\x05\x42\x00\x01\x02" \
        "\x42\x00\x3c\x21\x42\x00\xab\x05\x42\x00\x03\x00\x53\x00\xd2\x05" \
        "\x42\x00\x01\x02\x42\x00\xd2\x05\x42\x00\xd2\x05\x42\x00\xd2\x05" \
        "\x42\x00\xd2\x05\x42\x00\x40\x23\x42\x00\x01\x02\x42\x00\x3c\x21" \
        "\x42\x00\xab\x05\x42\x00\xd5\x10\x42\x00\x3c\x21\x42\x00\x3c\x21" \
        "\x42\x00\x3c\x21\x42\x00\x3c\x21\x42\x00\xab\x05\x42\x00\x3a\x21" \
        "\x42\x00\xab\x05\x42\x00\xd5\x10\x42\x00\x04\x00\x53\x00\x3c\x21" \
        "\x42\x00\x3f\x23\x42\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::BrokerQueue& bq, int32_t)
        {
            EXPECT_EQ(3188, bq.securityCode());
            auto& items = bq.items();
            EXPECT_EQ(40, items.count());
            EXPECT_EQ(2, items.side());
            EXPECT_EQ(89, items.bqMoreFlag());

            items.next();
            EXPECT_EQ(8449, items.item());
            EXPECT_EQ(66, items.itemType());

            items.next();
            EXPECT_EQ(1490, items.item());
            EXPECT_EQ(66, items.itemType());

            items.next();
            EXPECT_EQ(1490, items.item());
            EXPECT_EQ(66, items.itemType());

            items.next();
            EXPECT_EQ(1, items.item());
            EXPECT_EQ(83, items.itemType());

            items.next();
            EXPECT_EQ(1490, items.item());
            EXPECT_EQ(66, items.itemType());

            items.next();
            EXPECT_EQ(1451, items.item());
            EXPECT_EQ(66, items.itemType());

            items.next();
            EXPECT_EQ(145, items.item());
            EXPECT_EQ(66, items.itemType());

            // check last
            while (items.hasNext())
            {
                items.next();
            }
            EXPECT_EQ(9023, items.item());
            EXPECT_EQ(66, items.itemType());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);


}

TEST(OMDC_TEST, OrderImbalance)
{
    char msg[] = "\xbc\x05\x18\x2f\x35\x25\x31\x01\x00\x12\xf6\xae\x71\x22\x13\x15" \
        "\x14\x00\x38\x00\x4e\x05\x00\x00\x42\x01\x50\x46\x00\x00\x00\x00" \
        "\x00\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::OrderImbalance const& oib, int32_t)
        {
            EXPECT_EQ(1358, oib.securityCode());
            EXPECT_EQ(66, oib.orderImbalanceDirection());
            EXPECT_EQ(18000, oib.orderImbalanceQuantity());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, Trade)
{
    char msg[] = "\x54\x01\x0a\xc6\xb3\x8d\x09\x00\xc0\xca\xd0\xec\x45\x0d\x13\x15" \
        "\x20\x00\x32\x00\x44\x0a\x00\x00\x6b\x01\x00\x00\x42\x59\x00\x00" \
        "\xb8\x0b\x00\x00\x00\x00\x00\x00\x00\x22\x16\xd9\x45\x0d\x13\x15";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::Trade const& t, int32_t)
        {
            EXPECT_EQ(2628, t.securityCode());
            EXPECT_EQ(363, t.tradeID());
            EXPECT_EQ(22850, t.price());
            EXPECT_EQ(3000, t.quantity());
            EXPECT_EQ(0, t.trdType());
            EXPECT_EQ(1518572093000000000, t.tradeTime());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, TradeCancel)
{

}

TEST(OMDC_TEST, TradeTicker)
{
    char msg[] = "\x38\x05\x15\xc6\xb8\x92\x04\x00\xc0\x8a\x46\xec\x06\x0d\x13\x15" \
        "\x24\x00\x34\x00\x84\x01\x00\x00\x2c\x00\x00\x00\x50\x15\x04\x00\xc8\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x4c\x3a\xc0\x06\x0d\x13\x15\x00\x00\x4e\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::TradeTicker const& tt, int32_t)
        {
            EXPECT_EQ(388, tt.securityCode());
            EXPECT_EQ(44, tt.tickerID());
            EXPECT_EQ(267600, tt.price());
            EXPECT_EQ(200, tt.aggregateQuantity());
            EXPECT_EQ(0, tt.trdType());
            EXPECT_EQ('N', tt.trdCancelFlag());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, ClosingPrice)
{
    char msg[] = "\x20\x00\x01\x00\x52\xef\x08\x00\x80\xbb\xfa\xbf\xbe\x22\x13\x15" \
        "\x10\x00\x3e\x00\x76\x05\x00\x00\x7c\x1a\x00\x00\x04\x49\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::ClosingPrice const& cp, int32_t)
        {
            EXPECT_EQ(1398, cp.securityCode());
            EXPECT_EQ(6780, cp.closingPrice());
            EXPECT_EQ(18692, cp.numberOfTrades());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, NominalPrice)
{
    char msg[] = "\x44\x01\x06\xc6\xcd\x92\x04\x00\xc0\x8a\x46\xec\x06\x0d\x13\x15" \
        "\x0c\x00\x28\x00\x91\xfe\x00\x00\x6e\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::NominalPrice const& np, int32_t)
        {
            EXPECT_EQ(65169, np.securityCode());
            EXPECT_EQ(110, np.nominalPrice());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, IndicativeEquilibriumPrice)
{
    char msg[] = "\x24\x00\x01\x00\x59\x00\x00\x00\xc0\x59\x2e\x8f\x5e\x0b\x13\x15" \
        "\x14\x00\x29\x00\xbc\x02\x00\x00\xb0\x8f\x06\x00\x3c\x28\x00\x00" \
        "\x00\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::IndicativeEquilibriumPrice const& iep, int32_t)
        {
            EXPECT_EQ(700, iep.securityCode());
            EXPECT_EQ(430000, iep.price());
            EXPECT_EQ(10300, iep.aggregateQuantity());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, ReferencePrice)
{
    char msg[] = "\x44\x05\x2f\x2f\x2b\x36\x31\x01\x00\xd8\x46\x2e\x72\x22\x13\x15" \
        "\x14\x00\x2b\x00\x26\x0c\x00\x00\xda\x7a\x00\x00\xcc\x74\x00\x00" \
        "\xe8\x80\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::ReferencePrice const& rp, int32_t)
        {
            EXPECT_EQ(3110, rp.securityCode());
            EXPECT_EQ(31450, rp.referencePrice());
            EXPECT_EQ(29900, rp.lowerPrice());
            EXPECT_EQ(33000, rp.upperPrice());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, VCMTrigger)
{
    char msg[] = "\xc0\x05\x48\xcd\x50\x12\x02\x00\x80\x0d\x4d\xbe\x45\x2c\x63\x14" \
        "\x24\x00\x17\x00\x63\x09\x00\x00\x00\x2e\x11\xb1\x07\x2c\x63\x14" \
        "\x00\xe6\x75\x8a\x4d\x2c\x63\x14\x82\x00\x00\x00\x75\x00\x00\x00" \
        "\x8f\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::VCMTrigger const& vcm, int32_t)
        {
            EXPECT_EQ(2403, vcm.securityCode());
            EXPECT_EQ(1469066315000000000, vcm.coolingOffStartTime());
            EXPECT_EQ(1469066615000000000, vcm.coolingOffEndTime());
            EXPECT_EQ(130, vcm.vcmReferencePrice());
            EXPECT_EQ(117, vcm.vcmLowerPrice());
            EXPECT_EQ(143, vcm.vcmUpperPrice());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, Statistics)
{
    char msg[] = "\x44\x00\x01\x00\x9d\xd2\x08\x00\x40\x82\x82\x10\x47\x22\x13\x15" \
        "\x34\x00\x3c\x00\x74\x0c\x00\x00\x30\x50\x98\x00\x00\x00\x00\x00" \
        "\x20\xe0\xfe\xdd\x72\x00\x00\x00\x88\xc2\x00\x00\x68\xbf\x00\x00" \
        "\xc0\xc1\x00\x00\x10\xc1\x00\x00\x38\x9a\x14\x00\x90\x49\x48\x79" \
        "\x0f\x00\x00\x00";
    
    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::Statistics const& s, int32_t)
        {
            EXPECT_EQ(3188, s.securityCode());
            EXPECT_EQ(9982000, s.sharesTraded());
            EXPECT_EQ(493350740000, s.turnover());
            EXPECT_EQ(49800, s.highPrice());
            EXPECT_EQ(49000, s.lowPrice());
            EXPECT_EQ(49600, s.lastPrice());
            EXPECT_EQ(49424, s.vwap());
            EXPECT_EQ(1350200, s.shortSellSharesTraded());
            EXPECT_EQ(66459290000, s.shortSellTurnover());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, MarketTurnover)
{
    char msg[] = "\xb0\x00\x08\x00\x31\x87\x01\x00\x00\x48\x34\xba\x47\x22\x13\x15" 
        "\x14\x00\x3d\x00\x4d\x41\x49\x4e\x48\x4b\x44\x20\x59\x0d\x5b\xb9\x26\x5e\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::MarketTurnover const& mt, int32_t)
        {
            EXPECT_EQ("MAIN", mt.getMarketCodeAsString());
            EXPECT_EQ("HKD", mt.getCurrencyCodeAsString());
            EXPECT_EQ(103520411520345, mt.turnover());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, Yield)
{

}

TEST(OMDC_TEST, News)
{
    char msg[] = "\x34\x05\x01\x00\x3c\x31\x00\x00\x80\x9b\x07\x4e\x79\x3e\x63\x14" \
        "\x24\x05\x16\x00\x45\x58\x4e\x30\x30\x35\x00\x00\x00\x00\x00\x00" \

        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x4e\x4e\x00\x00\x00\x00" \
        "\x00\xa6\xae\xc9\x29\x31\x63\x14\x00\x00\x00\x00\x00\x00\xc8\x00" \
        "\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x04\x00\x00\x00" \
        "\x05\x00\x00\x00\x06\x00\x00\x00\x07\x00\x00\x00\x08\x00\x00\x00" \
        "\x09\x00\x00\x00\x0a\x00\x00\x00\x0e\x00\x00\x00\x1c\x00\x00\x00" \
        "\x10\x00\x00\x00\x11\x00\x00\x00\x12\x00\x00\x00\x13\x00\x00\x00" \
        "\x14\x00\x00\x00\x15\x00\x00\x00\x16\x00\x00\x00\x17\x00\x00\x00" \
        "\x1d\x00\x00\x00\x1e\x00\x00\x00\x1f\x00\x00\x00\x20\x00\x00\x00" \
        "\x25\x00\x00\x00\x26\x00\x00\x00\x2c\x00\x00\x00\x30\x00\x00\x00" \
        "\x31\x00\x00\x00\x32\x00\x00\x00\x33\x00\x00\x00\x34\x00\x00\x00" \
        "\x35\x00\x00\x00\x36\x00\x00\x00\x37\x00\x00\x00\x3a\x00\x00\x00" \
        "\x3b\x00\x00\x00\x3c\x00\x00\x00\x3d\x00\x00\x00\x3e\x00\x00\x00" \
        "\x3f\x00\x00\x00\x42\x00\x00\x00\x7e\x03\x00\x00\x86\x03\x00\x00" \
        "\x89\x03\x00\x00\x8a\x03\x00\x00\x92\x03\x00\x00\x94\x03\x00\x00" \
        "\x95\x03\x00\x00\x98\x03\x00\x00\xab\x03\x00\x00\xb7\x03\x00\x00" \
        "\xc6\x03\x00\x00\xd5\x03\x00\x00\xdf\x03\x00\x00\xe6\x03\x00\x00" \
        "\xf3\x03\x00\x00\xf4\x03\x00\x00\xf5\x03\x00\x00\xf7\x03\x00\x00" \
        "\xf9\x03\x00\x00\xfa\x03\x00\x00\x09\x04\x00\x00\x0e\x04\x00\x00" \
        "\x14\x04\x00\x00\x1f\x04\x00\x00\x2c\x04\x00\x00\x40\x04\x00\x00" \
        "\x4b\x04\x00\x00\x55\x04\x00\x00\x5a\x04\x00\x00\x6d\x04\x00\x00" \
        "\x72\x04\x00\x00\x77\x04\x00\x00\x93\x04\x00\x00\x96\x04\x00\x00" \
        "\xa2\x04\x00\x00\xaf\x04\x00\x00\xb0\x04\x00\x00\xb5\x04\x00\x00" \
        "\xb6\x04\x00\x00\xb7\x04\x00\x00\xba\x04\x00\x00\xbb\x04\x00\x00" \
        "\xbc\x04\x00\x00\xbe\x04\x00\x00\xc8\x04\x00\x00\xca\x04\x00\x00" \
        "\xcf\x04\x00\x00\xf7\x04\x00\x00\x35\x05\x00\x00\x57\x05\x00\x00" \
        "\x6b\x05\x00\x00\x71\x05\x00\x00\x74\x05\x00\x00\x76\x05\x00\x00" \
        "\x78\x05\x00\x00\x7d\x05\x00\x00\xd2\x05\x00\x00\xef\x05\x00\x00" \
        "\x52\x06\x00\x00\x6e\x06\x00\x00\x87\x06\x00\x00\x98\x06\x00\x00" \
        "\xa5\x06\x00\x00\xe6\x06\x00\x00\x07\x07\x00\x00\x08\x07\x00\x00" \
        "\x15\x07\x00\x00\x58\x07\x00\x00\x60\x07\x00\x00\x61\x07\x00\x00" \
        "\x65\x07\x00\x00\x6a\x07\x00\x00\x7f\x07\x00\x00\xc4\x07\x00\x00" \
        "\xcd\x07\x00\x00\xd0\x07\x00\x00\xd1\x07\x00\x00\xd2\x07\x00\x00" \
        "\xd3\x07\x00\x00\xd4\x07\x00\x00\xd5\x07\x00\x00\xd6\x07\x00\x00" \
        "\xd7\x07\x00\x00\xe4\x07\x00\x00\xf6\x07\x00\x00\x3c\x08\x00\x00" \
        "\x46\x08\x00\x00\x49\x08\x00\x00\x99\x08\x00\x00\xad\x08\x00\x00" \
        "\xfd\x08\x00\x00\x07\x09\x00\x00\x0a\x09\x00\x00\x0e\x09\x00\x00" \
        "\x0f\x09\x00\x00\x18\x09\x00\x00\x1b\x09\x00\x00\x1c\x09\x00\x00" \
        "\x1d\x09\x00\x00\x22\x09\x00\x00\x2b\x09\x00\x00\x52\x09\x00\x00" \
        "\x54\x09\x00\x00\x60\x09\x00\x00\x61\x09\x00\x00\x62\x09\x00\x00" \
        "\x63\x09\x00\x00\x64\x09\x00\x00\x65\x09\x00\x00\x66\x09\x00\x00" \
        "\x67\x09\x00\x00\x68\x09\x00\x00\x69\x09\x00\x00\x6a\x09\x00\x00" \
        "\x6b\x09\x00\x00\x6c\x09\x00\x00\x6d\x09\x00\x00\x6e\x09\x00\x00" \
        "\x6f\x09\x00\x00\x70\x09\x00\x00\x71\x09\x00\x00\x72\x09\x00\x00" \
        "\x73\x09\x00\x00\x74\x09\x00\x00\x75\x09\x00\x00\x76\x09\x00\x00" \
        "\x77\x09\x00\x00\x78\x09\x00\x00\x7c\x09\x00\x00\x83\x09\x00\x00" \
        "\xa2\x09\x00\x00\xcc\x09\x00\x00\xcd\x09\x00\x00\xd1\x09\x00\x00" \
        "\xd2\x09\x00\x00\xd7\x09\x00\x00\xd9\x09\x00\x00\xe0\x09\x00\x00" \
        "\xe1\x09\x00\x00\x03\x0a\x00\x00\x04\x0a\x00\x00\x05\x0a\x00\x00" \
        "\x07\x0a\x00\x00\x08\x0a\x00\x00\x0e\x0a\x00\x00\x10\x0a\x00\x00" \
        "\x12\x0a\x00\x00\x13\x0a\x00\x00\x1e\x0a\x00\x00\x26\x0a\x00\x00" \
        "\x28\x0a\x00\x00\x29\x0a\x00\x00\x42\x0a\x00\x00\x44\x0a\x00\x00" \
        "\x80\x0a\x00\x00\x8c\x0a\x00\x00\xa7\x0a\x00\x00\xd9\x0a\x00\x00" \
        
        "\x20\x00\x01\x00\x73\x68\x61\x72\x65\x73\x2f\x73\x65\x63\x75\x72" \
        "\x69\x74\x69\x65\x73\x20\x6f\x66\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x28\x74\x68\x65\x20\x22\x43\x6f\x6d\x70\x61\x6e\x79\x22" \
        "\x29\x20\x77\x69\x6c\x6c\x20\x62\x65\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::News& news, int32_t)
        {
            EXPECT_EQ("EXN", news.getNewsTypeAsString());
            EXPECT_EQ("005", news.getNewsIDAsString());
            EXPECT_EQ('N', news.cancelFlag());
            EXPECT_EQ('N', news.lastFragment());
            EXPECT_EQ(1469071959000000000, news.releaseTime());
            auto& market = news.noMarketCodes();
            EXPECT_EQ(0, market.count());
            EXPECT_EQ(false, market.hasNext());
            auto& sec = news.noSecurityCodes();
            EXPECT_EQ(200, sec.count());
            sec.next();
            EXPECT_EQ(1, sec.securityCode());
            while (sec.hasNext())
            {
                sec.next();
            }
            EXPECT_EQ(2777, sec.securityCode());
            auto& newsLines = news.noNewsLines();
            EXPECT_EQ(1, newsLines.count());
            newsLines.next();
            EXPECT_EQ(160, newsLines.getNewsLineAsString().size());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, IndexDefinition)
{
    char msg[] = "\x24\x00\x01\x00\x01\x00\x00\x00\xc0\xb8\x9f\xd5\x03\xf5\x12\x15" \
        "\x14\x00\x46\x00\x30\x30\x30\x30\x30\x31\x20\x20\x20\x20\x20\x43" \
        "\x43\x4e\x59\x20";
    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::IndexDefinition const& id, int32_t partition)
        {
            EXPECT_EQ("000001     ", id.getIndexCodeAsString());
            EXPECT_EQ(67, id.indexSource());
            EXPECT_EQ("CNY", id.getCurrencyCodeAsString());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, IndexData)
{
    char msg[] = "\x80\x00\x01\x84\x4e\x63\x02\x00\xc0\xe2\x32\x4b\xe8\x23\x13\x15" \
        "\x70\x00\x47\x00\x48\x31\x31\x31\x30\x38\x20\x20\x20\x20\x20\x20" \
        "\x00\x6e\x70\x35\xe6\x23\x13\x15\x7d\x24\x14\x01\x00\x00\x00\x00" \
        "\x9f\xa1\x03\x00\x00\x00\x00\x00\x0a\x7c\x14\x01\x00\x00\x00\x00" \
        "\x16\x61\x10\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80" \
        "\x98\x3b\xeb\x58\xb7\x03\x05\x00\xb8\x7a\x10\x01\x00\x00\x00\x00" \
        "\x7d\x24\x14\x01\x00\x00\x00\x00\xde\x82\x10\x01\x00\x00\x00\x00" \
        "\x28\xa1\x73\x6b\x02\x00\x00\x00\xf4\x33\x00\x00\x20\x20\x20\x20";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::IndexData const& id, int32_t)
        {
            EXPECT_EQ("H11108     ", id.getIndexCodeAsString());
            EXPECT_EQ(32, id.indexStatus());
            EXPECT_EQ(1518596971000000000, id.indexTime());
            EXPECT_EQ(18097277, id.indexValue());
            EXPECT_EQ(237983, id.netChgPrevDay());
            EXPECT_EQ(18119690, id.highValue());
            EXPECT_EQ(17850646, id.lowValue());
            EXPECT_EQ(INT64_MIN, id.easValue());
            EXPECT_EQ(1411460889263000, id.indexTurnover());
            EXPECT_EQ(17857208, id.openingValue());
            EXPECT_EQ(18097277, id.closingValue());
            EXPECT_EQ(17859294, id.previousSesClose());
            EXPECT_EQ(10392674600, id.indexVolume());
            EXPECT_EQ(13300, id.netChgPrevDayPct());
            EXPECT_EQ(' ', id.exception());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, StockConnectDailyQuotaBalance)
{

}

TEST(OMDC_TEST, StockConnectMarketTurnover)
{

}
}
}