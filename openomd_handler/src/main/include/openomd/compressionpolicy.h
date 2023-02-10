#pragma once
#include <zlib.h>
#include "openomd/omddef.h"

namespace openomd
{
struct NoopCompressionPolicy
{
    static inline bool process(PktHdr*& pktHdr, char*& data, size_t& dataSize, char* uncompressedBuffer, size_t cbSize)
    {
        return true;
    }
};

struct ZLibCompressionPolicy
{
    static inline bool process(PktHdr*& pktHdr, char*& data, size_t& dataSize, char* uncompressedBuffer, size_t cbSize)
    {
        bool rtn = true;
        if (pktHdr->compressionMode == 1)
        {
            uLongf compressedSize = static_cast<uLongf>(dataSize - sizeof(PktHdr));
            uLongf uncompressedSize = static_cast<uLongf>(cbSize - sizeof(PktHdr));
            memcpy(uncompressedBuffer, pktHdr, sizeof(PktHdr));
            auto ucresult = uncompress((unsigned char*)(uncompressedBuffer + sizeof(PktHdr)), &uncompressedSize, (unsigned char*)(data + sizeof(PktHdr)), compressedSize);
            switch (ucresult)
            {
            case Z_OK:
                data = uncompressedBuffer;
                pktHdr = (PktHdr*)uncompressedBuffer;
                pktHdr->size = static_cast<uint16_t>(uncompressedSize + sizeof(PktHdr));
                dataSize = uncompressedSize + sizeof(PktHdr);
                break;
            case Z_MEM_ERROR:
            case Z_BUF_ERROR:
                rtn = false;
                break;
            }
        }
        return rtn;
    }
};
}