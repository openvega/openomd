/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDD_SBE_COMMODITYDEFINITION_H_
#define _OMDD_SBE_COMMODITYDEFINITION_H_

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

class CommodityDefinition
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

    inline void reset(const CommodityDefinition& codec)
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

    CommodityDefinition() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    CommodityDefinition(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    CommodityDefinition(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    CommodityDefinition(const CommodityDefinition& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    CommodityDefinition(CommodityDefinition&& codec)
    {
        reset(codec);
    }

    CommodityDefinition& operator=(CommodityDefinition&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    CommodityDefinition& operator=(const CommodityDefinition& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)90;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)301;
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

    CommodityDefinition &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    CommodityDefinition &wrapForDecode(
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

    static SBE_CONSTEXPR std::uint16_t commodityCodeId() SBE_NOEXCEPT
    {
        return 101;
    }

    static SBE_CONSTEXPR std::uint64_t commodityCodeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool commodityCodeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= commodityCodeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t commodityCodeEncodingOffset() SBE_NOEXCEPT
    {
         return 0;
    }


    static const char *commodityCodeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t commodityCodeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t commodityCodeMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t commodityCodeMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t commodityCodeEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t commodityCode() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 0)));
    }

    CommodityDefinition &commodityCode(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t decimalInUnderlyingPriceId() SBE_NOEXCEPT
    {
        return 102;
    }

    static SBE_CONSTEXPR std::uint64_t decimalInUnderlyingPriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool decimalInUnderlyingPriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= decimalInUnderlyingPriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t decimalInUnderlyingPriceEncodingOffset() SBE_NOEXCEPT
    {
         return 2;
    }


    static const char *DecimalInUnderlyingPriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t decimalInUnderlyingPriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t decimalInUnderlyingPriceMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t decimalInUnderlyingPriceMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t decimalInUnderlyingPriceEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t decimalInUnderlyingPrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 2)));
    }

    CommodityDefinition &decimalInUnderlyingPrice(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 2)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t isinCodeId() SBE_NOEXCEPT
    {
        return 103;
    }

    static SBE_CONSTEXPR std::uint64_t isinCodeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool isinCodeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= isinCodeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t isinCodeEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }


    static const char *isinCodeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char isinCodeNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char isinCodeMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char isinCodeMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t isinCodeEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t isinCodeLength() SBE_NOEXCEPT
    {
        return 12;
    }

    const char *isinCode() const
    {
        return (m_buffer + m_offset + 4);
    }

    char isinCode(const std::uint64_t index) const
    {
        if (index >= 12)
        {
            throw std::runtime_error("index out of range for isinCode [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 4 + (index * 1))));
    }

    void isinCode(const std::uint64_t index, const char value)
    {
        if (index >= 12)
        {
            throw std::runtime_error("index out of range for isinCode [E105]");
        }

        *((char *)(m_buffer + m_offset + 4 + (index * 1))) = (value);
    }

    std::uint64_t getIsinCode(char *dst, const std::uint64_t length) const
    {
        if (length > 12)
        {
             throw std::runtime_error("length too large for getIsinCode [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 4, sizeof(char) * length);
        return length;
    }

    CommodityDefinition &putIsinCode(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 4, src, sizeof(char) * 12);
        return *this;
    }

    std::string getIsinCodeAsString() const
    {
        std::string result(m_buffer + m_offset + 4, 12);
        return result;
    }

    CommodityDefinition &putIsinCode(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 4, str.c_str(), 12);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t baseCurrencyId() SBE_NOEXCEPT
    {
        return 104;
    }

    static SBE_CONSTEXPR std::uint64_t baseCurrencySinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool baseCurrencyInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= baseCurrencySinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t baseCurrencyEncodingOffset() SBE_NOEXCEPT
    {
         return 16;
    }


    static const char *baseCurrencyMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char baseCurrencyNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char baseCurrencyMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char baseCurrencyMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t baseCurrencyEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t baseCurrencyLength() SBE_NOEXCEPT
    {
        return 3;
    }

    const char *baseCurrency() const
    {
        return (m_buffer + m_offset + 16);
    }

    char baseCurrency(const std::uint64_t index) const
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for baseCurrency [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 16 + (index * 1))));
    }

    void baseCurrency(const std::uint64_t index, const char value)
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for baseCurrency [E105]");
        }

        *((char *)(m_buffer + m_offset + 16 + (index * 1))) = (value);
    }

    std::uint64_t getBaseCurrency(char *dst, const std::uint64_t length) const
    {
        if (length > 3)
        {
             throw std::runtime_error("length too large for getBaseCurrency [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 16, sizeof(char) * length);
        return length;
    }

    CommodityDefinition &putBaseCurrency(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 16, src, sizeof(char) * 3);
        return *this;
    }

    std::string getBaseCurrencyAsString() const
    {
        std::string result(m_buffer + m_offset + 16, 3);
        return result;
    }

    CommodityDefinition &putBaseCurrency(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 16, str.c_str(), 3);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t underlyingPriceUnitId() SBE_NOEXCEPT
    {
        return 105;
    }

    static SBE_CONSTEXPR std::uint64_t underlyingPriceUnitSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool underlyingPriceUnitInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= underlyingPriceUnitSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t underlyingPriceUnitEncodingOffset() SBE_NOEXCEPT
    {
         return 19;
    }


    static const char *underlyingPriceUnitMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t underlyingPriceUnitNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t underlyingPriceUnitMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t underlyingPriceUnitMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t underlyingPriceUnitEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t underlyingPriceUnit() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 19)));
    }

    CommodityDefinition &underlyingPriceUnit(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 19)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t commodityNameId() SBE_NOEXCEPT
    {
        return 106;
    }

    static SBE_CONSTEXPR std::uint64_t commodityNameSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool commodityNameInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= commodityNameSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t commodityNameEncodingOffset() SBE_NOEXCEPT
    {
         return 20;
    }


    static const char *commodityNameMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char commodityNameNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char commodityNameMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char commodityNameMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t commodityNameEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t commodityNameLength() SBE_NOEXCEPT
    {
        return 32;
    }

    const char *commodityName() const
    {
        return (m_buffer + m_offset + 20);
    }

    char commodityName(const std::uint64_t index) const
    {
        if (index >= 32)
        {
            throw std::runtime_error("index out of range for commodityName [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 20 + (index * 1))));
    }

    void commodityName(const std::uint64_t index, const char value)
    {
        if (index >= 32)
        {
            throw std::runtime_error("index out of range for commodityName [E105]");
        }

        *((char *)(m_buffer + m_offset + 20 + (index * 1))) = (value);
    }

    std::uint64_t getCommodityName(char *dst, const std::uint64_t length) const
    {
        if (length > 32)
        {
             throw std::runtime_error("length too large for getCommodityName [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 20, sizeof(char) * length);
        return length;
    }

    CommodityDefinition &putCommodityName(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 20, src, sizeof(char) * 32);
        return *this;
    }

    std::string getCommodityNameAsString() const
    {
        std::string result(m_buffer + m_offset + 20, 32);
        return result;
    }

    CommodityDefinition &putCommodityName(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 20, str.c_str(), 32);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t nominalValueId() SBE_NOEXCEPT
    {
        return 107;
    }

    static SBE_CONSTEXPR std::uint64_t nominalValueSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool nominalValueInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= nominalValueSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t nominalValueEncodingOffset() SBE_NOEXCEPT
    {
         return 52;
    }


    static const char *nominalValueMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int64_t nominalValueNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT64;
    }

    static SBE_CONSTEXPR std::int64_t nominalValueMinValue() SBE_NOEXCEPT
    {
        return -9223372036854775807L;
    }

    static SBE_CONSTEXPR std::int64_t nominalValueMaxValue() SBE_NOEXCEPT
    {
        return 9223372036854775807L;
    }

    static SBE_CONSTEXPR std::size_t nominalValueEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    std::int64_t nominalValue() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::int64_t *)(m_buffer + m_offset + 52)));
    }

    CommodityDefinition &nominalValue(const std::int64_t value)
    {
        *((std::int64_t *)(m_buffer + m_offset + 52)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t underlyingCodeId() SBE_NOEXCEPT
    {
        return 108;
    }

    static SBE_CONSTEXPR std::uint64_t underlyingCodeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool underlyingCodeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= underlyingCodeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t underlyingCodeEncodingOffset() SBE_NOEXCEPT
    {
         return 60;
    }


    static const char *underlyingCodeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char underlyingCodeNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char underlyingCodeMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char underlyingCodeMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t underlyingCodeEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t underlyingCodeLength() SBE_NOEXCEPT
    {
        return 20;
    }

    const char *underlyingCode() const
    {
        return (m_buffer + m_offset + 60);
    }

    char underlyingCode(const std::uint64_t index) const
    {
        if (index >= 20)
        {
            throw std::runtime_error("index out of range for underlyingCode [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 60 + (index * 1))));
    }

    void underlyingCode(const std::uint64_t index, const char value)
    {
        if (index >= 20)
        {
            throw std::runtime_error("index out of range for underlyingCode [E105]");
        }

        *((char *)(m_buffer + m_offset + 60 + (index * 1))) = (value);
    }

    std::uint64_t getUnderlyingCode(char *dst, const std::uint64_t length) const
    {
        if (length > 20)
        {
             throw std::runtime_error("length too large for getUnderlyingCode [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 60, sizeof(char) * length);
        return length;
    }

    CommodityDefinition &putUnderlyingCode(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 60, src, sizeof(char) * 20);
        return *this;
    }

    std::string getUnderlyingCodeAsString() const
    {
        std::string result(m_buffer + m_offset + 60, 20);
        return result;
    }

    CommodityDefinition &putUnderlyingCode(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 60, str.c_str(), 20);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t underlyingTypeId() SBE_NOEXCEPT
    {
        return 109;
    }

    static SBE_CONSTEXPR std::uint64_t underlyingTypeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool underlyingTypeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= underlyingTypeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t underlyingTypeEncodingOffset() SBE_NOEXCEPT
    {
         return 80;
    }


    static const char *underlyingTypeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t underlyingTypeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t underlyingTypeMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t underlyingTypeMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t underlyingTypeEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t underlyingType() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 80)));
    }

    CommodityDefinition &underlyingType(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 80)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t effectiveTomorrowId() SBE_NOEXCEPT
    {
        return 110;
    }

    static SBE_CONSTEXPR std::uint64_t effectiveTomorrowSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool effectiveTomorrowInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= effectiveTomorrowSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t effectiveTomorrowEncodingOffset() SBE_NOEXCEPT
    {
         return 81;
    }


    static const char *effectiveTomorrowMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t effectiveTomorrowNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t effectiveTomorrowMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t effectiveTomorrowMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t effectiveTomorrowEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t effectiveTomorrow() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 81)));
    }

    CommodityDefinition &effectiveTomorrow(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 81)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t commodityIDId() SBE_NOEXCEPT
    {
        return 111;
    }

    static SBE_CONSTEXPR std::uint64_t commodityIDSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool commodityIDInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= commodityIDSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t commodityIDEncodingOffset() SBE_NOEXCEPT
    {
         return 82;
    }


    static const char *commodityIDMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char commodityIDNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char commodityIDMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char commodityIDMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t commodityIDEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t commodityIDLength() SBE_NOEXCEPT
    {
        return 6;
    }

    const char *commodityID() const
    {
        return (m_buffer + m_offset + 82);
    }

    char commodityID(const std::uint64_t index) const
    {
        if (index >= 6)
        {
            throw std::runtime_error("index out of range for commodityID [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 82 + (index * 1))));
    }

    void commodityID(const std::uint64_t index, const char value)
    {
        if (index >= 6)
        {
            throw std::runtime_error("index out of range for commodityID [E105]");
        }

        *((char *)(m_buffer + m_offset + 82 + (index * 1))) = (value);
    }

    std::uint64_t getCommodityID(char *dst, const std::uint64_t length) const
    {
        if (length > 6)
        {
             throw std::runtime_error("length too large for getCommodityID [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 82, sizeof(char) * length);
        return length;
    }

    CommodityDefinition &putCommodityID(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 82, src, sizeof(char) * 6);
        return *this;
    }

    std::string getCommodityIDAsString() const
    {
        std::string result(m_buffer + m_offset + 82, 6);
        return result;
    }

    CommodityDefinition &putCommodityID(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 82, str.c_str(), 6);
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
         return 88;
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
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 88)));
    }

    CommodityDefinition &filler1(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 88)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }
};
}
}
#endif
