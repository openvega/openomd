#include <algorithm>
#include <iostream>
#include "openomd/omdcostream.h"
#include "omdprintprocessor.h"

namespace openomd
{
using namespace std;

//BasePrintProcessor::BasePrintProcessor(std::set<int32_t> const& msgIds)
//    :_msgIds{msgIds}
//{
//}

void BasePrintProcessor::onUnknownMessage(uint16_t type, uint16_t msgSize)
{
    cout << "PrintProcessor onUnknownMessage type=" << type << " msgSize=" << msgSize << endl;
}

void BasePrintProcessor::onError(std::exception const& ex)
{
    cout << "PrintProcessor onError " << ex.what() << endl;
}

void OmdcPrintProcessor::onMessage(omdc::sbe::AddOddLotOrder const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {
    });
}

void OmdcPrintProcessor::onMessage(omdc::sbe::AddOrder const& m, uint32_t seqNum)
{
    onPrintMessage(m, [&](auto const& m) { 
        cout << seqNum << " " << m << endl;
    });
}

void OmdcPrintProcessor::onMessage(omdc::sbe::AggregateOrderBookUpdate& m, uint32_t seqNum)
{
    onPrintMessage(m, [&](auto& m) {
        cout << seqNum << " " << m;
    });
}

void OmdcPrintProcessor::onMessage(omdc::sbe::BrokerQueue const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::ClosingPrice const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::CurrencyRate const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::DeleteOddLotOrder const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::DeleteOrder const& m, uint32_t seqNum)
{
    onPrintMessage(m, [&](auto const& m) {
        cout << seqNum << " " << m << endl;
    });
}

void OmdcPrintProcessor::onMessage(omdc::sbe::DisasterRecoverySignal const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::IndexData const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::IndexDefinition const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::IndicativeEquilibriumPrice const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::LiquidityProvider const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::Logon const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::LogonResponse const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::MarketDefinition const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::MarketTurnover const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::ModifyOrder const& m, uint32_t seqNum)
{
    onPrintMessage(m, [&](auto const& m) {
        cout << seqNum << " " << m << endl;
    });
}

void OmdcPrintProcessor::onMessage(omdc::sbe::News const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::NominalPrice const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::OrderImbalance const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::ReferencePrice const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::RefreshComplete const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::RetransmissionReq const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::RetransmissionResp const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::SecurityDefinition const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::SecurityStatus const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::SequenceReset const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::Statistics const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::StockConnectDailyQuotaBalance const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::StockConnectMarketTurnover const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::Trade const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::TradeCancel const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::TradeTicker const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::TradingSessionStatus const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::VCMTrigger const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::Yield const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::AddOrder const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::AggregateOrderBookUpdate& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::CalculatedOpeningPrice const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::ClassDefinition const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::CombinationDefinition const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::CommodityDefinition const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::CommodityStatus const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::DeleteOrder const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::DisasterRecoverySignal const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::EstimatedAverageSettlementPrice const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::ImpliedVolatility const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::LogonResponse const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::MarketAlert const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::ModifyOrder const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::OpenInterest const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::OrderbookClear const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::QuoteRequest const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::RefreshComplete const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::RetransmissionResponse const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::SequenceReset const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::SeriesDefinitionBase const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::SeriesDefinitionExtended const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::SeriesStatistics const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::SeriesStatus const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::Trade const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::TradeAmendment const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::TradeStatistics const& m, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

}