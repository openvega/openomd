#include <algorithm>
#include <iostream>
#include "openomd/omdcostream.h"
#include "omdprintprocessor.h"

namespace openomd
{
using namespace std;

BasePrintProcessor::BasePrintProcessor(std::set<int32_t> const& msgIds)
    :_msgIds{msgIds}
{
}

void BasePrintProcessor::onUnknownMessage(uint16_t type, uint16_t msgSize)
{
    cout << "PrintProcessor onUnknownMessage type=" << type << " msgSize=" << msgSize << endl;
}

void BasePrintProcessor::onError(std::exception const& ex)
{
    cout << "PrintProcessor onError " << ex.what() << endl;
}

void OmdcPrintProcessor::onMessage(omdc::sbe::AddOddLotOrder const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {
    });
}

void OmdcPrintProcessor::onMessage(omdc::sbe::AddOrder const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [&](auto const& m) { 
        cout << partition << ":" << seqNum << " " << m << endl;
    });
}

void OmdcPrintProcessor::onMessage(omdc::sbe::AggregateOrderBookUpdate& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [&](auto& m) {
        cout << partition << ":" << seqNum << " " << m;
    });
}

void OmdcPrintProcessor::onMessage(omdc::sbe::BrokerQueue const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::ClosingPrice const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::CurrencyRate const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::DeleteOddLotOrder const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::DeleteOrder const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [&](auto const& m) {
        cout << partition << ":" << seqNum << " " << m << endl;
    });
}

void OmdcPrintProcessor::onMessage(omdc::sbe::DisasterRecoverySignal const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::IndexData const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::IndexDefinition const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::IndicativeEquilibriumPrice const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::LiquidityProvider const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::Logon const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::LogonResponse const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::MarketDefinition const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::MarketTurnover const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::ModifyOrder const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [&](auto const& m) {
        cout << partition << ":" << seqNum << " " << m << endl;
    });
}

void OmdcPrintProcessor::onMessage(omdc::sbe::News const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::NominalPrice const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::OrderImbalance const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::ReferencePrice const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::RefreshComplete const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::RetransmissionReq const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::RetransmissionResp const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::SecurityDefinition const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::SecurityStatus const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::SequenceReset const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::Statistics const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::StockConnectDailyQuotaBalance const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::StockConnectMarketTurnover const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::Trade const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::TradeCancel const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::TradeTicker const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::TradingSessionStatus const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::VCMTrigger const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmdcPrintProcessor::onMessage(omdc::sbe::Yield const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::AddOrder const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::AggregateOrderBookUpdate& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::CalculatedOpeningPrice const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::ClassDefinition const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::CombinationDefinition const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::CommodityDefinition const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::CommodityStatus const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::DeleteOrder const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::DisasterRecoverySignal const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::EstimatedAverageSettlementPrice const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::ImpliedVolatility const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::LogonResponse const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::MarketAlert const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::ModifyOrder const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::OpenInterest const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::OrderbookClear const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::QuoteRequest const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::RefreshComplete const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::RetransmissionResponse const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::SequenceReset const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::SeriesDefinitionBase const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::SeriesDefinitionExtended const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::SeriesStatistics const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::SeriesStatus const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::Trade const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::TradeAmendment const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

void OmddPrintProcessor::onMessage(omdd::sbe::TradeStatistics const& m, int32_t partition, uint32_t seqNum)
{
    onPrintMessage(m, [](auto const& m) {});
}

}