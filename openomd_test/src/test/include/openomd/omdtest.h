#pragma once
#include "openomd/omdcparser.h"
#include "openomd/omddparser.h"
#include "openomd/nooplinearbitration.h"

namespace omdc
{
#define ONMESSAGE(_MSG) virtual void onMessage(_MSG const&, uint32_t){}
template <typename _LineArbitration = openomd::NoopLineArbitration>
class OMDCProcessor : public _LineArbitration
{
public:
    ONMESSAGE(sbe::AddOddLotOrder)
    ONMESSAGE(sbe::AddOrder)
    ONMESSAGE(sbe::AggregateOrderBookUpdate)
    ONMESSAGE(sbe::BrokerQueue)
    ONMESSAGE(sbe::ClosingPrice)
    ONMESSAGE(sbe::CurrencyRate)
    ONMESSAGE(sbe::DeleteOddLotOrder)
    ONMESSAGE(sbe::DeleteOrder)
    ONMESSAGE(sbe::DisasterRecoverySignal)
    ONMESSAGE(sbe::IndexData)
    ONMESSAGE(sbe::IndexDefinition)
    ONMESSAGE(sbe::IndicativeEquilibriumPrice)
    ONMESSAGE(sbe::LiquidityProvider)
    ONMESSAGE(sbe::Logon)
    ONMESSAGE(sbe::LogonResponse)
    ONMESSAGE(sbe::MarketDefinition)
    ONMESSAGE(sbe::MarketTurnover)
    ONMESSAGE(sbe::ModifyOrder)
    ONMESSAGE(sbe::News)
    ONMESSAGE(sbe::NominalPrice)
    ONMESSAGE(sbe::OrderImbalance)
    ONMESSAGE(sbe::ReferencePrice)
    ONMESSAGE(sbe::RefreshComplete)
    ONMESSAGE(sbe::RetransmissionReq)
    ONMESSAGE(sbe::RetransmissionResp)
    ONMESSAGE(sbe::SecurityDefinition)
    ONMESSAGE(sbe::SecurityStatus)
    ONMESSAGE(sbe::SequenceReset)
    ONMESSAGE(sbe::Statistics)
    ONMESSAGE(sbe::StockConnectDailyQuotaBalance)
    ONMESSAGE(sbe::StockConnectMarketTurnover)
    ONMESSAGE(sbe::Trade)
    ONMESSAGE(sbe::TradeCancel)
    ONMESSAGE(sbe::TradeTicker)
    ONMESSAGE(sbe::TradingSessionStatus)
    ONMESSAGE(sbe::VCMTrigger)
    ONMESSAGE(sbe::Yield)
    void onUnknownMessage(uint16_t, uint16_t)
    {
    }
    void onError(std::exception const& ex)
    {
        printf("OMDCProcessor error %s\n", ex.what());
    }
};
}

namespace omdd
{
class OMDDProcessor : public openomd::NoopLineArbitration
{
public:
    ONMESSAGE(sbe::AddOrder)
    ONMESSAGE(sbe::AggregateOrderBookUpdate)
    ONMESSAGE(sbe::CalculatedOpeningPrice)
    ONMESSAGE(sbe::ClassDefinition)
    ONMESSAGE(sbe::CombinationDefinition)
    ONMESSAGE(sbe::CommodityDefinition)
    ONMESSAGE(sbe::CommodityStatus)
    ONMESSAGE(sbe::DeleteOrder)
    ONMESSAGE(sbe::DisasterRecoverySignal)
    ONMESSAGE(sbe::EstimatedAverageSettlementPrice)
    ONMESSAGE(sbe::ImpliedVolatility)
    ONMESSAGE(sbe::LogonResponse)
    ONMESSAGE(sbe::MarketAlert)
    ONMESSAGE(sbe::ModifyOrder)
    ONMESSAGE(sbe::OpenInterest)
    ONMESSAGE(sbe::OrderbookClear)
    ONMESSAGE(sbe::QuoteRequest)
    ONMESSAGE(sbe::RefreshComplete)
    ONMESSAGE(sbe::RetransmissionResponse)
    ONMESSAGE(sbe::SequenceReset)
    ONMESSAGE(sbe::SeriesDefinitionBase)
    ONMESSAGE(sbe::SeriesDefinitionExtended)
    ONMESSAGE(sbe::SeriesStatistics)
    ONMESSAGE(sbe::SeriesStatus)
    ONMESSAGE(sbe::Trade)
    ONMESSAGE(sbe::TradeAmendment)
    ONMESSAGE(sbe::TradeStatistics)
    ONMESSAGE(sbe::MarketStatus)
    void onUnknownMessage(uint16_t, uint16_t)
    {
    }
    void onError(std::exception const& ex)
    {
        printf("OMDDProcessor error %s\n", ex.what());
    }
};
}
