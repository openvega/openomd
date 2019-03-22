#pragma once
#include "openomd/nooplinearbitration.h"
#include "openomd/omdcprocessor.h"
#include "openomd/omddprocessor.h"

namespace openomd
{
template <typename _LineArbitration = NoopLineArbitration>
class OMDCInstrumentProcessor : public OMDCProcessor<_LineArbitration>
{
public:
    void onMessage(omdc::sbe::IndexDefinition const& indexDef, uint32_t seqNum)
    {
    }
    void onMessage(omdc::sbe::MarketDefinition const& mktDef, uint32_t seqNum)
    {
    }
    void onMessage(omdc::sbe::SecurityDefinition const& secDef, uint32_t seqNum)
    {
    }
    void onMessage(omdc::sbe::LiquidityProvider const& lp, uint32_t seqNum)
    {
    }
    using OMDCProcessor<_LineArbitration>::onMessage;
};

template <typename CodePolicy, typename _LineArbitration = NoopLineArbitration>
class OMDDInstrumentProcessor : public OMDDProcessor<_LineArbitration>
{
public:
    static const uint8_t OMDD_STOCK_INDEX = 7;

    struct CommodityDef
    {
        uint16_t commodityCode; // key
        std::string underlyingCode; // underlying code (?)
        uint8_t underlyingType;     // 1=stock, 2=currency, ... 7=stockIndex
        std::string commodityID;    // HKATS code
    };
    struct ClassKey
    {
        uint8_t country;
        uint8_t market;
        uint8_t instrumentGroup;
        uint16_t commodityCode;

        friend bool operator<(ClassKey const& lhs, ClassKey const& rhs)
        {
            return std::tie(lhs.country, lhs.market, lhs.instrumentGroup, lhs.commodityCode)
                < std::tie(rhs.country, rhs.market, rhs.instrumentGroup, rhs.commodityCode);
        }
    };

    struct ClassDef
    {
        int32_t priceQuotationFactor;
        uint32_t contractSize;
        uint16_t decimalInStrike;
        uint16_t decimalInContractSize;
        uint16_t decimalInPremium;
        std::string baseCurrency;
        int32_t tickSize;
    };
    struct SeriesDef
    {
        // SDB
        uint32_t orderbookID;   // key
        std::string symbol;
        uint8_t financialProduct;
        uint16_t numOfDecimalsInPrice;
        int32_t baseStrike;
        std::string expirationDate;
        uint8_t putOrCall; // 0=Undefined, 1=Call, 2=Put

        // SDE
        ClassKey ck;
        uint8_t modifier;
        uint16_t expirationDateN;
        int32_t strikePrice;
        int64_t contractSize;
        std::string effectiveExpDate;
    };

