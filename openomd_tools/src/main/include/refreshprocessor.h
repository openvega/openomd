#pragma once
#include "openomd/nooplinearbitration.h"
#include "openomd/omdcprocessor.h"
#include "openomd/omddprocessor.h"

namespace openomd
{
class BaseRefreshProcessor
{
public:
    bool refreshing() const
    {
        return _refreshing;
    }

    bool refreshCompleted() const
    {
        return _refreshCompleted;
    }

    void onRefreshComplete()
    {
        if (!_refreshing)
        {
            _refreshing = true;
        }
        else
        {
            _refreshing = false;
            _refreshCompleted = true;
        }
    }
private:
    bool _refreshing = false;
    bool _refreshCompleted = false;
};
class OmdcRefreshProcessor : public OMDCProcessor<NoopLineArbitration>, public BaseRefreshProcessor
{
public:
    using OMDCProcessor::onMessage;
    void onMessage(omdc::sbe::RefreshComplete const& m, uint32_t s)
    {
        onRefreshComplete();
    }
};

class OmddRefreshProcessor : public OMDDProcessor<NoopLineArbitration>, public BaseRefreshProcessor
{
public:
    using OMDDProcessor::onMessage;
    void onMessage(omdd::sbe::RefreshComplete const& m, int32_t s)
    {
        onRefreshComplete();
    }
};
}