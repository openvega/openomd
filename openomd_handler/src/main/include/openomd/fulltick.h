#pragma once
#include <cstdint>

namespace openomd
{
template < typename _OrderIdPolicy, typename _UpdatePolicy, typename _OrderTypePolicy>
class FullTickOrderBook
{
public:
    void addOrder(uint64_t orderId, int32_t price, uint32_t quantity, uint16_t side, uint16_t orderType)
    {

    }
    void modifyOrder(uint64_t orderId, uint32_t quantity, uint16_t side)
    {

    }
    void modifyOrder(uint64_t orderId, int32_t price, uint32_t quantity, uint16_t side, uint16_t orderType)
    {

    }
    void deleteOrder(uint64_t orderId, uint16 side)
    {

    }
};
}