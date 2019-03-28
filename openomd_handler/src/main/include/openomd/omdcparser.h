#pragma once
#include "openomd/omdbaseparser.h"
#include <omdc_sbe/AddOddLotOrder.h>
#include <omdc_sbe/AddOrder.h>
#include <omdc_sbe/AggregateOrderBookUpdate.h>
#include <omdc_sbe/BrokerQueue.h>
#include <omdc_sbe/ClosingPrice.h>
#include <omdc_sbe/CurrencyRate.h>
#include <omdc_sbe/DeleteOddLotOrder.h>
#include <omdc_sbe/DeleteOrder.h>
#include <omdc_sbe/DisasterRecoverySignal.h>
#include <omdc_sbe/Heartbeat.h>
#include <omdc_sbe/IndexData.h>
#include <omdc_sbe/IndexDefinition.h>
#include <omdc_sbe/IndicativeEquilibriumPrice.h>
#include <omdc_sbe/LiquidityProvider.h>
#include <omdc_sbe/Logon.h>
#include <omdc_sbe/LogonResponse.h>
#include <omdc_sbe/MarketDefinition.h>
#include <omdc_sbe/MarketTurnover.h>
#include <omdc_sbe/ModifyOrder.h>
#include <omdc_sbe/News.h>
#include <omdc_sbe/NominalPrice.h>
#include <omdc_sbe/OrderImbalance.h>
#include <omdc_sbe/ReferencePrice.h>
#include <omdc_sbe/RefreshComplete.h>
#include <omdc_sbe/RetransmissionReq.h>
#include <omdc_sbe/RetransmissionResp.h>
#include <omdc_sbe/SecurityDefinition.h>
#include <omdc_sbe/SecurityStatus.h>
#include <omdc_sbe/SequenceReset.h>
#include <omdc_sbe/Statistics.h>
#include <omdc_sbe/StockConnectDailyQuotaBalance.h>
#include <omdc_sbe/StockConnectMarketTurnover.h>
#include <omdc_sbe/Trade.h>
#include <omdc_sbe/TradeCancel.h>
#include <omdc_sbe/TradeTicker.h>
#include <omdc_sbe/TradingSessionStatus.h>
#include <omdc_sbe/VCMTrigger.h>
#include <omdc_sbe/Yield.h>

namespace openomd
{
class OmdcParser : public OmdBaseParser
{
#ifndef _OMDC_MSG_SWITCH_
#define _OMDC_MSG_SWITCH_ OMD_SWITCH_CASE(AddOddLotOrder, 33); \
    OMD_SWITCH_CASE(AddOrder, 30); \
    OMD_SWITCH_CASE(AggregateOrderBookUpdate, 53); \
    OMD_SWITCH_CASE(BrokerQueue, 54); \
    OMD_SWITCH_CASE(ClosingPrice, 62); \
    OMD_SWITCH_CASE(CurrencyRate, 14); \
    OMD_SWITCH_CASE(DeleteOddLotOrder, 34); \
    OMD_SWITCH_CASE(DeleteOrder, 32); \
    OMD_SWITCH_CASE(DisasterRecoverySignal, 105); \
    OMD_SWITCH_CASE(IndexData, 71); \
    OMD_SWITCH_CASE(IndexDefinition, 70); \
    OMD_SWITCH_CASE(IndicativeEquilibriumPrice, 41); \
    OMD_SWITCH_CASE(LiquidityProvider, 13); \
    OMD_SWITCH_CASE(LogonResponse, 102); \
    OMD_SWITCH_CASE(MarketDefinition, 10); \
    OMD_SWITCH_CASE(MarketTurnover, 61); \
    OMD_SWITCH_CASE(ModifyOrder, 31); \
    OMD_SWITCH_CASE(News, 22); \
    OMD_SWITCH_CASE(NominalPrice, 40); \
    OMD_SWITCH_CASE(OrderImbalance, 56); \
    OMD_SWITCH_CASE(ReferencePrice, 43); \
    OMD_SWITCH_CASE(RefreshComplete, 203); \
    OMD_SWITCH_CASE(RetransmissionResp, 202); \
    OMD_SWITCH_CASE(SecurityDefinition, 11); \
    OMD_SWITCH_CASE(SecurityStatus, 21); \
    OMD_SWITCH_CASE(SequenceReset, 100); \
    OMD_SWITCH_CASE(Statistics, 60); \
    OMD_SWITCH_CASE(StockConnectDailyQuotaBalance, 80); \
    OMD_SWITCH_CASE(StockConnectMarketTurnover, 81); \
    OMD_SWITCH_CASE(Trade, 50); \
    OMD_SWITCH_CASE(TradeCancel, 51); \
    OMD_SWITCH_CASE(TradeTicker, 52); \
    OMD_SWITCH_CASE(TradingSessionStatus, 20); \
    OMD_SWITCH_CASE(VCMTrigger, 23); \
    OMD_SWITCH_CASE(Yield, 44); \
default: \
    processor.onUnknownMessage(type, msgSize); \
    break;
#endif

public:
    template <typename _Processor>
    static void parse(char* data, size_t bytesRecvd, _Processor& processor)
    {
        using namespace omdc::sbe;
        parseHelper(data, bytesRecvd, processor, 
            [](uint16_t type, char* pos, uint16_t msgSize, _Processor& processor, uint32_t seqNum) {
            switch (type)
            {
                _OMDC_MSG_SWITCH_
            }
        });
    }

    template <typename _Processor>
    static void parseRefresh(char* data, size_t bytesRecvd, _Processor& processor)
    {
        using namespace omdc::sbe;
        parseRefreshHelper(data, bytesRecvd, processor,
            [](uint16_t type, char* pos, uint16_t msgSize, _Processor& processor, uint32_t seqNum) {
            switch (type)
            {
                _OMDC_MSG_SWITCH_
            }
        });
    }

    template <typename _Processor>
    static void processCachedMsg(_Processor& processor)
    {
        using namespace omdc::sbe;
        processCachedMsgHelper(processor,
            [](uint16_t type, char* pos, uint16_t msgSize, _Processor& processor, uint32_t seqNum) {
            switch (type)
            {
                _OMDC_MSG_SWITCH_
            }
        });
    }
};
}
