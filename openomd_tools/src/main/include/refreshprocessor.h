#pragma once
#include "openomd/nooplinearbitration.h"
#include "openomd/omdcprocessor.h"
#include "openomd/omddprocessor.h"
#include "openomd/msgcache.h"

namespace openomd
{
class BaseRefreshProcessor : public MapBasedCache
{
public:
    enum class State
    {
        Init,
        Refreshing,
        RefreshCompleted
    };
    void onHeartbeat()
    {
        if (_state == State::Init)
        {
            _state = State::Refreshing;
            std::cout << "Start refresh" << std::endl;
        }
    }
    void onRefreshComplete(uint32_t lastSeqNum)
    {
        if (_state == State::Init)
        {
            _state = State::Refreshing;
            std::cout << "Start refresh" << std::endl;
        }
        else if (_state == State::Refreshing)
        {
            _state = State::RefreshCompleted;
            _lastSeqNum = lastSeqNum;
            std::cout << "Refresh completed " << _lastSeqNum << std::endl;
        }
    }
    void reset()
    {
        _state = State::Init;
        _lastSeqNum = 0;
        MapBasedCache::_buffer.clear();
    }
    bool refreshCompleted() const
    {
        return _state == State::RefreshCompleted;
    }
    template <typename _F>
    void consumeAll(_F f)
    {
        for_each(MapBasedCache::_buffer.begin(), MapBasedCache::_buffer.end(), [&](auto& pos) {
            f(&pos.second[0], pos.second.size());
        });
    }

    inline bool checkPktSeq(openomd::PktHdr const& pktHdr, char* pos)
    {
        if (_state == State::Refreshing)
        {
            MapBasedCache::cache(pktHdr, pos);
        }
        return true;
    }
    inline bool checkPktSeqWithtouRecovery(openomd::PktHdr const& pktHdr, char* pos)
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
class OmdcRefreshProcessor : public OMDCProcessor<BaseRefreshProcessor>
{
public:
    void onHeartbeat()
    {
        BaseRefreshProcessor::onHeartbeat();
    }

    void onMessage(omdc::sbe::RefreshComplete const& m, uint32_t s)
    {
        onRefreshComplete(m.lastSeqNum());
    }
    using OMDCProcessor::onMessage;
};

class OmddRefreshProcessor : public OMDDProcessor<BaseRefreshProcessor>
{
public:
    void onHeartbeat()
    {
        BaseRefreshProcessor::onHeartbeat();
    }

    void onMessage(omdd::sbe::RefreshComplete const& m, uint32_t s)
    {
        onRefreshComplete(m.lastSeqNum());
    }
    using OMDDProcessor::onMessage;
};
}
