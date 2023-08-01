#pragma once
#include <ostream>
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

namespace omdc
{
namespace sbe
{
inline std::ostream& operator<<(std::ostream& os, const AddOrder& m)
{
    os << "ao s=" << m.securityCode() << " id=" << m.orderID() << " " << m.side() << " " << m.quantity() << "@" << m.price() << " t=" << m.orderType() << " p=" << m.orderBookPosition();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, const ModifyOrder& m)
{
    os << "mo s=" << m.securityCode() << " id=" << m.orderID() << " " << m.side() << " " << m.quantity() << " p=" << m.orderBookPosition();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, const DeleteOrder& m)
{
    os << "do s=" << m.securityCode() << " id=" << m.orderID() << " s=" << m.side();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, AggregateOrderBookUpdate const& cm)
{
    auto & m = const_cast<AggregateOrderBookUpdate&>(cm);
    os << "aob s=" << m.securityCode() << std::endl;
    auto& en = m.noEntries();
    while (en.hasNext())
    {
        en.next();
        os << " " << en.side() << " l=" << (int16_t)en.priceLevel() << " a=" << (int16_t)en.updateAction() << " " << en.aggregateQuantity() << "@" << en.price() << "(" << en.numberOfOrders() << ")" << std::endl;
    }
    return os;
}
inline std::ostream& operator<<(std::ostream& os, AddOddLotOrder const& m)
{
    os << "aoo";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, BrokerQueue const& m)
{
    auto& bq = const_cast<BrokerQueue&>(m);
    auto& items = bq.items();
    os << "bq " << bq.securityCode() << " side:" << items.side();
    while (items.hasNext())
    {
        items.next();
        os << (items.itemType() == 'S' ? " S:" : " ") << items.item();
    }
    return os;
}
inline std::ostream& operator<<(std::ostream& os, ClosingPrice const& m)
{
    os << "cp";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, CurrencyRate const& m)
{
    os << "cr " << m.currencyCode() << " f:" << m.currencyFactor() << " r:" << m.currencyRate();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, DeleteOddLotOrder const& m)
{
    os << "doo";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, DisasterRecoverySignal const& m)
{
    os << "dr";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, IndexData const& m)
{
    os << "id" << m.getIndexCodeAsString() << " v=" << m.indexValue() << " sts=" << m.indexStatus() << " o=" << m.openingValue() << " h=" << m.highValue() << " l=" << m.lowValue() << " eas=" << m.easValue() << " c=" << m.closingValue() << " pc=" << m.previousSesClose();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, IndexDefinition const& m)
{
    os << "idef";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, IndicativeEquilibriumPrice const& m)
{
    os << "iep " << m.securityCode() << " p=" << m.price() << " aQ=" << m.aggregateQuantity();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, LiquidityProvider const& m)
{
    os << "lp";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, LogonResponse const& m)
{
    os << "lr";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, MarketDefinition const& m)
{
    os << "md";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, MarketTurnover const& m)
{
    os << "mt";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, News const& m)
{
    os << "ns";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, NominalPrice const& m)
{
    os << "np";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, OrderImbalance const& m)
{
    os << "ob";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, ReferencePrice const& m)
{
    os << "rp";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, RefreshComplete const& m)
{
    os << "rc";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, RetransmissionResp const& m)
{
    os << "rr";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SecurityDefinition const& m)
{
    os << "sd";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SecurityStatus const& m)
{
    os << "ss: " << m.securityCode() << " Si=" << (int32_t)m.suspensionIndicator();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SequenceReset const& m)
{
    os << "sr";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, Statistics const& m)
{
    os << "st";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, StockConnectDailyQuotaBalance const& m)
{
    os << "scdb";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, StockConnectMarketTurnover const& m)
{
    os << "scmt";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, Trade const& m)
{
    os << "t";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, TradeCancel const& m)
{
    os << "tc";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, TradeTicker const& m)
{
    os << "tt";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, TradingSessionStatus const& m)
{
    os << "tss";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, VCMTrigger const& m)
{
    os << "vcm";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, Yield const& m)
{
    os << "y";
    return os;
}
}
}
