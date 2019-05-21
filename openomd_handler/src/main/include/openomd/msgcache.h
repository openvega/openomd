#pragma once
#include <map>
#include <vector>
#include "openomd/omddef.h"

namespace openomd
{
class MapBasedCache
{
public:
    inline void cache(PktHdr const& pktHdr, char* pos)
    {
        if (_buffer.find(pktHdr.seqNum) == _buffer.end())
        {
            _buffer.emplace(pktHdr.seqNum, std::vector<char>(pos, pos + pktHdr.size));
        }
    }

    inline void clear()
    {
        _buffer.clear();
    }

protected:
    std::map<uint32_t, std::vector<char>> _buffer;  // SeqNum -> packet
};
}
