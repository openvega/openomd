#pragma once
#include <openomd/parser.h>
#include <omdc_sbe/AggregateOrderBookUpdate.h>
#include <omdd_sbe/AggregateOrderBookUpdate.h>
#include <omdd_sbe/SeriesDefinitionBase.h>
#include <omdd_sbe/RefreshComplete.h>

namespace openomd
{
class parser_api OmdParser
{
    struct PktHdr
    {
        uint16_t size;
        uint8_t msgCnt;
        uint8_t filler;
        uint32_t seqNum;
        uint64_t sendTime;
    };
    struct MsgHdr
    {
        uint16_t size;
        uint16_t type;
    };

public:
    template <typename _Msg, typename _Callback>
    static void process(char* buffer, size_t size, _Callback& callback)
    {
        _Msg msg(buffer, size, sizeof(MsgHdr), _Msg::sbeSchemaVersion());
        callback.onMessage(msg);
    }

    template <typename _Callback>
    static void parse(char* data, size_t bytesRecvd, _Callback& callback)
    {
        if (bytesRecvd >= sizeof(PktHdr))
        {
            PktHdr* pktHdr = (PktHdr*) data;
            auto byteProcess = sizeof(PktHdr);
            size_t byteLeft = 0;
            uint16_t msgCnt = 0;
            while ((byteLeft = bytesRecvd - byteProcess) > sizeof(MsgHdr))
            {
                MsgHdr* msgHdr = (MsgHdr*) (data + byteProcess);
                if (msgHdr->size == 0)
                    break;
                char* pos = data + byteProcess + sizeof(MsgHdr);
                auto msgSize = msgHdr->size - sizeof(MsgHdr);
                switch (msgHdr->type)
                {
                case omdc::sbe::AggregateOrderBookUpdate::sbeTemplateId():
                    process<omdc::sbe::AggregateOrderBookUpdate>(pos, msgSize, callback);
                    break;
                case omdd::sbe::SeriesDefinitionBase::sbeTemplateId():
                    process<omdd::sbe::SeriesDefinitionBase>(pos, msgSize, callback);
                    break;
                case omdd::sbe::AggregateOrderBookUpdate::sbeTemplateId():
                    process<omdd::sbe::AggregateOrderBookUpdate>(pos, msgSize, callback);
                    break;
                case omdd::sbe::RefreshComplete::sbeTemplateId():
                    process<omdd::sbe::RefreshComplete>(pos, msgSize, callback);
                    break;
                default:
                    callback.onUnknownMessage(msgHdr->type, msgHdr->size);
                    break;
                }
                byteProcess += msgHdr->size;
            }
        }
    }
};
}
