#pragma once
#include <cstdint>
#include <string>

namespace openomd
{   
class BaseProcessor
{
public:
    inline int32_t channel() const {
        return _channel;
    }
    inline void channel(int32_t channel) {
        _channel = channel;
    }
    void onError(std::exception const& ex)
    {
    }
    void info(std::string const& log) const
    {
    }
    void warn(std::string const& log) const
    {
    }
    void error(std::string const& log) const
    {
    }
private:
    int32_t _channel;
};
}