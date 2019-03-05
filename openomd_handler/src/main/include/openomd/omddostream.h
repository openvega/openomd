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
    os << "ao ob=" << m.orderBookID() << " oid=" << m.orderID() << " px=" << m.price() << " qty=" << m.quantity() << " s=" << m.side() << " t=" << m.lotType() << " ot=" << m.orderType() << " obp=" << m.orderBookPosition();
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
    os << "cld cty=" << (int16_t)m.country() << " mkt=" (int16_t)m.market() << " ig=" << (int16_t)m.instrumentGroup() << " m=" << (int16_t)m.modifier() << " cc=" << m.commodityCode() << " pqf=" << m.priceQuotationFactor() << " cs=" << m.contractSize() << " dsp=" << m.decimalInStrikePrice() << " dcs=" << m.decimalInContractSize()
            << " dp=" << m.decimalInPremium() << " rt=" << m.rankingType() << " tb=" << m.tradable() << " pu=" << m.premiumUnit4Price() << " bc=" << m.baseCurrency() << " icid=" << m.instrumentClassID() << " icn=" << m.instrumentClassName() << " if=" << m.isFractions() << " sc=" << m.settlementCurrencyID() << " et=" m.effectiveTomorrow() << " tss=" << m.tickStepSize();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, CombinationDefinition const& m)
{
    os << "cbd cob=" << m.comboOrderbookID() << " lob=" << m.legOrderbookID() << " ls=" m.legSize() << " lr=" << m.legRatio();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, CommodityDefinition const& m)
{
    os << "cmd";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, CommodityStatus const& m)
{
    os <<"cms";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, DeleteOrder const& m)
{
    os <<"do";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, DisasterRecoverySignal const& m)
{
    os <<"drs";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, EstimatedAverageSettlementPrice const& m)
{
    os <<"eas";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, ImpliedVolatility const& m)
{
    os <<"iv";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, LogonResponse const& m)
{
    os <<"lrs";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, MarketAlert const& m)
{
    os <<"mka";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, MarketStatus const& m)
{
    os <<"mks";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, ModifyOrder const& m)
{
    os <<"mo";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, OpenInterest const& m)
{
    os <<"oi";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, OrderbookClear const& m)
{
    os <<"obc";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, QuoteRequest const& m)
{
    os <<"qr";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, RefreshComplete const& m)
{
    os <<"rfc";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, RetransmissionResponse const& m)
{
    os <<"rrs";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SequenceReset const& m)
{
    os <<"ser";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SeriesDefinitionBase const& m)
{
    os <<"sd";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SeriesDefinitionExtended const& m)
{
    os <<"sde";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SeriesStatistics const& m)
{
    os <<"sst";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SeriesStatus const& m)
{
    os <<"sss";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, Trade const& m)
{
    os <<"trd";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, TradeAmendment const& m)
{
    os <<"tam";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, TradeStatistics const& m)
{
    os <<"tst";
    return os;
}
}
}
