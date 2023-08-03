#pragma once
#include "openomd/omdbaseparser.h"
#include "openomd/compressionpolicy.h"
#include <omdcc_sbe/DisasterRecoverySignal.h>
#include <omdcc_sbe/Heartbeat.h>
#include <omdcc_sbe/Logon.h>
#include <omdcc_sbe/LogonResponse.h>
#include <omdcc_sbe/MarketDefinition.h>
#include <omdcc_sbe/RefreshComplete.h>
#include <omdcc_sbe/RetransmissionReq.h>
#include <omdcc_sbe/RetransmissionResp.h>
#include <omdcc_sbe/SecurityDefinition.h>
#include <omdcc_sbe/SecurityStatus.h>
#include <omdcc_sbe/SequenceReset.h>
#include <omdcc_sbe/Statistics.h>
#include <omdcc_sbe/TopOfBook.h>

namespace openomd
{
class OmdccParser : public OmdBaseParser<NoopCompressionPolicy>
{
#ifndef _OMDCC_MSG_SWITCH_
#define _OMDCC_MSG_SWITCH_ OMD_SWITCH_CASE(DisasterRecoverySignal, 105); \
    OMD_SWITCH_CASE(Logon, 101); \
    OMD_SWITCH_CASE(LogonResponse, 102); \
    OMD_SWITCH_CASE(MarketDefinition, 610); \
    OMD_SWITCH_CASE(RefreshComplete, 203); \
    OMD_SWITCH_CASE(RetransmissionReq, 201); \
    OMD_SWITCH_CASE(RetransmissionResp, 202); \
    OMD_SWITCH_CASE(SecurityDefinition, 611); \
    OMD_SWITCH_CASE(SecurityStatus, 621); \
    OMD_SWITCH_CASE(SequenceReset, 100); \
    OMD_SWITCH_CASE(Statistics, 660); \
    OMD_SWITCH_CASE(TopOfBook, 655); \
default: \
    processor.onUnknownMessage(type, msgSize); \
    break;
#endif

public:
    template <typename _Processor>
    static void parse(char* data, size_t bytesRecvd, _Processor& processor)
    {
        using namespace omdcc::sbe;
        parseHelper(data, bytesRecvd, processor,
            [](uint16_t type, char* pos, uint16_t msgSize, _Processor& processor, uint32_t seqNum) {
                switch (type)
                {
                    _OMDCC_MSG_SWITCH_
                }
            });
    }

    template <typename _Processor>
    static void parseRefresh(char* data, size_t bytesRecvd, _Processor& processor)
    {
        using namespace omdcc::sbe;
        parseRefreshHelper(data, bytesRecvd, processor,
            [](uint16_t type, char* pos, uint16_t msgSize, _Processor& processor, uint32_t seqNum) {
                switch (type)
                {
                    _OMDCC_MSG_SWITCH_
                }
            });
    }

    template <typename _Processor>
    static void processCachedMsg(_Processor& processor)
    {
        using namespace omdcc::sbe;
        processCachedMsgHelper(processor,
            [](uint16_t type, char* pos, uint16_t msgSize, _Processor& processor, uint32_t seqNum) {
                switch (type)
                {
                    _OMDCC_MSG_SWITCH_
                }
            });
    }
};
}