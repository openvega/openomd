#pragma once
#include <ostream>
#include <omdcc_sbe/DisasterRecoverySignal.h>
#include <omdcc_sbe/MarketDefinition.h>
#include <omdcc_sbe/RefreshComplete.h>
#include <omdcc_sbe/SecurityDefinition.h>
#include <omdcc_sbe/SecurityStatus.h>
#include <omdcc_sbe/SequenceReset.h>
#include <omdcc_sbe/Statistics.h>
#include <omdcc_sbe/TopOfBook.h>

namespace omdcc
{
namespace sbe
{
inline std::ostream& operator<<(std::ostream& os, DisasterRecoverySignal const& m)
{
    os << "dr";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, MarketDefinition const& m)
{
    os << "md c=" << m.marketCode() << " cur=" << m.currencyCode() << " num=" << m.numberOfSecurities();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, RefreshComplete const& m)
{
    os << "rc";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SecurityDefinition const& m)
{
    os << "sd s=" << m.securityCode() << " m=" << m.marketCode() << " t=" << m.instrumentType() << " cur=" << m.currencyCode() << " l=" << m.lotSize() << " ss=" << m.shortSellFlag();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SecurityStatus const& m)
{
    os << "ss: " << m.securityCode() << " Sts=" << (int32_t)m.securityTradingStatus() << " tpc=" << m.tradingPhaseCode();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, SequenceReset const& m)
{
    os << "sr: " << m.newSeqNo();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, Statistics const& m)
{
    os << "st: " << m.securityCode() ;
    return os;
}
inline std::ostream& operator<<(std::ostream& os, TopOfBook const& m)
{
    os << "tob: " << m.securityCode() << " bQ=" << m.aggregateBidQuantity() << " aQ=" << m.aggregateAskQuantity() << " b=" << m.bidPrice() << " a=" << m.askPrice();
    return os;
}
}
}