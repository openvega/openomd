#pragma once
#include "openomd/orderbookdef.h"

namespace openomd
{
template < typename _OrderIdPolicy, /*typename _UpdatePolicy, */ typename _OrderTypePolicy, typename _OrderStoragePolicy, typename _DepthPolicy>
class FullTickOrderBook
{
public:
    void addOrder(uint64_t orderId, px_t price, uint32_t quantity, uint16_t side, uint16_t orderType)
    {
        auto result = _orders.emplace(_OrderIdPolicy::id(orderId, side), _OrderStoragePolicy::mapped_type(price, quantity, orderType));
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
            updateDepth(side, pos->price, (quantity - pos->quantity));
            pos->quantity = quantity;
        }
    }

    void modifyOrder(uint64_t orderId, px_t price, uint32_t quantity, uint16_t side, uint16_t orderType)
    {
        auto pos = _orders.find(_OrderIdPolicy::id(orderId, side));
        if (pos != _orders.end())
        {
            if (tPos->second.price == price)
            {
                updateDepth(side, pos->price, (quantity - pos->quantity), true);
            }
            else
            {
                updateDepth(side, pos->price, pos->quantity * -1);
                insertDepth(side, price, quantity);
            }
            pos->price = price;
            pos->quantity = quantity;
            pos->orderType = orderType;
        }
    }
    
    void deleteOrder(uint64_t orderId, uint16_t side)
    {
        auto pos = _orders.find(_OrderIdPolicy::id(orderId, side));
        if (pos != _orders.end())
        {
            updateDepth(side, pos->price, pos->quantity * -1, true);
            _orders.erase(pos);
        }
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

    _OrderStoragePolicy _orders;
    _DepthPolicy _dp;
};

using OMDCFullTick = FullTickOrderBook<UniqueOrderIdPolicy, OMDCOrderTypePolicy, OrderMapPolicy, VectorDepth>;
}
