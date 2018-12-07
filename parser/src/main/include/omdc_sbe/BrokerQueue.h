/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDC_SBE_BROKERQUEUE_H_
#define _OMDC_SBE_BROKERQUEUE_H_

#if defined(SBE_HAVE_CMATH)
/* cmath needed for std::numeric_limits<double>::quiet_NaN() */
#  include <cmath>
#  define SBE_FLOAT_NAN std::numeric_limits<float>::quiet_NaN()
#  define SBE_DOUBLE_NAN std::numeric_limits<double>::quiet_NaN()
#else
/* math.h needed for NAN */
#  include <math.h>
#  define SBE_FLOAT_NAN NAN
#  define SBE_DOUBLE_NAN NAN
#endif

#if __cplusplus >= 201103L
#  include <cstdint>
#  include <string>
#  include <cstring>
#endif

#if __cplusplus >= 201103L
#  define SBE_CONSTEXPR constexpr
#  define SBE_NOEXCEPT noexcept
#else
#  define SBE_CONSTEXPR
#  define SBE_NOEXCEPT
#endif

#include <sbe/sbe.h>

#include "MessageHeader.h"
#include "GroupSize8.h"
#include "GroupSize16.h"

using namespace sbe;

namespace omdc {
namespace sbe {

class BrokerQueue
{
private:
    char *m_buffer;
    std::uint64_t m_bufferLength;
    std::uint64_t *m_positionPtr;
    std::uint64_t m_offset;
    std::uint64_t m_position;
    std::uint64_t m_actingBlockLength;
    std::uint64_t m_actingVersion;

    inline void reset(
        char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength,
        const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        m_buffer = buffer;
        m_offset = offset;
        m_bufferLength = bufferLength;
        m_actingBlockLength = actingBlockLength;
        m_actingVersion = actingVersion;
        m_positionPtr = &m_position;
        position(offset + m_actingBlockLength);
    }

    inline void reset(const BrokerQueue& codec)
    {
        m_buffer = codec.m_buffer;
        m_offset = codec.m_offset;
        m_bufferLength = codec.m_bufferLength;
        m_actingBlockLength = codec.m_actingBlockLength;
        m_actingVersion = codec.m_actingVersion;
        m_positionPtr = &m_position;
        m_position = codec.m_position;
    }

public:

    BrokerQueue() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    BrokerQueue(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    BrokerQueue(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    BrokerQueue(const BrokerQueue& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    BrokerQueue(BrokerQueue&& codec)
    {
        reset(codec);
    }

    BrokerQueue& operator=(BrokerQueue&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    BrokerQueue& operator=(const BrokerQueue& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)4;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)54;
    }

    static SBE_CONSTEXPR std::uint16_t sbeSchemaId() SBE_NOEXCEPT
    {
        return (std::uint16_t)1;
    }

    static SBE_CONSTEXPR std::uint16_t sbeSchemaVersion() SBE_NOEXCEPT
    {
        return (std::uint16_t)1;
    }

    static SBE_CONSTEXPR const char * sbeSemanticType() SBE_NOEXCEPT
    {
        return "4";
    }

    std::uint64_t offset() const SBE_NOEXCEPT
    {
        return m_offset;
    }

    BrokerQueue &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    BrokerQueue &wrapForDecode(
         char *buffer, const std::uint64_t offset, const std::uint64_t actingBlockLength,
         const std::uint64_t actingVersion, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, actingBlockLength, actingVersion);
        return *this;
    }

    std::uint64_t position() const SBE_NOEXCEPT
    {
        return m_position;
    }

    void position(const std::uint64_t position)
    {
        if (SBE_BOUNDS_CHECK_EXPECT((position > m_bufferLength), false))
        {
            throw std::runtime_error("buffer too short [E100]");
        }
        m_position = position;
    }

    std::uint64_t encodedLength() const SBE_NOEXCEPT
    {
        return position() - m_offset;
    }

    char *buffer() SBE_NOEXCEPT
    {
        return m_buffer;
    }

    std::uint64_t bufferLength() const SBE_NOEXCEPT
    {
        return m_bufferLength;
    }

    std::uint64_t actingVersion() const SBE_NOEXCEPT
    {
        return m_actingVersion;
    }

    static SBE_CONSTEXPR std::uint16_t securityCodeId() SBE_NOEXCEPT
    {
        return 101;
    }

    static SBE_CONSTEXPR std::uint64_t securityCodeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool securityCodeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= securityCodeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t securityCodeEncodingOffset() SBE_NOEXCEPT
    {
         return 0;
    }


    static const char *securityCodeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::EPOCH: return "unix";
            case MetaAttribute::TIME_UNIT: return "nanosecond";
            case MetaAttribute::SEMANTIC_TYPE: return "";
            case MetaAttribute::PRESENCE: return "required";
        }

