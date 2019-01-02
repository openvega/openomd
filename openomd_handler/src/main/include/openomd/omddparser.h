#pragma once
#include "openomd/omdbaseparser.h"
#include <omdd_sbe/AddOrder.h>
#include <omdd_sbe/AggregateOrderBookUpdate.h>
#include <omdd_sbe/CalculatedOpeningPrice.h>
#include <omdd_sbe/ClassDefinition.h>
#include <omdd_sbe/CombinationDefinition.h>
#include <omdd_sbe/CommodityDefinition.h>
#include <omdd_sbe/CommodityStatus.h>
#include <omdd_sbe/DeleteOrder.h>
#include <omdd_sbe/DisasterRecoverySignal.h>
#include <omdd_sbe/EstimatedAverageSettlementPrice.h>
#include <omdd_sbe/ImpliedVolatility.h>
#include <omdd_sbe/LogonResponse.h>
#include <omdd_sbe/MarketAlert.h>
#include <omdd_sbe/MarketStatus.h>
#include <omdd_sbe/ModifyOrder.h>
#include <omdd_sbe/OpenInterest.h>
#include <omdd_sbe/OrderbookClear.h>
#include <omdd_sbe/QuoteRequest.h>
#include <omdd_sbe/RefreshComplete.h>
#include <omdd_sbe/RetransmissionResponse.h>
#include <omdd_sbe/SequenceReset.h>
#include <omdd_sbe/SeriesDefinitionBase.h>
#include <omdd_sbe/SeriesDefinitionExtended.h>
#include <omdd_sbe/SeriesStatistics.h>
#include <omdd_sbe/SeriesStatus.h>
#include <omdd_sbe/Trade.h>
#include <omdd_sbe/TradeAmendment.h>
#include <omdd_sbe/TradeStatistics.h>


namespace openomd
{
class OmddParser : public OmdBaseParser
{
public:
    template <typename _Callback>
    static void parse(char* data, size_t bytesRecvd, _Callback& callback, int32_t partition)
    {
        using namespace omdd::sbe;
        parseHelper(data, bytesRecvd, callback, partition,
            [](uint16_t type, char* pos, uint16_t msgSize, _Callback& callback, int32_t partition) {
            switch (type)
            {
                OMD_SWITCH_CASE(AddOrder);
                OMD_SWITCH_CASE(AggregateOrderBookUpdate);
                OMD_SWITCH_CASE(CalculatedOpeningPrice);
                OMD_SWITCH_CASE(ClassDefinition);
                OMD_SWITCH_CASE(CombinationDefinition);
                OMD_SWITCH_CASE(CommodityDefinition);
                OMD_SWITCH_CASE(CommodityStatus);
                OMD_SWITCH_CASE(DeleteOrder);
                OMD_SWITCH_CASE(DisasterRecoverySignal);
                OMD_SWITCH_CASE(EstimatedAverageSettlementPrice);
                OMD_SWITCH_CASE(ImpliedVolatility);
                OMD_SWITCH_CASE(LogonResponse);
                OMD_SWITCH_CASE(MarketAlert);
                OMD_SWITCH_CASE(ModifyOrder);
                OMD_SWITCH_CASE(OpenInterest);
                OMD_SWITCH_CASE(OrderbookClear);
                OMD_SWITCH_CASE(QuoteRequest);
                OMD_SWITCH_CASE(RefreshComplete);
                OMD_SWITCH_CASE(RetransmissionResponse);
                OMD_SWITCH_CASE(SequenceReset);
                OMD_SWITCH_CASE(SeriesDefinitionBase);
                OMD_SWITCH_CASE(SeriesDefinitionExtended);
                OMD_SWITCH_CASE(SeriesStatistics);
                OMD_SWITCH_CASE(SeriesStatus);
                OMD_SWITCH_CASE(Trade);
                OMD_SWITCH_CASE(TradeAmendment);
                OMD_SWITCH_CASE(TradeStatistics);
            default:
                callback.onUnknownMessage(type, msgSize);
                break;
            }
        });
    }
};
}