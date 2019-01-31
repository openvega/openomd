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
    return os;
}
inline std::ostream& operator<<(std::ostream& os, AggregateOrderBookUpdate const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, CalculatedOpeningPrice const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, ClassDefinition const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, CombinationDefinition const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, CommodityDefinition const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, CommodityStatus const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, DeleteOrder const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, DisasterRecoverySignal const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, EstimatedAverageSettlementPrice const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, ImpliedVolatility const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, LogonResponse const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, MarketAlert const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, MarketStatus const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, ModifyOrder const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, OpenInterest const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, OrderbookClear const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, QuoteRequest const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, RefreshComplete const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, RetransmissionResponse const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SequenceReset const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SeriesDefinitionBase const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SeriesDefinitionExtended const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SeriesStatistics const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SeriesStatus const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, Trade const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, TradeAmendment const& m)
{
    return os;
}
inline std::ostream& operator<<(std::ostream& os, TradeStatistics const& m)
{
    return os;
}
}
}