    OMDDInstrumentProcessor() : _instrumentGroupMap{ {4, "Future"}, {6, "Option"}, {7, "Option"}, {22, "Option"}, {23, "Option"}, {254, "FX"} }
    {
        for (int32_t i = 201; i <= 223; ++i)
        {
            _instrumentGroupMap.emplace(i, "Future");
        }
    }
    void onMessage(omdd::sbe::CommodityDefinition const& cd, uint32_t seqNum)
    {
        std::string underlyingCode = cd.getUnderlyingCodeAsString();
        trim(underlyingCode);
        std::string commodityID = cd.getCommodityIDAsString();
        trim(commodityID);
        CommodityDef c{ cd.commodityCode(), underlyingCode, cd.underlyingType(), commodityID };
        _commodityDefs.emplace(cd.commodityCode(), c);
    }
    void onMessage(omdd::sbe::ClassDefinition const& cd, uint32_t seqNum)
    {
        std::string baseCurrency = cd.getBaseCurrencyAsString();
        trim(baseCurrency);
        ClassKey key{ cd.country(), cd.market(), cd.instrumentGroup(), cd.commodityCode() };
        ClassDef classDef{ cd.priceQuotationFactor(), cd.contractSize(), cd.decimalInStrikePrice(), cd.decimalInContractSize(), cd.decimalInPremium(), baseCurrency, cd.tickStepSize() };
        _classDefs.emplace( key, classDef );
    }
    void onMessage(omdd::sbe::SeriesDefinitionBase const& sdb, uint32_t seqNum)
    {
        if (sdb.orderbookID() == 0)
        {
            return;
        }
        std::string symbol = sdb.getSymbolAsString();
        trim(symbol);
        std::string expStr = sdb.getExpirationDateAsString();
        trim(expStr);
        
        auto ePos = _seriesDefs.emplace(sdb.orderbookID(), SeriesDef{ sdb.orderbookID() });
        SeriesDef& series = ePos.first->second;
        series.symbol = symbol;
        series.financialProduct = sdb.financialProduct();
        series.numOfDecimalsInPrice = sdb.numberOfDecimalsPrice();
        series.baseStrike = sdb.strikePrice();
        series.expirationDate = expStr;
        series.putOrCall = sdb.putOrCall();
    }
    void onMessage(omdd::sbe::SeriesDefinitionExtended const& sde, uint32_t seqNum)
    {
        if (sde.orderbookID() == 0)
        {
            return;
        }
        std::string symbol = sde.getSymbolAsString();
        trim(symbol);
        std::string expStr = sde.getEffectiveExpDateAsString();
        trim(expStr);
        auto ePos = _seriesDefs.emplace(sde.orderbookID(), SeriesDef{ sde.orderbookID() });
        SeriesDef& series = ePos.first->second;
        series.symbol = symbol;
        series.ck.country = sde.country();
        series.ck.market = sde.market();
        series.ck.instrumentGroup = sde.instrumentGroup();
        series.ck.commodityCode = sde.commodityCode();
        series.expirationDateN = sde.expirationDate();
        series.strikePrice = sde.strikePrice();
        series.contractSize = sde.contractSize();
        series.effectiveExpDate = expStr;

    }
    void onMessage(omdd::sbe::CombinationDefinition& combDef, uint32_t seqNum)
    {
    }
    using OMDDProcessor<_LineArbitration>::onMessage;

    void dump() const
    {
        using namespace std;
        //for_each(_seriesDefs.begin(), _seriesDefs.end(), [&](auto const& p) {
        for (auto p = _seriesDefs.begin(); p != _seriesDefs.end(); ++p)
        {
            auto const& s = p->second;
            auto commPos = _commodityDefs.find(s.ck.commodityCode);
            if (commPos == _commodityDefs.end())
            {
                cout << s.symbol << " commodity not found " << s.ck.commodityCode << endl;
                continue;
            }
            auto const& comm = commPos->second;
            auto clsPos = _classDefs.find(s.ck);
            if (clsPos == _classDefs.end())
            {
                cout << s.symbol << " class not found " << s.ck.market << " " << s.ck.instrumentGroup << " " << s.ck.commodityCode << endl;
                continue;
            }
            auto const& clsDef = clsPos->second;
            // consistence check
            if (s.numOfDecimalsInPrice != clsDef.decimalInPremium || s.baseStrike != s.strikePrice || s.expirationDate != s.effectiveExpDate)
            {
                cout << s.symbol << " " << s.orderbookID << " inconsistence: dp=" << s.numOfDecimalsInPrice << " vs " << clsDef.decimalInPremium << " strike=" << s.baseStrike << " vs " << s.strikePrice << " exp=" << s.expirationDate << " vs " << s.effectiveExpDate << endl;
            }
            double strike = ((double)s.strikePrice) / pow(10, clsDef.decimalInStrike);
            auto groupPos = _instrumentGroupMap.find(s.ck.instrumentGroup);
            if (groupPos == _instrumentGroupMap.end())
            {
                cout << s.symbol << " unsupported instrumentGroup " << s.ck.instrumentGroup << endl;
                continue;
            }

            int32_t unitValue = 1;
            if (comm.underlyingType == OMDD_STOCK_INDEX)
            {
                unitValue = clsDef.priceQuotationFactor;
            }

            cout << s.symbol << ","
                << CodePolicy::code(s.ck.country, s.ck.market, s.ck.instrumentGroup, s.modifier, s.ck.commodityCode, s.expirationDateN, s.strikePrice) << ","
                << s.symbol << ","
                << groupPos->second << ","
                << clsDef.baseCurrency << ","
                << "XHKF" << ","
                << 1 << ","
                << "XHKF-" << clsDef.tickSize << ","
                << unitValue;
        }
    }

private:
    std::map<uint32_t, std::string> _instrumentGroupMap;
    std::map<uint16_t, CommodityDef> _commodityDefs;
    std::map<ClassKey, ClassDef> _classDefs;
    std::map<uint32_t, SeriesDef> _seriesDefs;
};
}
