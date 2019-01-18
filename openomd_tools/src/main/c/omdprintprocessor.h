#pragma once
#include <set>
#include "openomd/omdcparser.h"
#include "openomd/omddparser.h"
#include "openomd/pcaputil.h"
#include "openomd/linearbitration.h"

namespace openomd
{
class BasePrintProcessor : public PcapLineArbitration
{
public:
    BasePrintProcessor(std::set<int32_t> const& msgIds);

    void onUnknownMessage(uint16_t, uint16_t);

    void onError(std::exception const& ex);
protected:
    template <typename _MSG, typename _F>
    void onPrintMessage(_MSG const& m, _F f)
    {
        if (_msgIds.find(_MSG::sbeTemplateId()) != _msgIds.end() || _msgIds.find(0) != _msgIds.end())
        {
            f(m);
        }
    }

    template <typename _MSG, typename _F>
    void onPrintMessage(_MSG& m, _F f)
    {
        if (_msgIds.find(_MSG::sbeTemplateId()) != _msgIds.end() || _msgIds.find(0) != _msgIds.end())
        {
            f(m);
        }
    }

    std::set<int32_t> _msgIds;
};

class OmdcPrintProcessor : public BasePrintProcessor
{
public:
    using BasePrintProcessor::BasePrintProcessor;

    void onMessage(omdc::sbe::AddOddLotOrder const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::AddOrder const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::AggregateOrderBookUpdate&, int32_t, uint32_t);
    void onMessage(omdc::sbe::BrokerQueue const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::ClosingPrice const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::CurrencyRate const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::DeleteOddLotOrder const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::DeleteOrder const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::DisasterRecoverySignal const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::IndexData const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::IndexDefinition const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::IndicativeEquilibriumPrice const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::LiquidityProvider const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::Logon const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::LogonResponse const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::MarketDefinition const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::MarketTurnover const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::ModifyOrder const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::News const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::NominalPrice const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::OrderImbalance const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::ReferencePrice const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::RefreshComplete const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::RetransmissionReq const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::RetransmissionResp const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::SecurityDefinition const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::SecurityStatus const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::SequenceReset const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::Statistics const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::StockConnectDailyQuotaBalance const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::StockConnectMarketTurnover const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::Trade const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::TradeCancel const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::TradeTicker const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::TradingSessionStatus const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::VCMTrigger const&, int32_t, uint32_t);
    void onMessage(omdc::sbe::Yield const&, int32_t, uint32_t);
};

class OmddPrintProcessor : public BasePrintProcessor
{
public:
    using BasePrintProcessor::BasePrintProcessor;

    void onMessage(omdd::sbe::AddOrder const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::AggregateOrderBookUpdate&, int32_t, uint32_t);
    void onMessage(omdd::sbe::CalculatedOpeningPrice const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::ClassDefinition const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::CombinationDefinition const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::CommodityDefinition const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::CommodityStatus const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::DeleteOrder const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::DisasterRecoverySignal const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::EstimatedAverageSettlementPrice const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::ImpliedVolatility const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::LogonResponse const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::MarketAlert const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::ModifyOrder const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::OpenInterest const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::OrderbookClear const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::QuoteRequest const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::RefreshComplete const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::RetransmissionResponse const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::SequenceReset const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::SeriesDefinitionBase const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::SeriesDefinitionExtended const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::SeriesStatistics const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::SeriesStatus const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::Trade const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::TradeAmendment const&, int32_t, uint32_t);
    void onMessage(omdd::sbe::TradeStatistics const&, int32_t, uint32_t);
};

template <typename _Processor, typename _Parser>
class OmdPcapRunner
{
public:
    struct Callback
    {
        _Processor& _processor;
        _Parser _parser;

        Callback(_Processor& processor) : _processor{ processor }
        {
        }

        void onReceive(int32_t byteRecvd, uint8_t* data, int32_t max, int32_t partition)
        {
            _parser.parse((char*)data, byteRecvd, _processor, partition);
        }
    };

    void run(std::string const& pcapFile, _Processor& processor)
    {
        Callback callback{ processor };
        openomd::PcapUtil<Callback> pcapUtil{ pcapFile, callback };
        pcapUtil.init();
        pcapUtil.start();
        pcapUtil.run();
        pcapUtil.stop();
    }
};
}