        return "";
    }

    static SBE_CONSTEXPR std::uint32_t securityCodeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t securityCodeMinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t securityCodeMaxValue() SBE_NOEXCEPT
    {
        return 4294967294;
    }

    static SBE_CONSTEXPR std::size_t securityCodeEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t securityCode() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 0)));
    }

    BrokerQueue &securityCode(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    class ItemCount
    {
    private:
        char *m_buffer;
        std::uint64_t m_bufferLength;
        std::uint64_t *m_positionPtr;
        std::uint64_t m_blockLength;
        std::uint64_t m_count;
        std::uint64_t m_index;
        std::uint64_t m_offset;
        std::uint64_t m_actingVersion;
        GroupSize8 m_dimensions;

    public:

        inline void wrapForDecode(char *buffer, std::uint64_t *pos, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
        {
            m_buffer = buffer;
            m_bufferLength = bufferLength;
            m_dimensions.wrap(m_buffer, *pos, actingVersion, bufferLength);
            m_blockLength = m_dimensions.blockLength();
            m_count = m_dimensions.numInGroup();
            m_index = -1;
            m_actingVersion = actingVersion;
            m_positionPtr = pos;
            *m_positionPtr = *m_positionPtr + 4;
        }

        inline void wrapForEncode(char *buffer, const std::uint8_t count, std::uint64_t *pos, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
        {
    #if defined(__GNUG__) && !defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wtype-limits"
    #endif
            if (count < 0 || count > 254)
            {
                throw std::runtime_error("count outside of allowed range [E110]");
            }
    #if defined(__GNUG__) && !defined(__clang__)
    #pragma GCC diagnostic pop
    #endif
            m_buffer = buffer;
            m_bufferLength = bufferLength;
            m_dimensions.wrap(m_buffer, *pos, actingVersion, bufferLength);
            m_dimensions.blockLength((std::uint8_t)4);
            m_dimensions.numInGroup((std::uint8_t)count);
            m_index = -1;
            m_count = count;
            m_blockLength = 4;
            m_actingVersion = actingVersion;
            m_positionPtr = pos;
            *m_positionPtr = *m_positionPtr + 4;
        }

        static SBE_CONSTEXPR std::uint64_t sbeHeaderSize() SBE_NOEXCEPT
        {
            return 4;
        }

        static SBE_CONSTEXPR std::uint64_t sbeBlockLength() SBE_NOEXCEPT
        {
            return 4;
        }

        std::uint64_t position() const
        {
            return *m_positionPtr;
        }

        void position(const std::uint64_t position)
        {
            if (SBE_BOUNDS_CHECK_EXPECT((position > m_bufferLength), false))
            {
                 throw std::runtime_error("buffer too short [E100]");
            }
            *m_positionPtr = position;
        }

        inline std::uint64_t count() const SBE_NOEXCEPT
        {
            return m_count;
        }

        inline bool hasNext() const SBE_NOEXCEPT
        {
            return m_index + 1 < m_count;
        }

        inline ItemCount &next()
        {
            m_offset = *m_positionPtr;
            if (SBE_BOUNDS_CHECK_EXPECT(( (m_offset + m_blockLength) > m_bufferLength ), false))
            {
                throw std::runtime_error("buffer too short to support next group index [E108]");
            }
            *m_positionPtr = m_offset + m_blockLength;
            ++m_index;

            return *this;
        }

    #if __cplusplus < 201103L
        template<class Func> inline void forEach(Func& func)
        {
            while (hasNext())
            {
                next(); func(*this);
            }
        }

    #else
        template<class Func> inline void forEach(Func&& func)
        {
            while (hasNext())
            {
                next(); func(*this);
            }
        }

    #endif


        static SBE_CONSTEXPR std::uint16_t itemId() SBE_NOEXCEPT
        {
            return 103;
        }

        static SBE_CONSTEXPR std::uint64_t itemSinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool itemInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= itemSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t itemEncodingOffset() SBE_NOEXCEPT
        {
             return 0;
        }


        static const char *itemMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
        {
            switch (metaAttribute)
            {
                case MetaAttribute::EPOCH: return "unix";
                case MetaAttribute::TIME_UNIT: return "nanosecond";
                case MetaAttribute::SEMANTIC_TYPE: return "";
                case MetaAttribute::PRESENCE: return "required";
            }

            return "";
        }

        static SBE_CONSTEXPR std::uint16_t itemNullValue() SBE_NOEXCEPT
        {
            return SBE_NULLVALUE_UINT16;
        }

        static SBE_CONSTEXPR std::uint16_t itemMinValue() SBE_NOEXCEPT
        {
            return (std::uint16_t)0;
        }

        static SBE_CONSTEXPR std::uint16_t itemMaxValue() SBE_NOEXCEPT
        {
            return (std::uint16_t)65534;
        }

        static SBE_CONSTEXPR std::size_t itemEncodingLength() SBE_NOEXCEPT
        {
            return 2;
        }

        std::uint16_t item() const
        {
            return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 0)));
        }

        ItemCount &item(const std::uint16_t value)
        {
            *((std::uint16_t *)(m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
            return *this;
        }

        static SBE_CONSTEXPR std::uint16_t typeId() SBE_NOEXCEPT
        {
            return 104;
        }

        static SBE_CONSTEXPR std::uint64_t typeSinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool typeInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= typeSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t typeEncodingOffset() SBE_NOEXCEPT
        {
             return 2;
        }


        static const char *typeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
        {
            switch (metaAttribute)
            {
                case MetaAttribute::EPOCH: return "unix";
                case MetaAttribute::TIME_UNIT: return "nanosecond";
                case MetaAttribute::SEMANTIC_TYPE: return "";
                case MetaAttribute::PRESENCE: return "required";
            }

            return "";
        }

        static SBE_CONSTEXPR char typeNullValue() SBE_NOEXCEPT
        {
            return (char)0;
        }

        static SBE_CONSTEXPR char typeMinValue() SBE_NOEXCEPT
        {
            return (char)32;
        }

        static SBE_CONSTEXPR char typeMaxValue() SBE_NOEXCEPT
        {
            return (char)126;
        }

        static SBE_CONSTEXPR std::size_t typeEncodingLength() SBE_NOEXCEPT
        {
            return 1;
        }

        char type() const
        {
            return (*((char *)(m_buffer + m_offset + 2)));
        }

        ItemCount &type(const char value)
        {
            *((char *)(m_buffer + m_offset + 2)) = (value);
            return *this;
        }

        static SBE_CONSTEXPR std::uint16_t fillerId() SBE_NOEXCEPT
        {
            return 201;
        }

        static SBE_CONSTEXPR std::uint64_t fillerSinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool fillerInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= fillerSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t fillerEncodingOffset() SBE_NOEXCEPT
        {
             return 3;
        }


        static const char *fillerMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
        {
            switch (metaAttribute)
            {
                case MetaAttribute::EPOCH: return "unix";
                case MetaAttribute::TIME_UNIT: return "nanosecond";
                case MetaAttribute::SEMANTIC_TYPE: return "";
                case MetaAttribute::PRESENCE: return "required";
            }

            return "";
        }

        static SBE_CONSTEXPR std::uint8_t fillerNullValue() SBE_NOEXCEPT
        {
            return SBE_NULLVALUE_UINT8;
        }

        static SBE_CONSTEXPR std::uint8_t fillerMinValue() SBE_NOEXCEPT
        {
            return (std::uint8_t)0;
        }

        static SBE_CONSTEXPR std::uint8_t fillerMaxValue() SBE_NOEXCEPT
        {
            return (std::uint8_t)254;
        }

        static SBE_CONSTEXPR std::size_t fillerEncodingLength() SBE_NOEXCEPT
        {
            return 1;
        }

        std::uint8_t filler() const
        {
            return (*((std::uint8_t *)(m_buffer + m_offset + 3)));
        }

        ItemCount &filler(const std::uint8_t value)
        {
            *((std::uint8_t *)(m_buffer + m_offset + 3)) = (value);
            return *this;
        }
    };

private:
    ItemCount m_itemCount;

public:

    static SBE_CONSTEXPR std::uint16_t itemCountId() SBE_NOEXCEPT
    {
        return 102;
    }


    inline ItemCount &itemCount()
    {
        m_itemCount.wrapForDecode(m_buffer, m_positionPtr, m_actingVersion, m_bufferLength);
        return m_itemCount;
    }

    ItemCount &itemCountCount(const std::uint8_t count)
    {
        m_itemCount.wrapForEncode(m_buffer, count, m_positionPtr, m_actingVersion, m_bufferLength);
        return m_itemCount;
    }

    static SBE_CONSTEXPR std::uint64_t itemCountSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool itemCountInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= itemCountSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }
};
}
}
#endif
