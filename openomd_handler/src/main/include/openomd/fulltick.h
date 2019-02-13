#pragma once
#include "openomd/orderbookdef.h"

namespace openomd
{
template < typename _OrderIdPolicy, typename _OrderTypePolicy, typename _DepthPolicy>
class FullTickOrderBook
{
public:
    void addOrder(uint64_t orderId, px_t price, uint32_t quantity, uint16_t side, uint16_t orderType)
    {
        auto result = _orders.emplace(_OrderIdPolicy::id(orderId, side), _OrderIdPolicy::OrderMap::mapped_type(price, quantity, orderType));
        if (result.second)
        {
            insertDepth(side, price, quantity);
        }
    }

    void modifyOrder(uint64_t orderId, uint32_t quantity, uint16_t side)
    {
        auto pos = _orders.find(_OrderIdPolicy::id(orderId, side));
        if (pos != _orders.end())
        {
            updateDepth(side, pos->second.price, (quantity - pos->second.quantity));
            pos->second.quantity = quantity;
        }
    }

    void modifyOrder(uint64_t orderId, px_t price, uint32_t quantity, uint16_t side, uint16_t orderType)
    {
        auto pos = _orders.find(_OrderIdPolicy::id(orderId, side));
        if (pos != _orders.end())
        {
            if (pos->second.price == price)
            {
                updateDepth(side, pos->second.price, (quantity - pos->second.quantity), false);
            }
            else
            {
                updateDepth(side, pos->second.price, pos->second.quantity * -1, true);
                insertDepth(side, price, quantity);
            }
            pos->second.price = price;
            pos->second.quantity = quantity;
            pos->second.orderType = orderType;
        }
    }
    
    void deleteOrder(uint64_t orderId, uint16_t side)
    {
        auto pos = _orders.find(_OrderIdPolicy::id(orderId, side));
        if (pos != _orders.end())
        {
            updateDepth(side, pos->second.price, pos->second.quantity * -1, true);
            _orders.erase(pos);
        }
    }

    void clear()
    {
        _orders.clear();
        _dp._depth[0].clear();
        _dp._depth[1].clear();
    }

    _DepthPolicy const& depth() const
    {
        return _dp;
    }

private:
    // TODO: insertDepth and updateDepth should move to DepthPolicy
    void insertDepth(uint16_t side, px_t price, uint32_t quantity)
    {
        bool insertAtEnd = true;
        for (auto pos = _dp._depth[side].begin(); pos != _dp._depth[side].end(); ++pos)
        {
            if (pos->price > price)
            {
                // insert
                _dp._depth[side].insert(pos, _DepthPolicy::_Level{ price, quantity, 1 });
                insertAtEnd = false;
                break;
            }
            else if (pos->price == price)
            {
                pos->qty += quantity;
                pos->nbOrder++;
                insertAtEnd = false;
                break;
            }
        }
        if (insertAtEnd)
        {
            _dp._depth[side].emplace_back(_DepthPolicy::_Level{ price, quantity, 1 });
        }
    }

    void updateDepth(uint16_t side, px_t price, uint32_t quantity, bool reduceNbOrder = false)
    {
        for (auto pos = _dp._depth[side].begin(); pos != _dp._depth[side].end(); ++pos)
        {
            if (pos->price == price)
            {
                pos->qty += quantity;
                if (pos->qty == 0)
                {
                    _dp._depth[side].erase(pos);
                }
                else
                {
                    if (reduceNbOrder)
                    {
                        pos->nbOrder--;
                    }
                }
                break;
            }
        }
    }

    typename _OrderIdPolicy::OrderMap _orders;
    _DepthPolicy _dp;
};

class OMDCFullTick : public FullTickOrderBook<UniqueOrderIdPolicy, OMDCOrderTypePolicy, VectorDepth>
{
    void modifyOrder(uint64_t, px_t, uint32_t, uint16_t, uint16_t) = delete;
public:
    using FullTickOrderBook<UniqueOrderIdPolicy, OMDCOrderTypePolicy, VectorDepth>::modifyOrder;
};

class OMDDFullTick : public FullTickOrderBook<OrderSideIdPolicy, OMDDOrderTypePolicy, VectorDepth>
{
    void modifyOrder(uint64_t, uint32_t, uint16_t) = delete;
public:
    using FullTickOrderBook<OrderSideIdPolicy, OMDDOrderTypePolicy, VectorDepth>::modifyOrder;
};
}
