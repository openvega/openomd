#pragma once
#include "openomd/nooplinearbitration.h"
#include "openomd/omdcprocessor.h"
#include "openomd/omddprocessor.h"
#include "openomd/msgcache.h"

namespace openomd
{
template <typename _Logger>
class BaseRefreshProcessor : public MapBasedCache, protected _Logger
{
public:
    enum class State
    {
        Init,
        Refreshing,
        RefreshCompleted,
        RefreshEnded
    };
    inline void onHeartbeat(int32_t channel)
    {
        if (_state == State::Init)
        {
            _state = State::Refreshing;
            std::stringstream ss;
            ss << channel << " Start refresh";
            _Logger::info(ss.str());
        }
    }
    inline void onRefreshComplete(int32_t channel, uint32_t lastSeqNum)
    {
        if (_state == State::Init)
        {
            _state = State::Refreshing;
            std::stringstream ss;
            ss << channel << " Start refresh";
            _Logger::info(ss.str());
        }
        else if (_state == State::Refreshing)
        {
            _state = State::RefreshCompleted;
            _lastSeqNum = lastSeqNum;
            std::stringstream ss;
            ss << channel << " Refresh completed " << _lastSeqNum;
            _Logger::info(ss.str());
        }
    }
    inline void end()
    {
        _state = State::RefreshEnded;
        _lastSeqNum = 0;
        MapBasedCache::_buffer.clear();
    }
    inline bool refreshCompleted() const
    {
        return _state == State::RefreshCompleted;
    }
    inline bool refreshEnded() const
    {
        return _state == State::RefreshEnded;
    }

    template <typename _F>
    void consumeAll(_F f);

    inline bool checkPktSeq(int32_t channel, openomd::PktHdr const& pktHdr, char* pos)
    {
        if (_state == State::Refreshing)
        {
            MapBasedCache::cache(pktHdr, pos);
        }
        return true;
    }
    inline bool checkPktSeqWithtouRecovery(int32_t channel, openomd::PktHdr const& pktHdr, char* pos)
    {
        return true;
    }
    inline bool checkMsgSeq(uint32_t)
    {
        return true;
    }
    inline void resetSeqNum(uint32_t newSeqNum)
    {
    }

    template <typename _Func>
    inline void processCache(_Func func)
    {
    }
    inline uint32_t nextSeqNum() const
    {
        return _lastSeqNum+1;
    }
protected:
    State _state = State::Init;
    uint32_t _lastSeqNum = 0;
};

template <typename _Logger>
template <typename _F>
void BaseRefreshProcessor<_Logger>::consumeAll(_F f)
{
    for_each(MapBasedCache::_buffer.begin(), MapBasedCache::_buffer.end(), [&](auto& pos) {
        f(&pos.second[0], pos.second.size());
    });
}
template <typename _Logger>
class OmdcRefreshProcessor : public OMDCProcessor<BaseRefreshProcessor<_Logger>>
{
public:
    inline void onHeartbeat()
    {
        BaseRefreshProcessor::onHeartbeat(channel());
    }

    inline void onMessage(omdc::sbe::RefreshComplete const& m, uint32_t s)
    {
        onRefreshComplete(channel(), m.lastSeqNum());
    }
    using OMDCProcessor<BaseRefreshProcessor<_Logger>>::onMessage;
};

template <typename _Logger>
class OmddRefreshProcessor : public OMDDProcessor<BaseRefreshProcessor<_Logger>>
{
public:
    inline void onHeartbeat()
    {
        BaseRefreshProcessor::onHeartbeat(channel());
    }

    inline void onMessage(omdd::sbe::RefreshComplete const& m, uint32_t s)
    {
        onRefreshComplete(channel(), m.lastSeqNum());
    }
    using OMDDProcessor<BaseRefreshProcessor<_Logger>>::onMessage;
};
}
