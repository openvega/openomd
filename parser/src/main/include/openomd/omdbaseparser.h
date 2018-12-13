#pragma once

namespace openomd
{
class OmdBaseParser
{
protected:
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

    template <typename _Msg, typename _Callback>
    static void process(char* buffer, size_t size, _Callback& callback, int32_t partition)
    {
        _Msg msg(buffer, size, _Msg::sbeBlockLength(), _Msg::sbeSchemaVersion());
        callback.onMessage(msg, partition);
    }

    template <typename _Callback, typename _Func>
    static void parseHelper(char* data, size_t bytesRecvd, _Callback& callback, int32_t partition, _Func func)
    {
        static const auto MSG_HDR_SIZE = static_cast<int16_t>(sizeof(MsgHdr));
        if (bytesRecvd >= sizeof(PktHdr))
        {
            PktHdr* pktHdr = (PktHdr*)data;
            auto byteProcess = sizeof(PktHdr);
            int64_t byteLeft = 0;
            uint16_t msgCnt = 0;
            while ((byteLeft = bytesRecvd - byteProcess) > MSG_HDR_SIZE)
            {
                MsgHdr* msgHdr = (MsgHdr*)(data + byteProcess);
                if (msgHdr->size == 0)
                    break;
                char* pos = data + byteProcess + MSG_HDR_SIZE;
                auto msgSize = msgHdr->size - MSG_HDR_SIZE;
                assert(msgSize >= 0);
                func(msgHdr->type, pos, msgSize, callback, partition);
                byteProcess += msgHdr->size;
            }
            assert(byteLeft >= 0);
        }
    }
};
}
