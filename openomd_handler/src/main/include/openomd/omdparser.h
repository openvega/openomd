#pragma once
#include "openomd/omdbaseparser.h"
#include "openomd/compressionpolicy.h"
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
class OmdParser : public OmdBaseParser<ZLibCompressionPolicy>
{
#ifndef _OMDCOMDD_MSG_SWITCH_
#define _OMDCOMDD_MSG_SWITCH_ OMD_SWITCH_CASE(omdc::sbe::AddOddLotOrder, 33); \
    OMD_SWITCH_CASE(omdc::sbe::AddOrder, 30); \
    OMD_SWITCH_CASE(omdc::sbe::AggregateOrderBookUpdate, 53); \
    OMD_SWITCH_CASE(omdc::sbe::BrokerQueue, 54); \
    OMD_SWITCH_CASE(omdc::sbe::ClosingPrice, 62); \
    OMD_SWITCH_CASE(omdc::sbe::CurrencyRate, 14); \
    OMD_SWITCH_CASE(omdc::sbe::DeleteOddLotOrder, 34); \
    OMD_SWITCH_CASE(omdc::sbe::DeleteOrder, 32); \
    OMD_SWITCH_CASE(omdc::sbe::DisasterRecoverySignal, 105); \
    OMD_SWITCH_CASE(omdc::sbe::IndexData, 71); \
    OMD_SWITCH_CASE(omdc::sbe::IndexDefinition, 70); \
    OMD_SWITCH_CASE(omdc::sbe::IndicativeEquilibriumPrice, 41); \
    OMD_SWITCH_CASE(omdc::sbe::LiquidityProvider, 13); \
    OMD_SWITCH_CASE(omdc::sbe::LogonResponse, 102); \
    OMD_SWITCH_CASE(omdc::sbe::MarketDefinition, 10); \
    OMD_SWITCH_CASE(omdc::sbe::MarketTurnover, 61); \
    OMD_SWITCH_CASE(omdc::sbe::ModifyOrder, 31); \
    OMD_SWITCH_CASE(omdc::sbe::News, 22); \
    OMD_SWITCH_CASE(omdc::sbe::NominalPrice, 40); \
    OMD_SWITCH_CASE(omdc::sbe::OrderImbalance, 56); \
    OMD_SWITCH_CASE(omdc::sbe::ReferencePrice, 43); \
    OMD_SWITCH_CASE(omdc::sbe::RefreshComplete, 203); \
    OMD_SWITCH_CASE(omdc::sbe::RetransmissionResp, 202); \
    OMD_SWITCH_CASE(omdc::sbe::SecurityDefinition, 11); \
    OMD_SWITCH_CASE(omdc::sbe::SecurityStatus, 21); \
    OMD_SWITCH_CASE(omdc::sbe::SequenceReset, 100); \
    OMD_SWITCH_CASE(omdc::sbe::Statistics, 60); \
    OMD_SWITCH_CASE(omdc::sbe::StockConnectDailyQuotaBalance, 80); \
    OMD_SWITCH_CASE(omdc::sbe::StockConnectMarketTurnover, 81); \
    OMD_SWITCH_CASE(omdc::sbe::Trade, 50); \
    OMD_SWITCH_CASE(omdc::sbe::TradeCancel, 51); \
    OMD_SWITCH_CASE(omdc::sbe::TradeTicker, 52); \
    OMD_SWITCH_CASE(omdc::sbe::TradingSessionStatus, 20); \
    OMD_SWITCH_CASE(omdc::sbe::VCMTrigger, 23); \
    OMD_SWITCH_CASE(omdc::sbe::Yield, 44); \
    OMD_SWITCH_CASE(omdd::sbe::AddOrder, 330); \
    OMD_SWITCH_CASE(omdd::sbe::AggregateOrderBookUpdate, 353); \
    OMD_SWITCH_CASE(omdd::sbe::CalculatedOpeningPrice, 364); \
    OMD_SWITCH_CASE(omdd::sbe::ClassDefinition, 302); \
    OMD_SWITCH_CASE(omdd::sbe::CombinationDefinition, 305); \
    OMD_SWITCH_CASE(omdd::sbe::CommodityDefinition, 301); \
    OMD_SWITCH_CASE(omdd::sbe::CommodityStatus, 322); \
    OMD_SWITCH_CASE(omdd::sbe::DeleteOrder, 332); \
    OMD_SWITCH_CASE(omdd::sbe::EstimatedAverageSettlementPrice, 365); \
    OMD_SWITCH_CASE(omdd::sbe::ImpliedVolatility, 367); \
    OMD_SWITCH_CASE(omdd::sbe::MarketAlert, 323); \
    OMD_SWITCH_CASE(omdd::sbe::ModifyOrder, 331); \
    OMD_SWITCH_CASE(omdd::sbe::OpenInterest, 366); \
    OMD_SWITCH_CASE(omdd::sbe::OrderbookClear, 335); \
    OMD_SWITCH_CASE(omdd::sbe::QuoteRequest, 336); \
    OMD_SWITCH_CASE(omdd::sbe::SeriesDefinitionBase, 303); \
    OMD_SWITCH_CASE(omdd::sbe::SeriesDefinitionExtended, 304); \
    OMD_SWITCH_CASE(omdd::sbe::SeriesStatistics, 363); \
    OMD_SWITCH_CASE(omdd::sbe::SeriesStatus, 321); \
    OMD_SWITCH_CASE(omdd::sbe::Trade, 350); \
    OMD_SWITCH_CASE(omdd::sbe::TradeAmendment, 356); \
    OMD_SWITCH_CASE(omdd::sbe::TradeStatistics, 360); \
    OMD_SWITCH_CASE(omdd::sbe::MarketStatus, 320); \
default: \
    processor.onUnknownMessage(type, msgSize); \
    break;
#endif

public:
    template <typename _Processor>
    static void parse(char* data, size_t bytesRecvd, _Processor& processor)
    {
        parseHelper(data, bytesRecvd, processor, 
            [](uint16_t type, char* pos, uint16_t msgSize, _Processor& processor, uint32_t seqNum) {
            switch (type)
            {
                _OMDCOMDD_MSG_SWITCH_
            }
        });
    }

    template <typename _Processor>
    static void parseRefresh(char* data, size_t bytesRecvd, _Processor& processor)
    {
        parseRefreshHelper(data, bytesRecvd, processor,
            [](uint16_t type, char* pos, uint16_t msgSize, _Processor& processor, uint32_t seqNum) {
            switch (type)
            {
                _OMDCOMDD_MSG_SWITCH_
            }
        });
    }

    template <typename _Processor>
    static void processCachedMsg(_Processor& processor)
    {
        processCachedMsgHelper(processor,
            [](uint16_t type, char* pos, uint16_t msgSize, _Processor& processor, uint32_t seqNum) {
            switch (type)
            {
                _OMDCOMDD_MSG_SWITCH_
            }
        });
    }
};
}
