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

//std::ostream& operator<<(std::ostream& os, const & m)
//{
//    return os;
//}

namespace omdc
{
namespace sbe
{
inline std::ostream& operator<<(std::ostream& os, const AddOrder& m)
{
    os << "AddOrder s=" << m.securityCode() << " id=" << m.orderID() << " p=" << m.price() << " q=" << m.quantity() << " s=" << m.side() << " t=" << m.orderType() << " p=" << m.orderBookPosition();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, const ModifyOrder& m)
{
    os << "ModifyOrder s=" << m.securityCode() << " id=" << m.orderID() << " q=" << m.quantity() << " s=" << m.side() << " p=" << m.orderBookPosition();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, const DeleteOrder& m)
{
    os << "DeleteOrder s=" << m.securityCode() << " id=" << m.orderID() << " s=" << m.side();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, AggregateOrderBookUpdate& m)
{
    os << "AggOrderBook s=" << m.securityCode() << std::endl;
    auto& en = m.noEntries();
    while (en.hasNext())
    {
        en.next();
        os << " s=" << en.side() << " l=" << (int16_t)en.priceLevel() << " a=" << (int16_t)en.updateAction() << " " << en.aggregateQuantity() << "@" << en.price() << "(" << en.numberOfOrders() << ")" << std::endl;
    }
    return os;
}
}
}
