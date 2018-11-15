/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDD_SBE_AGGREGATEORDERBOOKUPDATE_H_
#define _OMDD_SBE_AGGREGATEORDERBOOKUPDATE_H_

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

using namespace sbe;

namespace omdd {
namespace sbe {

class AggregateOrderBookUpdate
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

    inline void reset(const AggregateOrderBookUpdate& codec)
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

    AggregateOrderBookUpdate() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    AggregateOrderBookUpdate(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    AggregateOrderBookUpdate(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    AggregateOrderBookUpdate(const AggregateOrderBookUpdate& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    AggregateOrderBookUpdate(AggregateOrderBookUpdate&& codec)
    {
        reset(codec);
    }

    AggregateOrderBookUpdate& operator=(AggregateOrderBookUpdate&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    AggregateOrderBookUpdate& operator=(const AggregateOrderBookUpdate& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)7;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)353;
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

    AggregateOrderBookUpdate &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    AggregateOrderBookUpdate &wrapForDecode(
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

    static SBE_CONSTEXPR std::uint16_t orderbookIDId() SBE_NOEXCEPT
    {
        return 101;
    }

    static SBE_CONSTEXPR std::uint64_t orderbookIDSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool orderbookIDInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= orderbookIDSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t orderbookIDEncodingOffset() SBE_NOEXCEPT
    {
         return 0;
    }


    static const char *orderbookIDMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint32_t orderbookIDNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t orderbookIDMinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t orderbookIDMaxValue() SBE_NOEXCEPT
    {
        return 4294967294;
    }

    static SBE_CONSTEXPR std::size_t orderbookIDEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t orderbookID() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 0)));
    }

    AggregateOrderBookUpdate &orderbookID(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t filler1Id() SBE_NOEXCEPT
    {
        return 201;
    }

    static SBE_CONSTEXPR std::uint64_t filler1SinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool filler1InActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= filler1SinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t filler1EncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }


    static const char *filler1MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char filler1NullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char filler1MinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char filler1MaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t filler1EncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t filler1Length() SBE_NOEXCEPT
    {
        return 3;
    }

    const char *filler1() const
    {
        return (m_buffer + m_offset + 4);
    }

