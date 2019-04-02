#pragma once
#include "openomd/recoverypolicy.h"
#include "openomd/msgcache.h"

namespace openomd
{
template <typename _Cache, typename _RecoveryPolicy>
class LineArbitration : public _RecoveryPolicy, protected _Cache
{
public:
    using _RecoveryPolicy::_RecoveryPolicy;

    template <typename _Processor>
    bool checkPktSeq(_Processor& processor, openomd::PktHdr const& pktHdr, char* pos);
    template <typename _Processor>
    bool checkPktSeqWithtouRecovery(_Processor& processor, openomd::PktHdr const& pktHdr, char* pos);
    bool checkMsgSeq(uint32_t);
    void resetSeqNum(uint32_t newSeqNum);

    template <typename _Func>
    void processCache(_Func func);

    uint32_t nextSeqNum() const;
private:
    template <typename _RecoveryFunc>
    bool checkPktSeqInternal(openomd::PktHdr const& pktHdr, char* pos, _RecoveryFunc recoveryFunc);

    uint32_t _nextSeqNum = 1;
};

template <typename _Cache, typename _RecoveryPolicy>
template <typename _Processor>
bool LineArbitration<_Cache, _RecoveryPolicy>::checkPktSeq(_Processor& processor, openomd::PktHdr const& pktHdr, char* pos)
{
    return checkPktSeqInternal(pktHdr, pos, [&]()
    {
        std::stringstream ss;
        ss << "channel " << processor.channel() << " checkPktSeq gap detected nextSeq=" << _nextSeqNum << " pktseq=" << pktHdr.seqNum;
        processor.warn(ss.str());
        _RecoveryPolicy::recover(pktHdr, _nextSeqNum);
        _Cache::cache(pktHdr, pos);
    });
}

template <typename _Cache, typename _RecoveryPolicy>
template <typename _Processor>
bool LineArbitration<_Cache, _RecoveryPolicy>::checkPktSeqWithtouRecovery(_Processor& processor, openomd::PktHdr const& pktHdr, char* pos)
{
    return checkPktSeqInternal(pktHdr, pos, []() {});
}

template <typename _Cache, typename _RecoveryPolicy>
template <typename _RecoveryFunc>
bool LineArbitration<_Cache, _RecoveryPolicy>::checkPktSeqInternal(openomd::PktHdr const& pktHdr, char* pos, _RecoveryFunc recoveryFunc)
{
    if ((pktHdr.seqNum + pktHdr.msgCnt - 1) < _nextSeqNum)  // duplicated
    {
        return false;
    }
    if (pktHdr.seqNum > _nextSeqNum)   // gap
    {
        recoveryFunc();
        return false;
    }
    return true;
}

template <typename _Cache, typename _RecoveryPolicy>
bool LineArbitration<_Cache, _RecoveryPolicy>::checkMsgSeq(uint32_t seqNum)
{
    if (seqNum == _nextSeqNum)
    {
        _nextSeqNum++;
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
        func(&pos->second[0], pos->second.size());
        auto removePos = pos;
        pos++;
        _Cache::_buffer.erase(removePos);
    }
}

template <typename _Cache, typename _RecoveryPolicy>
uint32_t LineArbitration<_Cache, _RecoveryPolicy>::nextSeqNum() const
{
    return _nextSeqNum;
}

using PcapLineArbitration = LineArbitration<MapBasedCache, PcapRecoveryPolicy>;
}
