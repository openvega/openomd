#pragma once
#include "openomd/omdccparser.h"

namespace openomd
{
template <typename _LineArbitration, typename _BaseProcessor>
class OMDCCProcessor : public _LineArbitration, public _BaseProcessor
{
public:
    using _LineArbitration::_LineArbitration;

    ONMESSAGE(omdcc::sbe::DisasterRecoverySignal)
    ONMESSAGE(omdcc::sbe::Logon)
    ONMESSAGE(omdcc::sbe::LogonResponse)
    ONMESSAGE(omdcc::sbe::MarketDefinition)
    ONMESSAGE(omdcc::sbe::RefreshComplete)
    ONMESSAGE(omdcc::sbe::RetransmissionReq)
    ONMESSAGE(omdcc::sbe::RetransmissionResp)
    ONMESSAGE(omdcc::sbe::SecurityDefinition)
    ONMESSAGE(omdcc::sbe::SecurityStatus)
    ONMESSAGE(omdcc::sbe::SequenceReset)
    ONMESSAGE(omdcc::sbe::Statistics)
    ONMESSAGE(omdcc::sbe::TopOfBook)
    void onHeartbeat()
    {
    }
    void onUnknownMessage(uint16_t, uint16_t)
    {
    }
};
}