#pragma once
#include "openomd/omddef.h"

namespace openomd
{
#define OMD_SWITCH_CASE(MESSAGE) case MESSAGE::sbeTemplateId(): process<MESSAGE>(pos, msgSize, processor, partition, seqNum); break;
class OmdBaseParser
{
protected:
    template <typename _Msg, typename _Processor>
    static void process(char* buffer, size_t size, _Processor& processor, int32_t partition, uint32_t seqNum)
    {
        _Msg msg(buffer, size, _Msg::sbeBlockLength(), _Msg::sbeSchemaVersion());
        processor.onMessage(msg, partition, seqNum);
    }

    template <typename _Processor, typename _Func>
    static void parseHelper(char* data, size_t bytesRecvd, _Processor& processor, int32_t partition, _Func func)
    {
        static const auto MSG_HDR_SIZE = static_cast<int16_t>(sizeof(MsgHdr));
        if (bytesRecvd >= sizeof(PktHdr))
        {
            PktHdr* pktHdr = (PktHdr*)data;
            if (processor.checkPktSeq(partition, *pktHdr, data))
            {
                auto byteProcess = sizeof(PktHdr);
                int64_t byteLeft = 0;
                uint16_t msgCnt = 0;
                while ((byteLeft = bytesRecvd - byteProcess) > MSG_HDR_SIZE)
                {
                    auto* pos = data + byteProcess;
                    MsgHdr* msgHdr = (MsgHdr*)(pos);
                    if (msgHdr->size == 0 || msgHdr->size > byteLeft)
                    {
                        processor.onError(std::exception("Invalid message size"));
                        break;
                    }
                    try
                    {
                        auto msgSeq = pktHdr->seqNum + msgCnt;
                        if (processor.checkMsgSeq(partition, msgSeq))
                        {
                            func(msgHdr->type, pos + MSG_HDR_SIZE, msgHdr->size - MSG_HDR_SIZE, processor, partition, msgSeq);
                        }   
                    }
                    catch (std::exception const& ex)
                    {
                        processor.onError(ex);
                    }
                    byteProcess += msgHdr->size;
                    ++msgCnt;
                }
                // Try consume cached packet

            }
        }
    }
};
}
