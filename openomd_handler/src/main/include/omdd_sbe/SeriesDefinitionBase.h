/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDD_SBE_SERIESDEFINITIONBASE_H_
#define _OMDD_SBE_SERIESDEFINITIONBASE_H_

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
#include "GroupSize8Reverse.h"
#include "GroupSize8.h"

using namespace sbe;

namespace omdd {
namespace sbe {

class SeriesDefinitionBase
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

    inline void reset(const SeriesDefinitionBase& codec)
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

    SeriesDefinitionBase() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    SeriesDefinitionBase(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    SeriesDefinitionBase(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    SeriesDefinitionBase(const SeriesDefinitionBase& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    SeriesDefinitionBase(SeriesDefinitionBase&& codec)
    {
        reset(codec);
    }

    SeriesDefinitionBase& operator=(SeriesDefinitionBase&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    SeriesDefinitionBase& operator=(const SeriesDefinitionBase& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)56;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)303;
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

    SeriesDefinitionBase &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    SeriesDefinitionBase &wrapForDecode(
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

    SeriesDefinitionBase &orderbookID(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t symbolId() SBE_NOEXCEPT
    {
        return 102;
    }

    static SBE_CONSTEXPR std::uint64_t symbolSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool symbolInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= symbolSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t symbolEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }


    static const char *symbolMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char symbolNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char symbolMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char symbolMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t symbolEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t symbolLength() SBE_NOEXCEPT
    {
        return 32;
    }

    const char *symbol() const
    {
        return (m_buffer + m_offset + 4);
    }

    char symbol(const std::uint64_t index) const
    {
        if (index >= 32)
        {
            throw std::runtime_error("index out of range for symbol [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 4 + (index * 1))));
    }

    void symbol(const std::uint64_t index, const char value)
    {
        if (index >= 32)
        {
            throw std::runtime_error("index out of range for symbol [E105]");
        }

        *((char *)(m_buffer + m_offset + 4 + (index * 1))) = (value);
    }

    std::uint64_t getSymbol(char *dst, const std::uint64_t length) const
    {
        if (length > 32)
        {
             throw std::runtime_error("length too large for getSymbol [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 4, sizeof(char) * length);
        return length;
    }

    SeriesDefinitionBase &putSymbol(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 4, src, sizeof(char) * 32);
        return *this;
    }

    std::string getSymbolAsString() const
    {
        std::string result(m_buffer + m_offset + 4, 32);
        return result;
    }

    SeriesDefinitionBase &putSymbol(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 4, str.c_str(), 32);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t financialProductId() SBE_NOEXCEPT
    {
        return 103;
    }

    static SBE_CONSTEXPR std::uint64_t financialProductSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool financialProductInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= financialProductSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t financialProductEncodingOffset() SBE_NOEXCEPT
    {
         return 36;
    }


    static const char *financialProductMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t financialProductNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t financialProductMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t financialProductMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t financialProductEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t financialProduct() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 36)));
    }

    SeriesDefinitionBase &financialProduct(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 36)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t numberOfDecimalsPriceId() SBE_NOEXCEPT
    {
        return 104;
    }

    static SBE_CONSTEXPR std::uint64_t numberOfDecimalsPriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool numberOfDecimalsPriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= numberOfDecimalsPriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t numberOfDecimalsPriceEncodingOffset() SBE_NOEXCEPT
    {
         return 37;
    }


    static const char *numberOfDecimalsPriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t numberOfDecimalsPriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t numberOfDecimalsPriceMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t numberOfDecimalsPriceMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t numberOfDecimalsPriceEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t numberOfDecimalsPrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 37)));
    }

    SeriesDefinitionBase &numberOfDecimalsPrice(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 37)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t numberOfLegsId() SBE_NOEXCEPT
    {
        return 105;
    }

    static SBE_CONSTEXPR std::uint64_t numberOfLegsSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool numberOfLegsInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= numberOfLegsSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t numberOfLegsEncodingOffset() SBE_NOEXCEPT
    {
         return 39;
    }


    static const char *numberOfLegsMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t numberOfLegsNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t numberOfLegsMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t numberOfLegsMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t numberOfLegsEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t numberOfLegs() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 39)));
    }

    SeriesDefinitionBase &numberOfLegs(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 39)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t strikePriceId() SBE_NOEXCEPT
    {
        return 106;
    }

    static SBE_CONSTEXPR std::uint64_t strikePriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool strikePriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= strikePriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t strikePriceEncodingOffset() SBE_NOEXCEPT
    {
         return 40;
    }


    static const char *strikePriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t strikePriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t strikePriceMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t strikePriceMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t strikePriceEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t strikePrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 40)));
    }

    SeriesDefinitionBase &strikePrice(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 40)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t expirationDateId() SBE_NOEXCEPT
    {
        return 107;
    }

    static SBE_CONSTEXPR std::uint64_t expirationDateSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool expirationDateInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= expirationDateSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t expirationDateEncodingOffset() SBE_NOEXCEPT
    {
         return 44;
    }


    static const char *expirationDateMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char expirationDateNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char expirationDateMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char expirationDateMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t expirationDateEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t expirationDateLength() SBE_NOEXCEPT
    {
        return 8;
    }

    const char *expirationDate() const
    {
        return (m_buffer + m_offset + 44);
    }

    char expirationDate(const std::uint64_t index) const
    {
        if (index >= 8)
        {
            throw std::runtime_error("index out of range for expirationDate [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 44 + (index * 1))));
    }

    void expirationDate(const std::uint64_t index, const char value)
    {
        if (index >= 8)
        {
            throw std::runtime_error("index out of range for expirationDate [E105]");
        }

        *((char *)(m_buffer + m_offset + 44 + (index * 1))) = (value);
    }

    std::uint64_t getExpirationDate(char *dst, const std::uint64_t length) const
    {
        if (length > 8)
        {
             throw std::runtime_error("length too large for getExpirationDate [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 44, sizeof(char) * length);
        return length;
    }

    SeriesDefinitionBase &putExpirationDate(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 44, src, sizeof(char) * 8);
        return *this;
    }

    std::string getExpirationDateAsString() const
    {
        std::string result(m_buffer + m_offset + 44, 8);
        return result;
    }

    SeriesDefinitionBase &putExpirationDate(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 44, str.c_str(), 8);
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
         return 52;
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

    static SBE_CONSTEXPR std::uint16_t filler1NullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t filler1MinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t filler1MaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t filler1EncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t filler1() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 52)));
    }

    SeriesDefinitionBase &filler1(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 52)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t putOrCallId() SBE_NOEXCEPT
    {
        return 108;
    }

    static SBE_CONSTEXPR std::uint64_t putOrCallSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool putOrCallInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= putOrCallSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t putOrCallEncodingOffset() SBE_NOEXCEPT
    {
         return 54;
    }


    static const char *putOrCallMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t putOrCallNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t putOrCallMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t putOrCallMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t putOrCallEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t putOrCall() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 54)));
    }

    SeriesDefinitionBase &putOrCall(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 54)) = (value);
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
         return 55;
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

    static SBE_CONSTEXPR std::uint8_t filler2NullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t filler2MinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t filler2MaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t filler2EncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t filler2() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 55)));
    }

    SeriesDefinitionBase &filler2(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 55)) = (value);
        return *this;
    }
};
}
}
#endif
