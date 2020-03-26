#pragma once
#include <sstream>
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
        RefreshCompleted,
        RefreshEnded
    };

    template <typename _Log>
    void onHeartbeat(_Log log);

    template <typename _Log>
    void onRefreshComplete(_Log log, uint32_t lastSeqNum);

    inline void start()
    {
        _state = State::Init;
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

    template <typename _Processor>
    inline bool checkPktSeq(_Processor& processor, openomd::PktHdr const& pktHdr, char* pos)
    {
        if (_state == State::Refreshing)
        {
            MapBasedCache::cache(pktHdr, pos);
        }
        return true;
    }
    template <typename _Processor>
    inline bool checkPktSeqWithtouRecovery(_Processor& processor, openomd::PktHdr const& pktHdr, char* pos)
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

template <typename _Log>
void BaseRefreshProcessor::onHeartbeat(_Log log)
{
    if (_state == State::Init)
    {
        _state = State::Refreshing;
        log("Start refresh");
    }
}

template <typename _Log>
void BaseRefreshProcessor::onRefreshComplete(_Log log, uint32_t lastSeqNum)
{
    if (_state == State::Init)
    {
        _state = State::Refreshing;
        log("Start refresh");
    }
    else if (_state == State::Refreshing)
    {
        _state = State::RefreshCompleted;
        _lastSeqNum = lastSeqNum;
        std::stringstream ss;
        ss << "refresh completed " << _lastSeqNum;
        log(ss.str());
    }
}

template <typename _F>
void BaseRefreshProcessor::consumeAll(_F f)
{
    for_each(MapBasedCache::_buffer.begin(), MapBasedCache::_buffer.end(), [&](auto& pos) {
        f(&pos.second[0], pos.second.size());
    });
}
template <typename _BaseProcessor>
class OmdcRefreshProcessor : public OMDCProcessor<BaseRefreshProcessor, _BaseProcessor>
{
public:
    using Base=OMDCProcessor<BaseRefreshProcessor, _BaseProcessor>;

    inline void onHeartbeat()
    {
        BaseRefreshProcessor::onHeartbeat([&](std::string const& msg) {
            std::stringstream ss;
            ss << Base::channel() << " " << msg;
            _BaseProcessor::info(ss.str());
        });
    }

    inline void onMessage(omdc::sbe::RefreshComplete const& m, uint32_t s)
    {
        BaseRefreshProcessor::onRefreshComplete([&](std::string const& msg) {
            std::stringstream ss;
            ss << Base::channel() << " " << msg;
            _BaseProcessor::info(ss.str());
        }, m.lastSeqNum());
    }
    using Base::onMessage;
};

template <typename _BaseProcessor>
class OmddRefreshProcessor : public OMDDProcessor<BaseRefreshProcessor, _BaseProcessor>
{
public:
    using Base=OMDDProcessor<BaseRefreshProcessor, _BaseProcessor>;
    inline void onHeartbeat()
    {
        BaseRefreshProcessor::onHeartbeat([&](std::string const& msg) {
            std::stringstream ss;
            ss << Base::channel() << " " << msg;
            _BaseProcessor::info(ss.str());
        });
    }

    inline void onMessage(omdd::sbe::RefreshComplete const& m, uint32_t s)
    {
        BaseRefreshProcessor::onRefreshComplete([&](std::string const& msg) {
            std::stringstream ss;
            ss << Base::channel() << " " << msg;
            _BaseProcessor::info(ss.str());
        }, m.lastSeqNum());
    }
    using Base::onMessage;
};
}
