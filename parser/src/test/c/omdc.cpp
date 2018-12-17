#include <gtest/gtest.h>
#include "omdc_sbe/Logon.h"
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
    ONMESSAGE(ModifyOrder)
    ONMESSAGE(NominalPrice)
    ONMESSAGE(OrderImbalance)
    ONMESSAGE(ReferencePrice)
    ONMESSAGE(RefreshComplete)
    ONMESSAGE(RetransmissionReq)
    ONMESSAGE(RetransmissionResp)
    ONMESSAGE(SecurityDefinition)
    ONMESSAGE(SecurityStatus)
    ONMESSAGE(SequenceReset)
    ONMESSAGE(Trade)
    ONMESSAGE(TradeCancel)
    ONMESSAGE(TradeTicker)
    ONMESSAGE(TradingSessionStatus)
    ONMESSAGE(VCMTrigger)
    void onUnknownMessage(uint16_t, uint16_t)
    {
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
//
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
            auto& u1 = underlyings.next();
            EXPECT_EQ(1398, u1.underlyingSecurityCode());
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
            auto& lp1 = lps.next();
            EXPECT_EQ(9707, lp1.lpBrokerNumber());
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
    char msg[] = "\x70\x00\x03\x02\x03\x00\x00\x00\x00\x91\x63\x8d\x06\xf5\x12\x15" \
        "\x20\x00\x14\x00\x47\x45\x4d\x20\x01\x64\x00\x30\x20\x20\x20\x20" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::TradingSessionStatus const& ts, int32_t partition)
        {
            EXPECT_EQ("GEM ", ts.getMarketCodeAsString());
            EXPECT_EQ(100, ts.tradingSessionSubID());
            EXPECT_EQ(0, ts.tradingSesStatus());
            EXPECT_EQ(48, ts.tradingSesControlFlag());
            EXPECT_EQ(0, ts.startDateTime());
            EXPECT_EQ(0, ts.endDateTime());
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
            EXPECT_EQ(18204674, ao.orderId());
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

}

TEST(OMDC_TEST, DeleteOrder)
{

}

TEST(OMDC_TEST, AddOddLotOrder)
{

}

TEST(OMDC_TEST, DeleteOddLotOrder)
{

}

TEST(OMDC_TEST, AggregateOrderBookUpdate)
{
    
}

TEST(OMDC_TEST, BrokerQueue)
{
    
}


TEST(OMDC_TEST, OrderImbalance)
{

}

TEST(OMDC_TEST, Trade)
{

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

}

TEST(OMDC_TEST, VCMTrigger)
{

}

TEST(OMDC_TEST, Statistics)
{
    char msg[] = "\x6c\x00\x02\x01\x41\x3e\x00\x00\x00\x4c\xb0\x70\x17\x0d\x13\x15" \
        "\x34\x00\x3c\x00\x4e\x09\x00\x00\xbc\x6e\x07\x00\x00\x00\x00\x00" \
        "\xdc\xda\x0e\xaa\x0d\x00\x00\x00\x2c\xdc\x01\x00\x5c\xd4\x01\x00" \
        "\xc8\xdb\x01\x00\xa5\xd6\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00";
    
    struct Processor : public OMDCProcessor
    {
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, MarketTurnover)
{

}

TEST(OMDC_TEST, Yield)
{

}

TEST(OMDC_TEST, News)
{

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
    char msg[] = "\x80\x00\x01\x84\xff\x16\x00\x00\x40\x09\x65\x99\xd0\x0a\x13\x15" \
        "\x70\x00\x47\x00\x30\x30\x30\x30\x31\x30\x33\x20\x20\x20\x20\x50" \
        "\x00\x4c\xbb\x81\xd0\x0a\x13\x15\x00\x00\x00\x00\x00\x00\x00\x80" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80" \
        "\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x80" \
        "\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x80" \
        "\x00\x00\x00\x00\x00\x00\x00\x80\xd4\x03\x39\x17\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x00\x20\x20\x20\x20";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::IndexData const& id, int32_t)
        {
            EXPECT_EQ("0000103    ", id.getIndexCodeAsString());
            EXPECT_EQ(80, id.indexStatus());
            EXPECT_EQ(1518569390000000000, id.indexTime());
            EXPECT_EQ(-9223372036854775808, id.indexValue());
            EXPECT_EQ(0, id.netChgPrevDay());
            EXPECT_EQ(-9223372036854775808, id.highValue());
            EXPECT_EQ(-9223372036854775808, id.lowValue());
            EXPECT_EQ(-9223372036854775808, id.easValue());
            EXPECT_EQ(-9223372036854775808, id.indexTurnover());
            EXPECT_EQ(-9223372036854775808, id.openingValue());
            EXPECT_EQ(-9223372036854775808, id.closingValue());
            EXPECT_EQ(389612500, id.previousSesClose());
            EXPECT_EQ(-9223372036854775808, id.indexVolume());
            EXPECT_EQ(0, id.netChgPrevDayPct());
            EXPECT_EQ(' ', id.exception());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

}
}