#pragma once
#include <map>
#include "openomd/omdcparser.h"
#include "openomd/omddparser.h"
#include "openomd/pcaputil.h"
#include "openomd/linearbitration.h"

namespace openomd
{
class BasePrintProcessor : public PcapLineArbitration
{
public:
    //BasePrintProcessor(std::set<int32_t> const& msgIds);

    void onUnknownMessage(uint16_t, uint16_t);

    void onError(std::exception const& ex);
protected:
    template <typename _MSG, typename _F>
    void onPrintMessage(_MSG const& m, _F f)
    {
//        if (_msgIds.find(_MSG::sbeTemplateId()) != _msgIds.end() || _msgIds.find(0) != _msgIds.end())
        {
            f(m);
        }
    }

    template <typename _MSG, typename _F>
    void onPrintMessage(_MSG& m, _F f)
    {
//        if (_msgIds.find(_MSG::sbeTemplateId()) != _msgIds.end() || _msgIds.find(0) != _msgIds.end())
        {
            f(m);
        }
    }

//    std::set<int32_t> _msgIds;
};

class OmdcPrintProcessor : public BasePrintProcessor
{
public:
    using BasePrintProcessor::BasePrintProcessor;

    void onMessage(omdc::sbe::AddOddLotOrder const&, uint32_t);
    void onMessage(omdc::sbe::AddOrder const&, uint32_t);
    void onMessage(omdc::sbe::AggregateOrderBookUpdate&, uint32_t);
    void onMessage(omdc::sbe::BrokerQueue const&, uint32_t);
    void onMessage(omdc::sbe::ClosingPrice const&, uint32_t);
    void onMessage(omdc::sbe::CurrencyRate const&, uint32_t);
    void onMessage(omdc::sbe::DeleteOddLotOrder const&, uint32_t);
    void onMessage(omdc::sbe::DeleteOrder const&, uint32_t);
    void onMessage(omdc::sbe::DisasterRecoverySignal const&, uint32_t);
    void onMessage(omdc::sbe::IndexData const&, uint32_t);
    void onMessage(omdc::sbe::IndexDefinition const&, uint32_t);
    void onMessage(omdc::sbe::IndicativeEquilibriumPrice const&, uint32_t);
    void onMessage(omdc::sbe::LiquidityProvider const&, uint32_t);
    void onMessage(omdc::sbe::Logon const&, uint32_t);
    void onMessage(omdc::sbe::LogonResponse const&, uint32_t);
    void onMessage(omdc::sbe::MarketDefinition const&, uint32_t);
    void onMessage(omdc::sbe::MarketTurnover const&, uint32_t);
    void onMessage(omdc::sbe::ModifyOrder const&, uint32_t);
    void onMessage(omdc::sbe::News const&, uint32_t);
    void onMessage(omdc::sbe::NominalPrice const&, uint32_t);
    void onMessage(omdc::sbe::OrderImbalance const&, uint32_t);
    void onMessage(omdc::sbe::ReferencePrice const&, uint32_t);
    void onMessage(omdc::sbe::RefreshComplete const&, uint32_t);
    void onMessage(omdc::sbe::RetransmissionReq const&, uint32_t);
    void onMessage(omdc::sbe::RetransmissionResp const&, uint32_t);
    void onMessage(omdc::sbe::SecurityDefinition const&, uint32_t);
    void onMessage(omdc::sbe::SecurityStatus const&, uint32_t);
    void onMessage(omdc::sbe::SequenceReset const&, uint32_t);
    void onMessage(omdc::sbe::Statistics const&, uint32_t);
    void onMessage(omdc::sbe::StockConnectDailyQuotaBalance const&, uint32_t);
    void onMessage(omdc::sbe::StockConnectMarketTurnover const&, uint32_t);
    void onMessage(omdc::sbe::Trade const&, uint32_t);
    void onMessage(omdc::sbe::TradeCancel const&, uint32_t);
    void onMessage(omdc::sbe::TradeTicker const&, uint32_t);
    void onMessage(omdc::sbe::TradingSessionStatus const&, uint32_t);
    void onMessage(omdc::sbe::VCMTrigger const&, uint32_t);
    void onMessage(omdc::sbe::Yield const&, uint32_t);
};

class OmddPrintProcessor : public BasePrintProcessor
{
public:
    using BasePrintProcessor::BasePrintProcessor;

