#pragma once
#include "openomd/omddparser.h"
#include "openomd/omddef.h"

namespace openomd
{
template <typename _LineArbitration>
class OMDDProcessor : public _LineArbitration, public BaseProcessor
{
public:
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
    void onError(std::exception const& ex)
    {
        _LineArbitration::error(ex.what());
    }
};
}