    char filler1(const std::uint64_t index) const
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for filler1 [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 4 + (index * 1))));
    }

    void filler1(const std::uint64_t index, const char value)
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for filler1 [E105]");
        }

        *((char *)(m_buffer + m_offset + 4 + (index * 1))) = (value);
    }

    std::uint64_t getFiller1(char *dst, const std::uint64_t length) const
    {
        if (length > 3)
        {
             throw std::runtime_error("length too large for getFiller1 [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 4, sizeof(char) * length);
        return length;
    }

    AggregateOrderBookUpdate &putFiller1(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 4, src, sizeof(char) * 3);
        return *this;
    }

    std::string getFiller1AsString() const
    {
        std::string result(m_buffer + m_offset + 4, 3);
        return result;
    }

    AggregateOrderBookUpdate &putFiller1(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 4, str.c_str(), 3);
        return *this;
    }


    class NoEntries
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
            m_dimensions.blockLength((std::uint8_t)24);
            m_dimensions.numInGroup((std::uint8_t)count);
            m_index = -1;
            m_count = count;
            m_blockLength = 24;
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
            return 24;
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

        inline NoEntries &next()
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


        static SBE_CONSTEXPR std::uint16_t aggregateQuantityId() SBE_NOEXCEPT
        {
            return 103;
        }

        static SBE_CONSTEXPR std::uint64_t aggregateQuantitySinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool aggregateQuantityInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= aggregateQuantitySinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t aggregateQuantityEncodingOffset() SBE_NOEXCEPT
        {
             return 0;
        }


        static const char *aggregateQuantityMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

        static SBE_CONSTEXPR std::uint64_t aggregateQuantityNullValue() SBE_NOEXCEPT
        {
            return SBE_NULLVALUE_UINT64;
        }

        static SBE_CONSTEXPR std::uint64_t aggregateQuantityMinValue() SBE_NOEXCEPT
        {
            return 0x0L;
        }

        static SBE_CONSTEXPR std::uint64_t aggregateQuantityMaxValue() SBE_NOEXCEPT
        {
            return 0xfffffffffffffffeL;
        }

        static SBE_CONSTEXPR std::size_t aggregateQuantityEncodingLength() SBE_NOEXCEPT
        {
            return 8;
        }

        std::uint64_t aggregateQuantity() const
        {
            return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::uint64_t *)(m_buffer + m_offset + 0)));
        }

        NoEntries &aggregateQuantity(const std::uint64_t value)
        {
            *((std::uint64_t *)(m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
            return *this;
        }

        static SBE_CONSTEXPR std::uint16_t priceId() SBE_NOEXCEPT
        {
            return 104;
        }

        static SBE_CONSTEXPR std::uint64_t priceSinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool priceInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= priceSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t priceEncodingOffset() SBE_NOEXCEPT
        {
             return 8;
        }


        static const char *priceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

        static SBE_CONSTEXPR std::int32_t priceNullValue() SBE_NOEXCEPT
        {
            return SBE_NULLVALUE_INT32;
        }

        static SBE_CONSTEXPR std::int32_t priceMinValue() SBE_NOEXCEPT
        {
            return -2147483647;
        }

        static SBE_CONSTEXPR std::int32_t priceMaxValue() SBE_NOEXCEPT
        {
            return 2147483647;
        }

        static SBE_CONSTEXPR std::size_t priceEncodingLength() SBE_NOEXCEPT
        {
            return 4;
        }

        std::int32_t price() const
        {
            return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 8)));
        }

        NoEntries &price(const std::int32_t value)
        {
            *((std::int32_t *)(m_buffer + m_offset + 8)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
            return *this;
        }

        static SBE_CONSTEXPR std::uint16_t numberOfOrdersId() SBE_NOEXCEPT
        {
            return 105;
        }

        static SBE_CONSTEXPR std::uint64_t numberOfOrdersSinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool numberOfOrdersInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= numberOfOrdersSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t numberOfOrdersEncodingOffset() SBE_NOEXCEPT
        {
             return 12;
        }


        static const char *numberOfOrdersMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

        static SBE_CONSTEXPR std::uint32_t numberOfOrdersNullValue() SBE_NOEXCEPT
        {
            return SBE_NULLVALUE_UINT32;
        }

        static SBE_CONSTEXPR std::uint32_t numberOfOrdersMinValue() SBE_NOEXCEPT
        {
            return 0;
        }

        static SBE_CONSTEXPR std::uint32_t numberOfOrdersMaxValue() SBE_NOEXCEPT
        {
            return 4294967294;
        }

        static SBE_CONSTEXPR std::size_t numberOfOrdersEncodingLength() SBE_NOEXCEPT
        {
            return 4;
        }

        std::uint32_t numberOfOrders() const
        {
            return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 12)));
        }

        NoEntries &numberOfOrders(const std::uint32_t value)
        {
            *((std::uint32_t *)(m_buffer + m_offset + 12)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
            return *this;
        }

        static SBE_CONSTEXPR std::uint16_t sideId() SBE_NOEXCEPT
        {
            return 106;
        }

        static SBE_CONSTEXPR std::uint64_t sideSinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool sideInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= sideSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t sideEncodingOffset() SBE_NOEXCEPT
        {
             return 16;
        }


        static const char *sideMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

        static SBE_CONSTEXPR std::uint8_t sideNullValue() SBE_NOEXCEPT
        {
            return SBE_NULLVALUE_UINT8;
        }

        static SBE_CONSTEXPR std::uint8_t sideMinValue() SBE_NOEXCEPT
        {
            return (std::uint8_t)0;
        }

        static SBE_CONSTEXPR std::uint8_t sideMaxValue() SBE_NOEXCEPT
        {
            return (std::uint8_t)254;
        }

        static SBE_CONSTEXPR std::size_t sideEncodingLength() SBE_NOEXCEPT
        {
            return 1;
        }

        std::uint8_t side() const
        {
            return (*((std::uint8_t *)(m_buffer + m_offset + 16)));
        }

        NoEntries &side(const std::uint8_t value)
        {
            *((std::uint8_t *)(m_buffer + m_offset + 16)) = (value);
            return *this;
        }

        static SBE_CONSTEXPR std::uint16_t filler2Id() SBE_NOEXCEPT
        {
            return 202;
        }

        static SBE_CONSTEXPR std::uint64_t filler2SinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool filler2InActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= filler2SinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t filler2EncodingOffset() SBE_NOEXCEPT
        {
             return 17;
        }


        static const char *filler2MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

        static SBE_CONSTEXPR char filler2NullValue() SBE_NOEXCEPT
        {
            return (char)0;
        }

        static SBE_CONSTEXPR char filler2MinValue() SBE_NOEXCEPT
        {
            return (char)32;
        }

        static SBE_CONSTEXPR char filler2MaxValue() SBE_NOEXCEPT
        {
            return (char)126;
        }

        static SBE_CONSTEXPR std::size_t filler2EncodingLength() SBE_NOEXCEPT
        {
            return 1;
        }

        char filler2() const
        {
            return (*((char *)(m_buffer + m_offset + 17)));
        }

        NoEntries &filler2(const char value)
        {
            *((char *)(m_buffer + m_offset + 17)) = (value);
            return *this;
        }

        static SBE_CONSTEXPR std::uint16_t priceLevelId() SBE_NOEXCEPT
        {
            return 107;
        }

        static SBE_CONSTEXPR std::uint64_t priceLevelSinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool priceLevelInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= priceLevelSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t priceLevelEncodingOffset() SBE_NOEXCEPT
        {
             return 18;
        }


        static const char *priceLevelMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

        static SBE_CONSTEXPR std::uint8_t priceLevelNullValue() SBE_NOEXCEPT
        {
            return SBE_NULLVALUE_UINT8;
        }

        static SBE_CONSTEXPR std::uint8_t priceLevelMinValue() SBE_NOEXCEPT
        {
            return (std::uint8_t)0;
        }

        static SBE_CONSTEXPR std::uint8_t priceLevelMaxValue() SBE_NOEXCEPT
        {
            return (std::uint8_t)254;
        }

        static SBE_CONSTEXPR std::size_t priceLevelEncodingLength() SBE_NOEXCEPT
        {
            return 1;
        }

        std::uint8_t priceLevel() const
        {
            return (*((std::uint8_t *)(m_buffer + m_offset + 18)));
        }

        NoEntries &priceLevel(const std::uint8_t value)
        {
            *((std::uint8_t *)(m_buffer + m_offset + 18)) = (value);
            return *this;
        }

        static SBE_CONSTEXPR std::uint16_t updateActionId() SBE_NOEXCEPT
        {
            return 108;
        }

        static SBE_CONSTEXPR std::uint64_t updateActionSinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool updateActionInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= updateActionSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t updateActionEncodingOffset() SBE_NOEXCEPT
        {
             return 19;
        }


        static const char *updateActionMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

        static SBE_CONSTEXPR std::uint8_t updateActionNullValue() SBE_NOEXCEPT
        {
            return SBE_NULLVALUE_UINT8;
        }

        static SBE_CONSTEXPR std::uint8_t updateActionMinValue() SBE_NOEXCEPT
        {
            return (std::uint8_t)0;
        }

        static SBE_CONSTEXPR std::uint8_t updateActionMaxValue() SBE_NOEXCEPT
        {
            return (std::uint8_t)254;
        }

        static SBE_CONSTEXPR std::size_t updateActionEncodingLength() SBE_NOEXCEPT
        {
            return 1;
        }

        std::uint8_t updateAction() const
        {
            return (*((std::uint8_t *)(m_buffer + m_offset + 19)));
        }

        NoEntries &updateAction(const std::uint8_t value)
        {
            *((std::uint8_t *)(m_buffer + m_offset + 19)) = (value);
            return *this;
        }

        static SBE_CONSTEXPR std::uint16_t filler3Id() SBE_NOEXCEPT
        {
            return 203;
        }

        static SBE_CONSTEXPR std::uint64_t filler3SinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool filler3InActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= filler3SinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t filler3EncodingOffset() SBE_NOEXCEPT
        {
             return 20;
        }


        static const char *filler3MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

        static SBE_CONSTEXPR std::uint32_t filler3NullValue() SBE_NOEXCEPT
        {
            return SBE_NULLVALUE_UINT32;
        }

        static SBE_CONSTEXPR std::uint32_t filler3MinValue() SBE_NOEXCEPT
        {
            return 0;
        }

        static SBE_CONSTEXPR std::uint32_t filler3MaxValue() SBE_NOEXCEPT
        {
            return 4294967294;
        }

        static SBE_CONSTEXPR std::size_t filler3EncodingLength() SBE_NOEXCEPT
        {
            return 4;
        }

        std::uint32_t filler3() const
        {
            return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 20)));
        }

        NoEntries &filler3(const std::uint32_t value)
        {
            *((std::uint32_t *)(m_buffer + m_offset + 20)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
            return *this;
        }
    };

private:
    NoEntries m_noEntries;

public:

    static SBE_CONSTEXPR std::uint16_t NoEntriesId() SBE_NOEXCEPT
    {
        return 102;
    }


    inline NoEntries &noEntries()
    {
        m_noEntries.wrapForDecode(m_buffer, m_positionPtr, m_actingVersion, m_bufferLength);
        return m_noEntries;
    }

    NoEntries &noEntriesCount(const std::uint8_t count)
    {
        m_noEntries.wrapForEncode(m_buffer, count, m_positionPtr, m_actingVersion, m_bufferLength);
        return m_noEntries;
    }

    static SBE_CONSTEXPR std::uint64_t noEntriesSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool noEntriesInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= noEntriesSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }
};
}
}
#endif
