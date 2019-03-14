#pragma once
#include "openomd/omdcparser.h"
#include "openomd/omddef.h"

namespace openomd
{
template <typename _LineArbitration>
class OMDCProcessor : public _LineArbitration
{
public:
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
    void onUnknownMessage(uint16_t, uint16_t)
    {
    }
    void onError(std::exception const& ex)
    {
        printf("OMDCProcessor error %s\n", ex.what());
    }
};
}
