#pragma once
#include <array>
#include <cstdint>
#include <limits>
#include <unordered_map>
#include <vector>

namespace openomd
{
using px_t = int32_t;
using lvQty_t = uint32_t;

struct Level
{
    px_t price = 0;
    lvQty_t qty = 0;
    uint32_t nbOrder = 0;

    inline explicit Level(px_t p = 0, lvQty_t q = 0, uint32_t nb = 0)
        : price(p)
        , qty(q)
        , nbOrder(nb)
    {
    }
    inline void update(px_t p, lvQty_t q, uint32_t nb)
    {
        price = p;
        qty = q;
        nbOrder = nb;
    }
    inline bool operator==(Level const& rhs) const
    {
        return price == rhs.price && qty == rhs.qty && nbOrder == rhs.nbOrder;
    }
};

//template <uint16_t _Depth = 10>
//struct ArrayDepth
//{
//    using Levels = std::array<Level, _Depth>;
//    Levels _depth[2];
//    uint16_t _depthSize[2] = { 0,0 };
//    uint16_t _maxDepth = _Depth;
//};

struct VectorDepth
{
    VectorDepth(uint16_t maxDepth = 10)
    {
        _maxDepth = maxDepth;
        _depth[0].reserve(_maxDepth);
        _depth[1].reserve(_maxDepth);
    }
    using _Level = Level;
    using Levels = std::vector<Level>;
    Levels _depth[2];
    uint16_t _maxDepth;
};

struct OrderDetail
{
    inline OrderDetail(px_t p, uint32_t qty, uint16_t type)
        : price{p}, quantity{ qty }, orderType{type}
    {
    }

    px_t price;
    uint32_t quantity;
    uint16_t orderType;
};

struct UniqueOrderIdPolicy
{
    static uint64_t id(uint64_t orderId, uint16_t side)
    {
        return orderId;
    }
};
struct OrderSideIdPolicy
{
    static std::pair<uint64_t, uint16_t> id(uint64_t orderId, uint16_t side)
    {
        return std::make_pair(orderId, side);
    }
};

struct OMDCOrderTypePolicy
{
    bool isMarketOrder(uint16_t orderType)
    {
        return orderType == '1';
    }
};
struct OMDDOrderTypePolicy
{
    bool isMarketOrder(uint16_t orderType)
    {
        return false;
    }
};

using OrderMapPolicy = std::unordered_map<uint64_t, OrderDetail>;
}