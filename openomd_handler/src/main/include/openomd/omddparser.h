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
#ifndef _OMDD_MSG_SWITCH_
#define _OMDD_MSG_SWITCH_ OMD_SWITCH_CASE(AddOrder, 330); \
    OMD_SWITCH_CASE(AggregateOrderBookUpdate, 353); \
    OMD_SWITCH_CASE(CalculatedOpeningPrice, 364); \
    OMD_SWITCH_CASE(ClassDefinition, 302); \
    OMD_SWITCH_CASE(CombinationDefinition, 305); \
    OMD_SWITCH_CASE(CommodityDefinition, 301); \
    OMD_SWITCH_CASE(CommodityStatus, 322); \
    OMD_SWITCH_CASE(DeleteOrder, 332); \
    OMD_SWITCH_CASE(DisasterRecoverySignal, 105); \
    OMD_SWITCH_CASE(EstimatedAverageSettlementPrice, 365); \
    OMD_SWITCH_CASE(ImpliedVolatility, 367); \
    OMD_SWITCH_CASE(LogonResponse, 102); \
    OMD_SWITCH_CASE(MarketAlert, 323); \
    OMD_SWITCH_CASE(ModifyOrder, 331); \
    OMD_SWITCH_CASE(OpenInterest, 366); \
    OMD_SWITCH_CASE(OrderbookClear, 335); \
    OMD_SWITCH_CASE(QuoteRequest, 336); \
    OMD_SWITCH_CASE(RefreshComplete, 203); \
    OMD_SWITCH_CASE(RetransmissionResponse, 202); \
    OMD_SWITCH_CASE(SequenceReset, 100); \
    OMD_SWITCH_CASE(SeriesDefinitionBase, 303); \
    OMD_SWITCH_CASE(SeriesDefinitionExtended, 304); \
    OMD_SWITCH_CASE(SeriesStatistics, 363); \
    OMD_SWITCH_CASE(SeriesStatus, 321); \
    OMD_SWITCH_CASE(Trade, 350); \
    OMD_SWITCH_CASE(TradeAmendment, 356); \
    OMD_SWITCH_CASE(TradeStatistics, 360); \
    OMD_SWITCH_CASE(MarketStatus, 320); \
default: \
    processor.onUnknownMessage(type, msgSize); \
    break;
#endif

public:
    template <typename _Processor>
    static void parse(char* data, size_t bytesRecvd, _Processor& processor)
    {
        using namespace omdd::sbe;        
        parseHelper(data, bytesRecvd, processor,
            [](uint16_t type, char* pos, uint16_t msgSize, _Processor& processor, uint32_t seqNum) {
            switch (type)
            {
                _OMDD_MSG_SWITCH_
            }
        });
    }

    template <typename _Processor>
    static void parseRefresh(char* data, size_t bytesRecvd, _Processor& processor)
    {
        using namespace omdd::sbe;
        parseRefreshHelper(data, bytesRecvd, processor,
            [](uint16_t type, char* pos, uint16_t msgSize, _Processor& processor, uint32_t seqNum) {
            switch (type)
            {
                _OMDD_MSG_SWITCH_
            }
        });
    }

    template <typename _Processor>
    static void processCachedMsg(_Processor& processor)
    {
        using namespace omdd::sbe;
        processCachedMsgHelper(processor,
            [](uint16_t type, char* pos, uint16_t msgSize, _Processor& processor, uint32_t seqNum) {
            switch (type)
            {
                _OMDD_MSG_SWITCH_
            }
        });
    }
};
}
