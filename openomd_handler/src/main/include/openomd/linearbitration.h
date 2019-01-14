#pragma once
#include <unordered_map>
#include <vector>

namespace openomd
{
template <typename _Cache, typename _RecoveryPolicy>
class LineArbitration : public _RecoveryPolicy
{
public:
    bool checkPktSeq(int32_t partition, openomd::PktHdr const& pktHdr, char* pos);
    bool checkMsgSeq(int32_t, uint32_t);
    
private:
    uint32_t _nextSeqNum = 1;
    _Cache _cache;
};

template <typename _Cache, typename _RecoveryPolicy>
bool LineArbitration<_Cache, _RecoveryPolicy>::checkPktSeq(int32_t partition, openomd::PktHdr const& pktHdr, char* pos)
{
    if ((pktHdr.seqNum + pktHdr.msgCnt) < _nextSeqNum)   // normal
    {
        return false;
        // then process cached message?
    }
    if (pktHdr.seqNum > _nextSeqNum)   // gap
    {
        // Kick off recovery
        _RecoveryPolicy::recovery(partition, _nextSeqNum);
        // Cache packet
        _Cache::cache(pos, pktHdr.size);
        return false;
    }
    return true;
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
}