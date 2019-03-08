#pragma once
#include <unordered_map>
#include "openomd/recoverypolicy.h"
#include "openomd/msgcache.h"

namespace openomd
{
template <typename _Cache, typename _RecoveryPolicy>
class LineArbitration : public _RecoveryPolicy, protected _Cache
{
public:
    bool checkPktSeq(openomd::PktHdr const& pktHdr, char* pos);
    bool checkPktSeqWithtouRecovery(openomd::PktHdr const& pktHdr, char* pos);
    bool checkMsgSeq(uint32_t);
    void resetSeqNum(uint32_t newSeqNum);

    template <typename _Func>
    void processCache(_Func func);

private:
    template <typename _RecoveryFunc>
    bool checkPktSeqInternal(openomd::PktHdr const& pktHdr, char* pos, _RecoveryFunc func);

    uint32_t _nextSeqNum = 1;
};

template <typename _Cache, typename _RecoveryPolicy>
bool LineArbitration<_Cache, _RecoveryPolicy>::checkPktSeq(openomd::PktHdr const& pktHdr, char* pos)
{
    return checkPktSeqInternal(pktHdr, pos, [&]()
    {
        _RecoveryPolicy::recover(pktHdr, _nextSeqNum);
        _Cache::cache(pktHdr, pos);
    });
}

template <typename _Cache, typename _RecoveryPolicy>
bool LineArbitration<_Cache, _RecoveryPolicy>::checkPktSeqWithtouRecovery(openomd::PktHdr const& pktHdr, char* pos)
{
    return checkPktSeqInternal(pktHdr, pos, []() {});
}

template <typename _Cache, typename _RecoveryPolicy>
template <typename _RecoveryFunc>
bool LineArbitration<_Cache, _RecoveryPolicy>::checkPktSeqInternal(openomd::PktHdr const& pktHdr, char* pos, _RecoveryFunc func)
{
    if ((pktHdr.seqNum + pktHdr.msgCnt - 1) < _nextSeqNum)  // duplicated
    {
        return false;
    }
    if (pktHdr.seqNum > _nextSeqNum)   // gap
    {
        func();
        return false;
    }
    return true;
}

template <typename _Cache, typename _RecoveryPolicy>
bool LineArbitration<_Cache, _RecoveryPolicy>::checkMsgSeq(uint32_t seqNum)
{
    if (seqNum == _nextSeqNum)
    {
        _nextSeqNum = seqNum+1;
        return true;
    }
    else
    {
        return false;
    }
}

template <typename _Cache, typename _RecoveryPolicy>
void LineArbitration<_Cache, _RecoveryPolicy>::resetSeqNum(uint32_t newSeqNum)
{
    _nextSeqNum = newSeqNum;
}

template <typename _Cache, typename _RecoveryPolicy>
template <typename _Func>
void LineArbitration<_Cache, _RecoveryPolicy>::processCache(_Func func)
{
    if (_Cache::_buffer.empty())
    {
        _RecoveryPolicy::stopRecovery();
        return;
    }

    auto pos = _Cache::_buffer.begin();
    while (pos != _Cache::_buffer.end())
    {
        if (pos->first > _nextSeqNum)
        {
            break;
        }
        PktHdr* pktHdr = (PktHdr*)&pos->second[0];
        func(&pos->second[0], pos->second.size());
        printf("process cache %d\n", pos->first);
        auto removePos = pos;
        pos++;
        _Cache::_buffer.erase(removePos);
    }
}

using PcapLineArbitration = LineArbitration<MapBasedCache, PcapRecoveryPolicy>;
}