    void onMessage(omdd::sbe::AddOrder const&, uint32_t);
    void onMessage(omdd::sbe::AggregateOrderBookUpdate&, uint32_t);
    void onMessage(omdd::sbe::CalculatedOpeningPrice const&, uint32_t);
    void onMessage(omdd::sbe::ClassDefinition const&, uint32_t);
    void onMessage(omdd::sbe::CombinationDefinition const&, uint32_t);
    void onMessage(omdd::sbe::CommodityDefinition const&, uint32_t);
    void onMessage(omdd::sbe::CommodityStatus const&, uint32_t);
    void onMessage(omdd::sbe::DeleteOrder const&, uint32_t);
    void onMessage(omdd::sbe::DisasterRecoverySignal const&, uint32_t);
    void onMessage(omdd::sbe::EstimatedAverageSettlementPrice const&, uint32_t);
    void onMessage(omdd::sbe::ImpliedVolatility const&, uint32_t);
    void onMessage(omdd::sbe::LogonResponse const&, uint32_t);
    void onMessage(omdd::sbe::MarketAlert const&, uint32_t);
    void onMessage(omdd::sbe::ModifyOrder const&, uint32_t);
    void onMessage(omdd::sbe::OpenInterest const&, uint32_t);
    void onMessage(omdd::sbe::OrderbookClear const&, uint32_t);
    void onMessage(omdd::sbe::QuoteRequest const&, uint32_t);
    void onMessage(omdd::sbe::RefreshComplete const&, uint32_t);
    void onMessage(omdd::sbe::RetransmissionResponse const&, uint32_t);
    void onMessage(omdd::sbe::SequenceReset const&, uint32_t);
    void onMessage(omdd::sbe::SeriesDefinitionBase const&, uint32_t);
    void onMessage(omdd::sbe::SeriesDefinitionExtended const&, uint32_t);
    void onMessage(omdd::sbe::SeriesStatistics const&, uint32_t);
    void onMessage(omdd::sbe::SeriesStatus const&, uint32_t);
    void onMessage(omdd::sbe::Trade const&, uint32_t);
    void onMessage(omdd::sbe::TradeAmendment const&, uint32_t);
    void onMessage(omdd::sbe::TradeStatistics const&, uint32_t);
};

struct ChannelConfig
{
    int32_t channel;
    uint32_t ipA;
    uint16_t portA;
    uint32_t ipB;
    uint16_t portB;
};

template <typename _Processor, typename _Parser>
class OmdPcapRunner
{
public:
    struct Callback
    {
        std::map<std::pair<uint32_t, uint16_t>, int32_t> _addressToChannel;
        std::map<int32_t, _Processor> _processors;
        _Parser _parser;

        Callback(std::vector<ChannelConfig> const& channelConfig)
        {
            for_each(channelConfig.begin(), channelConfig.end(), [&](ChannelConfig const& c) {
                _addressToChannel.emplace(std::make_pair(c.ipA, c.portA), c.channel);
                _addressToChannel.emplace(std::make_pair(c.ipB, c.portB), c.channel);
                _processors.emplace(c.channel, _Processor{});
            });
        }

        void onReceive(int32_t byteRecvd, uint8_t* data, int32_t max, uint32_t ip, uint16_t port)
        {
            auto pos = _addressToChannel.find({ ip, port });
            if (pos != _addressToChannel.end())
            {
                _parser.parse((char*)data, byteRecvd, _processors[pos->second]);
            }
        }
    };

    OmdPcapRunner(std::vector<ChannelConfig> const& channelConfig, std::string const& pcapFile)
        : _callback{channelConfig}, _pcapFile{pcapFile}
    {
    }

    void run()
    {
        openomd::PcapUtil<Callback> pcapUtil{ _pcapFile, _callback };
        pcapUtil.init();
        pcapUtil.start();
        pcapUtil.run();
        pcapUtil.stop();
    }

private:
    Callback _callback;
    std::string _pcapFile;
};
}