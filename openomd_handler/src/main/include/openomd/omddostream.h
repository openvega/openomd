#pragma once
#include <ostream>
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

namespace omdd
{
namespace sbe
{
inline std::ostream& operator<<(std::ostream& os, AddOrder const& m)
{
    os << "ao ob=" << m.orderbookID() << " oid=" << m.orderID() << " px=" << m.price() << " qty=" << m.quantity() << " s=" << m.side() << " t=" << m.lotType() << " ot=" << m.orderType() << " obp=" << m.orderBookPosition();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, AggregateOrderBookUpdate const& cm)
{
    auto &m = const_cast<AggregateOrderBookUpdate&>(cm);
    os << "aob ob=" << m.orderbookID() << std::endl;
    auto& en = m.noEntries();
    while (en.hasNext())
    {
        en.next();
        os << " " << en.side() << " l=" << (int16_t)en.priceLevel() << " a=" << (int16_t)en.updateAction() << " " << en.aggregateQuantity() << "@" << en.price() << "(" << en.numberOfOrders() << ")" << std::endl;
    }
    return os;
}
inline std::ostream& operator<<(std::ostream& os, CalculatedOpeningPrice const& m)
{
    os << "cop ob=" << m.orderbookID() << " cop=" << m.calculatedOpeningPrice() << " q=" << m.quantity();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, ClassDefinition const& m)
{
    os << "cld cty=" << (int16_t)m.country() << " mkt=" << (int16_t)m.market() << " ig=" << (int16_t)m.instrumentGroup() << " m=" << (int16_t)m.modifier() << " cc=" << m.commodityCode() << " pqf=" << m.priceQuotationFactor() << " cs=" << m.contractSize() << " dsp=" << m.decimalInStrikePrice() << " dcs=" << m.decimalInContractSize()
            << " dp=" << m.decimalInPremium() << " rt=" << m.rankingType() << " tb=" << (uint16_t)m.tradable() << " pu=" << (uint16_t)m.premiumUnit4Price() << " bc=" << m.getBaseCurrencyAsString() << " icid=" << m.getInstrumentClassIDAsString() << " icn=" << m.getInstrumentClassNameAsString() << " if=" << m.isFractions() << " sc=" << m.getSettlementCurrencyIDAsString() << " et=" << (uint16_t)m.effectiveTomorrow() << " tss=" << m.tickStepSize();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, CombinationDefinition const& m)
{
    os << "cbd cob=" << m.comboOrderbookID() << " lob=" << m.legOrderbookID() << " ls=" << m.legSide() << " lr=" << m.legRatio();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, CommodityDefinition const& m)
{
    os << "cmd cc=" << m.commodityCode() << " dup=" << m.decimalInUnderlyingPrice() << " isin=" << m.getIsinCodeAsString() << " bc=" << m.getBaseCurrencyAsString() << " upu=" << (int16_t)m.underlyingPriceUnit() << " cn=" << m.getCommodityNameAsString() << " nv=" << m.nominalValue() << " uc=" << m.getUnderlyingCodeAsString() << " ut=" << (int16_t)m.underlyingType() << "et=" << (uint16_t)m.effectiveTomorrow() << " cid=" << m.getCommodityIDAsString();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, CommodityStatus const& m)
{
    os <<"cms cc=" << m.commodityCode() << " ss=" << m.suspended() << " lk=" << (uint16_t)m.locked();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, DeleteOrder const& m)
{
    os <<"do ob=" << m.orderbookID() << " oid=" << m.orderID() << " s=" << (int16_t)m.side();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, DisasterRecoverySignal const& m)
{
    os <<"drs drs=" << m.drStatus();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, EstimatedAverageSettlementPrice const& m)
{
    os <<"eas et=" << m.easType() << " ic=" << m.getInstrumentCodeAsString() << " eas=" << m.eas();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, ImpliedVolatility const& m)
{
    os <<"iv ob=" << m.orderbookID() << " iv=" << m.impliedVolatility();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, LogonResponse const& m)
{
    os <<"lrs ss=" << m.sessionStatus();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, MarketAlert const& m)
{
    os <<"mka aid=" << m.alertID() << " s=" << m.source() << " header=" << m.getHeaderAsString();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, MarketStatus const& m)
{
    os <<"mks sl=" << m.stateLevel() << " mkt=" << (uint16_t)m.market() << " inst=" << (uint16_t)m.instrument() << " ob=" << m.orderbookID() << " cc=" << m.commodityCode() << " asd=" << m.actualStartDate() << " ast=" << m.actualStartTime() << " psd=" << m.plannedStartDate() << " pst=" << m.plannedStartTime() << " ssc=" << m.secondsToStateChange() << " s=" << m.state() << " p=" << (uint16_t)m.priority();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, ModifyOrder const& m)
{
    os <<"mo ob=" << m.orderbookID() << " oid=" << m.orderID() << " p=" << m.price() << " qty=" << m.quantity() << " s=" << (uint16_t)m.side() << " ot=" << m.orderType() << " obp=" << m.orderBookPosition();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, OpenInterest const& m)
{
    os <<"oi di=" << m.dayIndicator() << " ob=" << m.orderbookID() << " st=" << m.settlement() << " dc=" << m.dealCount() << " gOI=" << m.grossOI() << " nOI=" << m.netOI() << " to=" << m.turnover();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, OrderbookClear const& m)
{
    os <<"obc ob=" << m.orderbookID();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, QuoteRequest const& m)
{
    os <<"qr ob=" << m.orderbookID() << " lot=" << m.numberOfLots() << " ba=" << (uint16_t)m.bidAskFlag();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, RefreshComplete const& m)
{
    os <<"rfc seq=" << m.lastSeqNum();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, RetransmissionResponse const& m)
{
    os <<"rrs cid=" << m.channelID() << " rs=" << m.retransStatus() << " bsn=" << m.beginSeqNum() << " esn=" << m.endSeqNum();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SequenceReset const& m)
{
    os <<"ser nsn=" << m.newSeqNo();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SeriesDefinitionBase const& m)
{
    os <<"sd ob=" << m.orderbookID() << " sym=" << m.getSymbolAsString() << " fp=" << (uint16_t)m.financialProduct() << " ndp=" << m.numberOfDecimalsPrice() << " nl=" << (uint16_t)m.numberOfLegs() << " sp=" << m.strikePrice() << " ed=" << m.getExpirationDateAsString() << " dis=" << m.decimalInStrikePrice() << " pc=" << (uint16_t)m.putOrCall();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SeriesDefinitionExtended const& m)
{
    os <<"sde ob=" << m.orderbookID() << " sym=" << m.getSymbolAsString() << " c=" << (uint16_t)m.country() << " mkt=" << (uint16_t)m.market() << " ig=" << (uint16_t)m.instrumentGroup() << " m=" << (uint16_t)m.modifier() << " cc=" << m.commodityCode() << " ed=" << m.expirationDate() << " sp=" << m.strikePrice() << " cs=" << m.contractSize() 
        << " ic=" << m.getIsinCodeAsString() << " ss=" << (uint16_t)m.seriesStatus() << " et=" << (uint16_t)m.effectiveTomorrow() << " pqf=" << m.priceQuotationFactor() << " pm=" << (uint16_t)m.priceMethod() << " exp=" << m.getEffectiveExpDateAsString() << " dlt=" << m.dateTimeLastTrading() << " dft=" << m.dateTimeFirstTrading();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SeriesStatistics const& m)
{
    os <<"sst ob=" << m.orderbookID() << " ss=" << (uint16_t)m.session() << " op=" << m.open() << " h=" << m.high() << " l=" << m.low() << " trv=" << m.tradeReportVolume() << " dc=" << m.dealCount() << " p=" << m.price() << " to="<< m.turnover();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SeriesStatus const& m)
{
    os <<"sss ob=" << m.orderbookID() << " si=" << (uint16_t)m.suspensionIndicator() << " ss=" << (uint16_t)m.seriesStatus();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, Trade const& m)
{
    os << "trd ob=" << m.orderbookID() << " oid=" << m.orderID() << " p=" << m.price() << " tid=" << m.tradeID() << " cgid=" << m.comboGroupID() << " sd=" << m.side() << " dt=" << m.dealType() << " tc=" << m.tradeCondition() << " di=" << m.dealInfo() << " qty=" << m.quantity() << " tt=" << m.tradeTime();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, TradeAmendment const& m)
{
    os <<"tam tid=" << m.tradeID() << " cgid=" << m.comboGroupID() << " p=" << m.price() << " qty=" << m.quantity() << " tt=" << m.tradeTime() << " ts=" << m.tradeState();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, TradeStatistics const& m)
{
    os <<"tst ob=" << m.orderbookID() << " p=" << m.price() << " ds=" << (uint16_t)m.dealSource() << " ss=" << (uint16_t)m.session() << " agq=" << m.aggregateQuantity() << " o=" << m.open() << " h=" << m.high() << " l=" << m.low() << " trv=" << m.tradeReportVolume() << " dc=" << m.dealCount() << " to=" << m.turnover();
    return os;
}
}
}
