/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDCC_SBE_STATISTICS_H_
#define _OMDCC_SBE_STATISTICS_H_

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

using namespace sbe;

namespace omdcc {
namespace sbe {

class Statistics
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

    inline void reset(const Statistics& codec)
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

    Statistics() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    Statistics(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    Statistics(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    Statistics(const Statistics& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    Statistics(Statistics&& codec)
    {
        reset(codec);
    }

    Statistics& operator=(Statistics&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    Statistics& operator=(const Statistics& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)48;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)660;
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

    Statistics &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    Statistics &wrapForDecode(
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

    Statistics &securityCode(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sharesTradedId() SBE_NOEXCEPT
    {
        return 102;
    }

    static SBE_CONSTEXPR std::uint64_t sharesTradedSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool sharesTradedInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= sharesTradedSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t sharesTradedEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }


    static const char *sharesTradedMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint64_t sharesTradedNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT64;
    }

    static SBE_CONSTEXPR std::uint64_t sharesTradedMinValue() SBE_NOEXCEPT
    {
        return 0x0L;
    }

    static SBE_CONSTEXPR std::uint64_t sharesTradedMaxValue() SBE_NOEXCEPT
    {
        return 0xfffffffffffffffeL;
    }

    static SBE_CONSTEXPR std::size_t sharesTradedEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    std::uint64_t sharesTraded() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::uint64_t *)(m_buffer + m_offset + 4)));
    }

    Statistics &sharesTraded(const std::uint64_t value)
    {
        *((std::uint64_t *)(m_buffer + m_offset + 4)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t turnoverId() SBE_NOEXCEPT
    {
        return 103;
    }

    static SBE_CONSTEXPR std::uint64_t turnoverSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool turnoverInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= turnoverSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t turnoverEncodingOffset() SBE_NOEXCEPT
    {
         return 12;
    }


    static const char *turnoverMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int64_t turnoverNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT64;
    }

    static SBE_CONSTEXPR std::int64_t turnoverMinValue() SBE_NOEXCEPT
    {
        return -9223372036854775807L;
    }

    static SBE_CONSTEXPR std::int64_t turnoverMaxValue() SBE_NOEXCEPT
    {
        return 9223372036854775807L;
    }

    static SBE_CONSTEXPR std::size_t turnoverEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    std::int64_t turnover() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::int64_t *)(m_buffer + m_offset + 12)));
    }

    Statistics &turnover(const std::int64_t value)
    {
        *((std::int64_t *)(m_buffer + m_offset + 12)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t highPriceId() SBE_NOEXCEPT
    {
        return 104;
    }

    static SBE_CONSTEXPR std::uint64_t highPriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool highPriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= highPriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t highPriceEncodingOffset() SBE_NOEXCEPT
    {
         return 20;
    }


    static const char *highPriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t highPriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t highPriceMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t highPriceMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t highPriceEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t highPrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 20)));
    }

    Statistics &highPrice(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 20)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t lowPriceId() SBE_NOEXCEPT
    {
        return 105;
    }

    static SBE_CONSTEXPR std::uint64_t lowPriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool lowPriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= lowPriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t lowPriceEncodingOffset() SBE_NOEXCEPT
    {
         return 24;
    }


    static const char *lowPriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t lowPriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t lowPriceMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t lowPriceMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t lowPriceEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t lowPrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 24)));
    }

    Statistics &lowPrice(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 24)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t lastPriceId() SBE_NOEXCEPT
    {
        return 106;
    }

    static SBE_CONSTEXPR std::uint64_t lastPriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool lastPriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= lastPriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t lastPriceEncodingOffset() SBE_NOEXCEPT
    {
         return 28;
    }


    static const char *lastPriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t lastPriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t lastPriceMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t lastPriceMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t lastPriceEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t lastPrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 28)));
    }

    Statistics &lastPrice(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 28)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t openingPriceId() SBE_NOEXCEPT
    {
        return 107;
    }

    static SBE_CONSTEXPR std::uint64_t openingPriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool openingPriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= openingPriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t openingPriceEncodingOffset() SBE_NOEXCEPT
    {
         return 32;
    }


    static const char *openingPriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t openingPriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t openingPriceMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t openingPriceMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t openingPriceEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t openingPrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 32)));
    }

    Statistics &openingPrice(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 32)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
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
         return 36;
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

    static SBE_CONSTEXPR char fillerNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char fillerMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char fillerMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t fillerEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t fillerLength() SBE_NOEXCEPT
    {
        return 12;
    }

    const char *filler() const
    {
        return (m_buffer + m_offset + 36);
    }

    char filler(const std::uint64_t index) const
    {
        if (index >= 12)
        {
            throw std::runtime_error("index out of range for filler [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 36 + (index * 1))));
    }

    void filler(const std::uint64_t index, const char value)
    {
        if (index >= 12)
        {
            throw std::runtime_error("index out of range for filler [E105]");
        }

        *((char *)(m_buffer + m_offset + 36 + (index * 1))) = (value);
    }

    std::uint64_t getFiller(char *dst, const std::uint64_t length) const
    {
        if (length > 12)
        {
             throw std::runtime_error("length too large for getFiller [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 36, sizeof(char) * length);
        return length;
    }

    Statistics &putFiller(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 36, src, sizeof(char) * 12);
        return *this;
    }

    std::string getFillerAsString() const
    {
        std::string result(m_buffer + m_offset + 36, 12);
        return result;
    }

    Statistics &putFiller(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 36, str.c_str(), 12);
        return *this;
    }

};
}
}
#endif
