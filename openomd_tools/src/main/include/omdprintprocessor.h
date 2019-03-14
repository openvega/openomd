#pragma once
#include <set>
#include "openomd/omdcparser.h"
#include "openomd/omddparser.h"
#include "openomd/omdcostream.h"
#include "openomd/omddostream.h"

namespace openomd
{
template <typename _LineArbitration>
class BasePrintProcessor : public _LineArbitration
{
public:
    using _LineArbitration::_LineArbitration;

    //BasePrintProcessor(std::set<int32_t> const& msgIds);

    void onUnknownMessage(uint16_t type, uint16_t msgSize)
    {
        std::cout << "PrintProcessor onUnknownMessage type=" << type << " msgSize=" << msgSize << std::endl;
    }

    void onError(std::exception const& ex)
    {
        std::cout << "PrintProcessor onError " << ex.what() << std::endl;
    }
protected:
    
    template <typename _Msg>
    void onPrintMessage(_Msg const& m, uint32_t seqNum)
    {
        //if (_msgIds.find(_Msg::sbeTemplateId()) != _msgIds.end() || _msgIds.find(0) != _msgIds.end())
        {
            std::cout << seqNum << " " << m << std::endl;
        }
    }
    std::set<int32_t> _msgIds;
};

template <typename _LineArbitration>
class OmdcPrintProcessor : public BasePrintProcessor<_LineArbitration>
{
public:
    using Base = BasePrintProcessor<_LineArbitration>;
    using Base::BasePrintProcessor;
    using Base::onPrintMessage;

    void onMessage(omdc::sbe::AddOddLotOrder const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::AddOrder const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::AggregateOrderBookUpdate& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::BrokerQueue const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::ClosingPrice const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::CurrencyRate const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::DeleteOddLotOrder const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::DeleteOrder const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::DisasterRecoverySignal const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::IndexData const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::IndexDefinition const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::IndicativeEquilibriumPrice const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::LiquidityProvider const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::Logon const& m, uint32_t s) { }
    void onMessage(omdc::sbe::LogonResponse const& m, uint32_t s) { }
    void onMessage(omdc::sbe::MarketDefinition const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::MarketTurnover const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::ModifyOrder const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::News const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::NominalPrice const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::OrderImbalance const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::ReferencePrice const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::RefreshComplete const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::RetransmissionReq const& m, uint32_t s) { }
    void onMessage(omdc::sbe::RetransmissionResp const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::SecurityDefinition const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::SecurityStatus const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::SequenceReset const& m, uint32_t s) { onPrintMessage(m, s); Base::resetSeqNum(m.newSeqNo()); }
    void onMessage(omdc::sbe::Statistics const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::StockConnectDailyQuotaBalance const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::StockConnectMarketTurnover const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::Trade const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::TradeCancel const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::TradeTicker const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::TradingSessionStatus const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::VCMTrigger const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdc::sbe::Yield const& m, uint32_t s) { onPrintMessage(m, s); }
};

template <typename _LineArbitration>
class OmddPrintProcessor : public BasePrintProcessor<_LineArbitration>
{
public:
    using Base = BasePrintProcessor<_LineArbitration>;
    using Base::BasePrintProcessor;
    using Base::onPrintMessage;

    void onMessage(omdd::sbe::AddOrder const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::AggregateOrderBookUpdate& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::CalculatedOpeningPrice const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::ClassDefinition const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::CombinationDefinition const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::CommodityDefinition const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::CommodityStatus const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::DeleteOrder const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::DisasterRecoverySignal const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::EstimatedAverageSettlementPrice const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::ImpliedVolatility const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::LogonResponse const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::MarketAlert const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::ModifyOrder const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::OpenInterest const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::OrderbookClear const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::QuoteRequest const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::RefreshComplete const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::RetransmissionResponse const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::SequenceReset const& m, uint32_t s) { onPrintMessage(m, s); Base::resetSeqNum(m.newSeqNo());}
    void onMessage(omdd::sbe::SeriesDefinitionBase const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::SeriesDefinitionExtended const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::SeriesStatistics const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::SeriesStatus const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::Trade const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::TradeAmendment const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::TradeStatistics const& m, uint32_t s) { onPrintMessage(m, s); }
    void onMessage(omdd::sbe::MarketStatus const& m, uint32_t s) { onPrintMessage(m, s); }
};
}
