#pragma once
#include "openomd/omddef.h"

namespace openomd
{
struct NoopCompressionPolicy
{
    static void process(PktHdr*& pktHdr, char*& data, size_t dataSize, char* uncompressedBuffer, size_t cbSize)
    {
    }
};

struct ZLibCompressionPolicy
{
    static void process(PktHdr*& pktHdr, char*& data, size_t dataSize, char* uncompressedBuffer, size_t cbSize)
    {
        if (pktHdr->compressionMode)
        {


        }
    }
};
}