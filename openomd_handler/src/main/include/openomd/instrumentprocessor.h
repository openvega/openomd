#pragma once
#include <sstream>
#include "openomd/nooplinearbitration.h"
#include "openomd/omdcprocessor.h"
#include "openomd/omddprocessor.h"

namespace openomd
{
template <typename TranslatePolicy, typename _BaseProcessor, typename _LineArbitration = NoopLineArbitration>
class OMDCInstrumentProcessor : public OMDCProcessor<_LineArbitration, _BaseProcessor>, protected TranslatePolicy
{
public:
    OMDCInstrumentProcessor(std::ostream& ostream)
        : _ostream{ostream}
        , _instrumentTypes{
            {1, TranslatePolicy::Equity},
            {2, TranslatePolicy::Equity},
            {6, TranslatePolicy::Equity},
            {7, TranslatePolicy::Equity},
            {12, TranslatePolicy::Equity},
            {13, TranslatePolicy::Warrant},
            {3, TranslatePolicy::Warrant},
            {14, TranslatePolicy::Warrant},
            {11, TranslatePolicy::Cbbc},
            {4, TranslatePolicy::Equity},
            {5, TranslatePolicy::ETF},
            {8, TranslatePolicy::Equity},
            {9, TranslatePolicy::Equity},
            {10, TranslatePolicy::Equity},
            {99, TranslatePolicy::Equity}}
        , _indexMap{ {"0000100",TranslatePolicy::HSI}, {"0001400", TranslatePolicy::HSCEI}}
    {
    }
    void onMessage(omdc::sbe::IndexDefinition const& indexDef, uint32_t seqNum)
    {
        std::string indexCode = indexDef.getIndexCodeAsString();
        trim(indexCode);
        auto pos = _indexMap.find(indexCode);
        if (pos != _indexMap.end())
        {
            std::string currency = indexDef.getCurrencyCodeAsString();
            std::stringstream ss;
            TranslatePolicy::write(ss, pos->second, "", pos->second, TranslatePolicy::Index.first, "", 0, "HKD", "XHKG", 1, "XHKG",
                    1, 1, "", "", "", "", "", "", 0, "", "", "", 0, 0, 0, 0, 0, 0);
            _secDefs.emplace(TranslatePolicy::Index.second, ss.str());
        }
    }
    void onMessage(omdc::sbe::MarketDefinition const& mktDef, uint32_t seqNum)
    {
    }
    void onMessage(omdc::sbe::SecurityDefinition& s, uint32_t seqNum)
    {
        using namespace std;
        auto pos = _instrumentTypes.find(s.productType());
        if (pos == _instrumentTypes.end())
        {
            std::stringstream ss;
            ss << s.securityCode() << " unsupported instrumentType " << (int32_t)s.productType();
            _BaseProcessor::warn(ss.str());
            return;
        }

        std::string& secType = pos->second.first;
        int32_t ordering = pos->second.second;
        std::string shortname = s.getSecurityShortNameAsString();
        trim(shortname);
        std::string currency = s.getCurrencyCodeAsString();
        trim(currency);
        std::string underlying;
        std::string underlyingExchange;
        std::string optionClass;
        double strike = 0;
        double strike2 = 0;
        double callPrice = 0;
        std::string optionType;
        std::string exerciseStyle;
        std::string payoffStyle = "S";
        int64_t mNum = 0;
        int64_t mDenom = 1;
        uint32_t maturity = 0;
        std::string issuer;

        if (secType == TranslatePolicy::Warrant.first || secType == TranslatePolicy::Cbbc.first)
        {
            strike = (double)s.strikePrice1() / 1000;
            strike2 = (double)s.strikePrice2() / 1000;
            if (secType == TranslatePolicy::Cbbc.first)
            {
                callPrice  = (double)s.callPrice() / pow(10, s.decimalsInCallPrice());
            }
            if (s.callPutFlag() == 'C')
            {
                optionType = TranslatePolicy::Call;
            }
            if (s.callPutFlag() == 'P')
            {
                optionType = TranslatePolicy::Put;
            }
            if (s.style() == 'A')
            {
                exerciseStyle=TranslatePolicy::American;
            }
            if (s.style() == 'E')
            {
                exerciseStyle=TranslatePolicy::European;
            }
            if (s.conversionRatio() > 0)
            {
                mNum = s.conversionRatio();
                mDenom = 1000;
            }
            if (s.noWarrantsPerEntitlement() != s.conversionRatio()/1000 || s.conversionRatio() == 0)
            {
                if (s.entitlement() > 0)
                {
                    // TODO: whats the rule for warrant entitlement
                    //mNum = s.noWarrantsPerEntitlement();
                    //mDenom = s.entitlement()/pow(10, s.decimalsInEntitlement());
                }
            }

            auto& underlyings = s.noUnderlyingSecurities();
            if (underlyings.hasNext())
            {
                underlyings.next();
                if (underlyings.underlyingSecurityCode() > 0)
                {
                    std::stringstream ss;
                    ss << underlyings.underlyingSecurityCode();
                    underlying = ss.str();
                    underlyingExchange = "XHKG";
                    if (!underlying.empty() && secType == TranslatePolicy::Warrant.first)
                    {
                        payoffStyle = "P";
                    }
                }
            } else
            {
                // HSI/HSCEI ?
                if (secType == TranslatePolicy::Warrant.first)
                {
                    underlying = shortname.substr(2, 5);
                    if (!underlying.empty() && underlying[0]=='-')
                    {
                        underlying = underlying.substr(1,4);
                    }
                } else if (secType == TranslatePolicy::Cbbc.first)
                {
                    auto cbbcPos = shortname.find('#');
                    if (cbbcPos != std::string::npos)
                    {
                        underlying = shortname.substr(shortname.find('#')+1, 5);
                    }
                }
                trim(underlying);
                underlyingExchange = "XHKG";
            }
            maturity = s.maturityDate();
            issuer = shortname.substr(0, 2);
        }

        std::stringstream ss;
        TranslatePolicy::write(ss, s.securityCode(), s.securityCode(), shortname, secType, "MAIN", 1, currency, "XHKG", s.lotSize(), "XHKG", 1, 1, issuer,
            underlying, underlyingExchange, s.listingDate(), maturity, "", strike, optionType, exerciseStyle, payoffStyle, mNum, mDenom, 1, 1, callPrice, strike2);
        _secDefs.emplace(ordering, ss.str());
    }
    void onMessage(omdc::sbe::LiquidityProvider const& lp, uint32_t seqNum)
    {
    }
    using OMDCProcessor<_LineArbitration, _BaseProcessor>::onMessage;
    void dump()
    {
        for (auto &pos : _secDefs)
        {
            _ostream << pos.second << std::endl;
        }
    }

private:
    std::ostream& _ostream;
    std::map<uint8_t, std::pair<std::string, int32_t>> _instrumentTypes; // product type to secType and order
    std::map<std::string, std::string> _indexMap;
    std::multimap<int32_t, std::string> _secDefs;
};

template <typename TranslatePolicy, typename _BaseProcessor, typename _LineArbitration = NoopLineArbitration>
class OMDDInstrumentProcessor : public OMDDProcessor<_LineArbitration, _BaseProcessor>, protected TranslatePolicy
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
        uint8_t effectiveTomorrow;
        int32_t priceQuotationFactor;
        std::string effectiveExpDate;
    };

    OMDDInstrumentProcessor(std::ostream& ostream)
        : _ostream{ostream}
        , _instrumentGroupMap{ {4, TranslatePolicy::Future}, {6, TranslatePolicy::Option}, {7, TranslatePolicy::Option}, {22, TranslatePolicy::Option}, {23, TranslatePolicy::Option}, {254, TranslatePolicy::FX} }
    {
        for (int32_t i = 201; i <= 223; ++i)
        {
            _instrumentGroupMap.emplace(i, TranslatePolicy::Future);
        }
    }

    static bool isOption(uint8_t instrumentGroup)
    {
        if (instrumentGroup == 6 || instrumentGroup == 7 || instrumentGroup == 22 || instrumentGroup == 23)
        {
            return true;
        }
        return false;
    }

    static bool isAmerican(uint8_t instrumentGroup)
    {
        if (instrumentGroup == 6 || instrumentGroup == 7)
        {
            return true;
        }
        return false;
    }

    static bool isEuropean(uint8_t instrumentGroup)
    {
        if (instrumentGroup == 22 || instrumentGroup == 23)
        {
            return true;
        }
        return false;
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
        series.effectiveTomorrow = sde.effectiveTomorrow();
        series.priceQuotationFactor = sde.priceQuotationFactor();
        series.effectiveExpDate = expStr;
    }
    void onMessage(omdd::sbe::CombinationDefinition& combDef, uint32_t seqNum)
    {
    }
    using OMDDProcessor<_LineArbitration, _BaseProcessor>::onMessage;

    void dump() const
    {
        using namespace std;
        //for_each(_seriesDefs.begin(), _seriesDefs.end(), [&](auto const& p) {
        for (auto p = _seriesDefs.begin(); p != _seriesDefs.end(); ++p)
        {
            auto const& s = p->second;
            if (s.effectiveTomorrow == 1)
            {
                continue;
            }
            auto commPos = _commodityDefs.find(s.ck.commodityCode);
            if (commPos == _commodityDefs.end())
            {
                std::stringstream ss;
                ss << s.symbol << " commodity not found " << (int32_t)s.ck.market << " " << (int32_t)s.ck.instrumentGroup << " " << s.ck.commodityCode;
                _BaseProcessor::warn(ss.str());
                continue;
            }
            auto const& comm = commPos->second;
            auto clsPos = _classDefs.find(s.ck);
            if (clsPos == _classDefs.end())
            {
                std::stringstream ss;
                ss << s.symbol << " class not found " << s.ck.market << " " << s.ck.instrumentGroup << " " << s.ck.commodityCode;
                _BaseProcessor::warn(ss.str());
                continue;
            }
            auto const& clsDef = clsPos->second;
            auto groupPos = _instrumentGroupMap.find(s.ck.instrumentGroup);
            if (groupPos == _instrumentGroupMap.end())
            {
                std::stringstream ss;
                ss << s.symbol << " unsupported instrumentGroup " << (int32_t)s.ck.instrumentGroup;
                _BaseProcessor::warn(ss.str());
                continue;
            }

            int32_t unitValue = 1;
            if (comm.underlyingType == OMDD_STOCK_INDEX)
            {
                if (s.priceQuotationFactor > 0)
                {
                    unitValue = ((double)s.priceQuotationFactor) / pow(10, clsDef.decimalInContractSize);
                }
                else
                {
                    unitValue = ((double)clsDef.priceQuotationFactor) / pow(10, clsDef.decimalInContractSize);
                }
            }

            std::string underlyingStr = comm.underlyingCode;
            if (!underlyingStr.empty())
            {
                try
                {
                    int32_t underlyingCode = stol(comm.underlyingCode);
                    std::stringstream ss;
                    ss << underlyingCode;
                    underlyingStr = ss.str();
                } catch (std::invalid_argument const&)
                {
                    // try replace HSE with HSCEI
                    if (underlyingStr == "HSE")
                    {
                        underlyingStr =TranslatePolicy::HSCEI;
                    }
                }
            }

            std::string optionClass;
            double strike = 0;
            std::string optionType;
            std::string exerciseStyle;
            int64_t csNum = 0;
            int64_t csDenom = 0;
            std::stringstream tickRule;
            double tickStep = (double)clsDef.tickSize / pow(10, clsDef.decimalInPremium);
            tickRule << "XHKF-" << tickStep;
            std::string listingDate;

            if (isOption(s.ck.instrumentGroup))
            {
                optionClass = comm.commodityID;
                strike = ((double)s.strikePrice) / pow(10, clsDef.decimalInStrike);
                if (s.putOrCall == 1)
                {
                    optionType = TranslatePolicy::Call;
                } else if (s.putOrCall == 2)
                {
                    optionType = TranslatePolicy::Put;
                }
                if (isAmerican(s.ck.instrumentGroup))
                {
                    exerciseStyle=TranslatePolicy::American;
                }
                if (isEuropean(s.ck.instrumentGroup))
                {
                    exerciseStyle=TranslatePolicy::European;
                }
                csNum = s.contractSize > 0 ? s.contractSize : clsDef.contractSize;
                csDenom = pow(10, clsDef.decimalInContractSize);
            }
            TranslatePolicy::write(_ostream, s.symbol, TranslatePolicy::code(s.ck.country, s.ck.market, s.ck.instrumentGroup, s.modifier, s.ck.commodityCode, s.expirationDateN, s.strikePrice),
                s.symbol, groupPos->second, "", 0, clsDef.baseCurrency, "XHKF", 1, tickRule.str(), unitValue, pow(10, clsDef.decimalInPremium), "",
                underlyingStr, "XHKG", listingDate, (s.effectiveExpDate.empty() ? s.expirationDate : s.effectiveExpDate), optionClass, strike, optionType, exerciseStyle, "S", 1, 1, csNum, csDenom, 0, 0);
            _ostream << endl;
        }
    }

private:
    std::ostream& _ostream;
    std::map<uint32_t, std::string> _instrumentGroupMap;
    std::map<uint16_t, CommodityDef> _commodityDefs;
    std::map<ClassKey, ClassDef> _classDefs;
    std::map<uint32_t, SeriesDef> _seriesDefs;
};
}
