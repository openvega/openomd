#pragma once
#include <unordered_map>
#include <vector>
#include "openomd/recoverypolicy.h"
#include "openomd/vectorbasedcache.h"

namespace openomd
{
template <typename _Cache, typename _RecoveryPolicy>
class LineArbitration : public _RecoveryPolicy, protected _Cache
{
public:
    bool checkPktSeq(int32_t partition, openomd::PktHdr const& pktHdr, char* pos);
    bool checkPktSeqWithtouRecovery(int32_t partition, openomd::PktHdr const& pktHdr, char* pos);
    bool checkMsgSeq(int32_t, uint32_t);
    
    template <typename _Func>
    void processCache(_Func func);

private:
    template <typename _RecoveryFunc>
    bool checkPktSeqInternal(int32_t partition, openomd::PktHdr const& pktHdr, char* pos, _RecoveryFunc func)
    {
        if ((pktHdr.seqNum + pktHdr.msgCnt) < _nextSeqNum)  // duplicated
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
    uint32_t _nextSeqNum = 1;
};

template <typename _Cache, typename _RecoveryPolicy>
bool LineArbitration<_Cache, _RecoveryPolicy>::checkPktSeq(int32_t partition, openomd::PktHdr const& pktHdr, char* pos)
{
    return checkPktSeqInternal(partition, pktHdr, pos, [&]()
    {
        _RecoveryPolicy::recover(pktHdr, partition, _nextSeqNum);
        _Cache::cache(pktHdr, pos);
    });
}

template <typename _Cache, typename _RecoveryPolicy>
bool LineArbitration<_Cache, _RecoveryPolicy>::checkPktSeqWithtouRecovery(int32_t partition, openomd::PktHdr const& pktHdr, char* pos)
{
    return checkPktSeqInternal(partition, pktHdr, pos, []() {});
}

template <typename _Cache, typename _RecoveryPolicy>
bool LineArbitration<_Cache, _RecoveryPolicy>::checkMsgSeq(int32_t partition, uint32_t seqNum)
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
template <typename _Func>
void LineArbitration<_Cache, _RecoveryPolicy>::processCache(_Func func)
{
    if (_Cache::_buffer.empty())
    {
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
        auto removePos = pos;
        pos++;
        _Cache::_buffer.erase(removePos);
    }
}

using NoRecoveryLineArbitration = LineArbitration<MapBasedCache, NoopRecoveryPolicy>;
using PcapLineArbitration = LineArbitration<MapBasedCache, PcapRecoveryPolicy>;
}