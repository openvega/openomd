#pragma once
#include "openomd/omdparser.h"

namespace openomd
{
template <typename _LineArbitration, typename _BaseProcessor>
class OMDProcessor : public _LineArbitration, public _BaseProcessor
{
public:
    using _LineArbitration::_LineArbitration;

    ONMESSAGE(omdc::sbe::AddOddLotOrder)
    ONMESSAGE(omdc::sbe::AddOrder)
    ONMESSAGE(omdc::sbe::AggregateOrderBookUpdate)
    ONMESSAGE(omdc::sbe::BrokerQueue)
    ONMESSAGE(omdc::sbe::ClosingPrice)
    ONMESSAGE(omdc::sbe::CurrencyRate)
    ONMESSAGE(omdc::sbe::DeleteOddLotOrder)
    ONMESSAGE(omdc::sbe::DeleteOrder)
    ONMESSAGE(omdc::sbe::DisasterRecoverySignal)
    ONMESSAGE(omdc::sbe::IndexData)
    ONMESSAGE(omdc::sbe::IndexDefinition)
    ONMESSAGE(omdc::sbe::IndicativeEquilibriumPrice)
    ONMESSAGE(omdc::sbe::LiquidityProvider)
    ONMESSAGE(omdc::sbe::Logon)
    ONMESSAGE(omdc::sbe::LogonResponse)
    ONMESSAGE(omdc::sbe::MarketDefinition)
    ONMESSAGE(omdc::sbe::MarketTurnover)
    ONMESSAGE(omdc::sbe::ModifyOrder)
    ONMESSAGE(omdc::sbe::News)
    ONMESSAGE(omdc::sbe::NominalPrice)
    ONMESSAGE(omdc::sbe::OrderImbalance)
    ONMESSAGE(omdc::sbe::ReferencePrice)
    ONMESSAGE(omdc::sbe::RefreshComplete)
    ONMESSAGE(omdc::sbe::RetransmissionReq)
    ONMESSAGE(omdc::sbe::RetransmissionResp)
    ONMESSAGE(omdc::sbe::SecurityDefinition)
    ONMESSAGE(omdc::sbe::SecurityStatus)
    ONMESSAGE(omdc::sbe::SequenceReset)
    ONMESSAGE(omdc::sbe::Statistics)
    ONMESSAGE(omdc::sbe::StockConnectDailyQuotaBalance)
    ONMESSAGE(omdc::sbe::StockConnectMarketTurnover)
    ONMESSAGE(omdc::sbe::Trade)
    ONMESSAGE(omdc::sbe::TradeCancel)
    ONMESSAGE(omdc::sbe::TradeTicker)
    ONMESSAGE(omdc::sbe::TradingSessionStatus)
    ONMESSAGE(omdc::sbe::VCMTrigger)
    ONMESSAGE(omdc::sbe::Yield)
    ONMESSAGE(omdd::sbe::AddOrder)
    ONMESSAGE(omdd::sbe::AggregateOrderBookUpdate)
    ONMESSAGE(omdd::sbe::CalculatedOpeningPrice)
    ONMESSAGE(omdd::sbe::ClassDefinition)
    ONMESSAGE(omdd::sbe::CombinationDefinition)
    ONMESSAGE(omdd::sbe::CommodityDefinition)
    ONMESSAGE(omdd::sbe::CommodityStatus)
    ONMESSAGE(omdd::sbe::DeleteOrder)
    ONMESSAGE(omdd::sbe::DisasterRecoverySignal)
    ONMESSAGE(omdd::sbe::EstimatedAverageSettlementPrice)
    ONMESSAGE(omdd::sbe::ImpliedVolatility)
    ONMESSAGE(omdd::sbe::LogonResponse)
    ONMESSAGE(omdd::sbe::MarketAlert)
    ONMESSAGE(omdd::sbe::ModifyOrder)
    ONMESSAGE(omdd::sbe::OpenInterest)
    ONMESSAGE(omdd::sbe::OrderbookClear)
    ONMESSAGE(omdd::sbe::QuoteRequest)
    ONMESSAGE(omdd::sbe::RefreshComplete)
    ONMESSAGE(omdd::sbe::RetransmissionResponse)
    ONMESSAGE(omdd::sbe::SequenceReset)
    ONMESSAGE(omdd::sbe::SeriesDefinitionBase)
    ONMESSAGE(omdd::sbe::SeriesDefinitionExtended)
    ONMESSAGE(omdd::sbe::SeriesStatistics)
    ONMESSAGE(omdd::sbe::SeriesStatus)
    ONMESSAGE(omdd::sbe::Trade)
    ONMESSAGE(omdd::sbe::TradeAmendment)
    ONMESSAGE(omdd::sbe::TradeStatistics)
    ONMESSAGE(omdd::sbe::MarketStatus)
    void onHeartbeat()
    {
    }
    void onUnknownMessage(uint16_t, uint16_t)
    {
    }
    
};
}
