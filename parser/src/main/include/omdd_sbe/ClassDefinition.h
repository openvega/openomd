/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDD_SBE_CLASSDEFINITION_H_
#define _OMDD_SBE_CLASSDEFINITION_H_

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

class ClassDefinition
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

    inline void reset(const ClassDefinition& codec)
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

    ClassDefinition() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    ClassDefinition(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    ClassDefinition(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    ClassDefinition(const ClassDefinition& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    ClassDefinition(ClassDefinition&& codec)
    {
        reset(codec);
    }

    ClassDefinition& operator=(ClassDefinition&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    ClassDefinition& operator=(const ClassDefinition& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)114;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)302;
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

    ClassDefinition &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    ClassDefinition &wrapForDecode(
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

    static SBE_CONSTEXPR std::uint16_t countryId() SBE_NOEXCEPT
    {
        return 101;
    }

    static SBE_CONSTEXPR std::uint64_t countrySinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool countryInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= countrySinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t countryEncodingOffset() SBE_NOEXCEPT
    {
         return 0;
    }


    static const char *countryMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t countryNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t countryMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t countryMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t countryEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t country() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 0)));
    }

    ClassDefinition &country(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 0)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t marketId() SBE_NOEXCEPT
    {
        return 102;
    }

    static SBE_CONSTEXPR std::uint64_t marketSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool marketInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= marketSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t marketEncodingOffset() SBE_NOEXCEPT
    {
         return 1;
    }


    static const char *marketMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t marketNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t marketMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t marketMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t marketEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t market() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 1)));
    }

    ClassDefinition &market(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 1)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t intsrumentGroupId() SBE_NOEXCEPT
    {
        return 103;
    }

    static SBE_CONSTEXPR std::uint64_t intsrumentGroupSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool intsrumentGroupInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= intsrumentGroupSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t intsrumentGroupEncodingOffset() SBE_NOEXCEPT
    {
         return 2;
    }


    static const char *intsrumentGroupMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t intsrumentGroupNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t intsrumentGroupMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t intsrumentGroupMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t intsrumentGroupEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t intsrumentGroup() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 2)));
    }

    ClassDefinition &intsrumentGroup(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 2)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t modifierId() SBE_NOEXCEPT
    {
        return 104;
    }

    static SBE_CONSTEXPR std::uint64_t modifierSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool modifierInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= modifierSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t modifierEncodingOffset() SBE_NOEXCEPT
    {
         return 3;
    }


    static const char *modifierMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t modifierNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t modifierMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t modifierMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t modifierEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t modifier() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 3)));
    }

    ClassDefinition &modifier(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 3)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t commodityCodeId() SBE_NOEXCEPT
    {
        return 105;
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
         return 4;
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
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 4)));
    }

    ClassDefinition &commodityCode(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 4)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
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
         return 6;
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
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 6)));
    }

    ClassDefinition &filler1(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 6)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t priceQuotationFactorId() SBE_NOEXCEPT
    {
        return 106;
    }

    static SBE_CONSTEXPR std::uint64_t priceQuotationFactorSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool priceQuotationFactorInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= priceQuotationFactorSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t priceQuotationFactorEncodingOffset() SBE_NOEXCEPT
    {
         return 8;
    }


    static const char *priceQuotationFactorMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t priceQuotationFactorNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t priceQuotationFactorMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t priceQuotationFactorMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t priceQuotationFactorEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t priceQuotationFactor() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 8)));
    }

    ClassDefinition &priceQuotationFactor(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 8)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t contractSizeId() SBE_NOEXCEPT
    {
        return 107;
    }

    static SBE_CONSTEXPR std::uint64_t contractSizeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool contractSizeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= contractSizeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t contractSizeEncodingOffset() SBE_NOEXCEPT
    {
         return 12;
    }


    static const char *contractSizeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint32_t contractSizeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t contractSizeMinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t contractSizeMaxValue() SBE_NOEXCEPT
    {
        return 4294967294;
    }

    static SBE_CONSTEXPR std::size_t contractSizeEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t contractSize() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 12)));
    }

    ClassDefinition &contractSize(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 12)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t decimalInStrikePriceId() SBE_NOEXCEPT
    {
        return 108;
    }

    static SBE_CONSTEXPR std::uint64_t decimalInStrikePriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool decimalInStrikePriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= decimalInStrikePriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t decimalInStrikePriceEncodingOffset() SBE_NOEXCEPT
    {
         return 16;
    }


    static const char *decimalInStrikePriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t decimalInStrikePriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t decimalInStrikePriceMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t decimalInStrikePriceMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t decimalInStrikePriceEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t decimalInStrikePrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 16)));
    }

    ClassDefinition &decimalInStrikePrice(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 16)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t decimalInContractSizeId() SBE_NOEXCEPT
    {
        return 109;
    }

    static SBE_CONSTEXPR std::uint64_t decimalInContractSizeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool decimalInContractSizeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= decimalInContractSizeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t decimalInContractSizeEncodingOffset() SBE_NOEXCEPT
    {
         return 18;
    }


    static const char *decimalInContractSizeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t decimalInContractSizeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t decimalInContractSizeMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t decimalInContractSizeMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t decimalInContractSizeEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t decimalInContractSize() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 18)));
    }

    ClassDefinition &decimalInContractSize(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 18)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t decimalInPremiumId() SBE_NOEXCEPT
    {
        return 110;
    }

    static SBE_CONSTEXPR std::uint64_t decimalInPremiumSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool decimalInPremiumInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= decimalInPremiumSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t decimalInPremiumEncodingOffset() SBE_NOEXCEPT
    {
         return 20;
    }


    static const char *decimalInPremiumMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t decimalInPremiumNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t decimalInPremiumMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t decimalInPremiumMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t decimalInPremiumEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t decimalInPremium() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 20)));
    }

    ClassDefinition &decimalInPremium(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 20)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t rankingTypeId() SBE_NOEXCEPT
    {
        return 111;
    }

    static SBE_CONSTEXPR std::uint64_t rankingTypeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool rankingTypeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= rankingTypeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t rankingTypeEncodingOffset() SBE_NOEXCEPT
    {
         return 22;
    }


    static const char *rankingTypeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t rankingTypeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t rankingTypeMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t rankingTypeMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t rankingTypeEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t rankingType() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 22)));
    }

    ClassDefinition &rankingType(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 22)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t tradableId() SBE_NOEXCEPT
    {
        return 112;
    }

    static SBE_CONSTEXPR std::uint64_t tradableSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool tradableInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= tradableSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t tradableEncodingOffset() SBE_NOEXCEPT
    {
         return 24;
    }


    static const char *tradableMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t tradableNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t tradableMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t tradableMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t tradableEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t tradable() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 24)));
    }

    ClassDefinition &tradable(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 24)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t premiumUnit4PriceId() SBE_NOEXCEPT
    {
        return 113;
    }

    static SBE_CONSTEXPR std::uint64_t premiumUnit4PriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool premiumUnit4PriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= premiumUnit4PriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t premiumUnit4PriceEncodingOffset() SBE_NOEXCEPT
    {
         return 25;
    }


    static const char *premiumUnit4PriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t premiumUnit4PriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t premiumUnit4PriceMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t premiumUnit4PriceMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t premiumUnit4PriceEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t premiumUnit4Price() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 25)));
    }

    ClassDefinition &premiumUnit4Price(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 25)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t baseCurrencyId() SBE_NOEXCEPT
    {
        return 114;
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
         return 26;
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
        return (m_buffer + m_offset + 26);
    }

    char baseCurrency(const std::uint64_t index) const
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for baseCurrency [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 26 + (index * 1))));
    }

    void baseCurrency(const std::uint64_t index, const char value)
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for baseCurrency [E105]");
        }

        *((char *)(m_buffer + m_offset + 26 + (index * 1))) = (value);
    }

    std::uint64_t getBaseCurrency(char *dst, const std::uint64_t length) const
    {
        if (length > 3)
        {
             throw std::runtime_error("length too large for getBaseCurrency [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 26, sizeof(char) * length);
        return length;
    }

    ClassDefinition &putBaseCurrency(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 26, src, sizeof(char) * 3);
        return *this;
    }

    std::string getBaseCurrencyAsString() const
    {
        std::string result(m_buffer + m_offset + 26, 3);
        return result;
    }

    ClassDefinition &putBaseCurrency(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 26, str.c_str(), 3);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t instrumentClassIDId() SBE_NOEXCEPT
    {
        return 115;
    }

    static SBE_CONSTEXPR std::uint64_t instrumentClassIDSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool instrumentClassIDInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= instrumentClassIDSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t instrumentClassIDEncodingOffset() SBE_NOEXCEPT
    {
         return 29;
    }


    static const char *instrumentClassIDMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char instrumentClassIDNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char instrumentClassIDMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char instrumentClassIDMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t instrumentClassIDEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t instrumentClassIDLength() SBE_NOEXCEPT
    {
        return 14;
    }

    const char *instrumentClassID() const
    {
        return (m_buffer + m_offset + 29);
    }

    char instrumentClassID(const std::uint64_t index) const
    {
        if (index >= 14)
        {
            throw std::runtime_error("index out of range for instrumentClassID [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 29 + (index * 1))));
    }

    void instrumentClassID(const std::uint64_t index, const char value)
    {
        if (index >= 14)
        {
            throw std::runtime_error("index out of range for instrumentClassID [E105]");
        }

        *((char *)(m_buffer + m_offset + 29 + (index * 1))) = (value);
    }

    std::uint64_t getInstrumentClassID(char *dst, const std::uint64_t length) const
    {
        if (length > 14)
        {
             throw std::runtime_error("length too large for getInstrumentClassID [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 29, sizeof(char) * length);
        return length;
    }

    ClassDefinition &putInstrumentClassID(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 29, src, sizeof(char) * 14);
        return *this;
    }

    std::string getInstrumentClassIDAsString() const
    {
        std::string result(m_buffer + m_offset + 29, 14);
        return result;
    }

    ClassDefinition &putInstrumentClassID(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 29, str.c_str(), 14);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t instrumentClassNameId() SBE_NOEXCEPT
    {
        return 116;
    }

    static SBE_CONSTEXPR std::uint64_t instrumentClassNameSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool instrumentClassNameInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= instrumentClassNameSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t instrumentClassNameEncodingOffset() SBE_NOEXCEPT
    {
         return 43;
    }


    static const char *instrumentClassNameMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char instrumentClassNameNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char instrumentClassNameMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char instrumentClassNameMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t instrumentClassNameEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t instrumentClassNameLength() SBE_NOEXCEPT
    {
        return 32;
    }

    const char *instrumentClassName() const
    {
        return (m_buffer + m_offset + 43);
    }

    char instrumentClassName(const std::uint64_t index) const
    {
        if (index >= 32)
        {
            throw std::runtime_error("index out of range for instrumentClassName [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 43 + (index * 1))));
    }

    void instrumentClassName(const std::uint64_t index, const char value)
    {
        if (index >= 32)
        {
            throw std::runtime_error("index out of range for instrumentClassName [E105]");
        }

        *((char *)(m_buffer + m_offset + 43 + (index * 1))) = (value);
    }

    std::uint64_t getInstrumentClassName(char *dst, const std::uint64_t length) const
    {
        if (length > 32)
        {
             throw std::runtime_error("length too large for getInstrumentClassName [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 43, sizeof(char) * length);
        return length;
    }

    ClassDefinition &putInstrumentClassName(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 43, src, sizeof(char) * 32);
        return *this;
    }

    std::string getInstrumentClassNameAsString() const
    {
        std::string result(m_buffer + m_offset + 43, 32);
        return result;
    }

    ClassDefinition &putInstrumentClassName(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 43, str.c_str(), 32);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t isFractionsId() SBE_NOEXCEPT
    {
        return 117;
    }

    static SBE_CONSTEXPR std::uint64_t isFractionsSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool isFractionsInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= isFractionsSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t isFractionsEncodingOffset() SBE_NOEXCEPT
    {
         return 75;
    }


    static const char *isFractionsMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char isFractionsNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char isFractionsMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char isFractionsMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t isFractionsEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char isFractions() const
    {
        return (*((char *)(m_buffer + m_offset + 75)));
    }

    ClassDefinition &isFractions(const char value)
    {
        *((char *)(m_buffer + m_offset + 75)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t settlementCurrencyIDId() SBE_NOEXCEPT
    {
        return 118;
    }

    static SBE_CONSTEXPR std::uint64_t settlementCurrencyIDSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool settlementCurrencyIDInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= settlementCurrencyIDSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t settlementCurrencyIDEncodingOffset() SBE_NOEXCEPT
    {
         return 76;
    }


    static const char *settlementCurrencyIDMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char settlementCurrencyIDNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char settlementCurrencyIDMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char settlementCurrencyIDMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t settlementCurrencyIDEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t settlementCurrencyIDLength() SBE_NOEXCEPT
    {
        return 32;
    }

    const char *settlementCurrencyID() const
    {
        return (m_buffer + m_offset + 76);
    }

    char settlementCurrencyID(const std::uint64_t index) const
    {
        if (index >= 32)
        {
            throw std::runtime_error("index out of range for settlementCurrencyID [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 76 + (index * 1))));
    }

    void settlementCurrencyID(const std::uint64_t index, const char value)
    {
        if (index >= 32)
        {
            throw std::runtime_error("index out of range for settlementCurrencyID [E105]");
        }

        *((char *)(m_buffer + m_offset + 76 + (index * 1))) = (value);
    }

    std::uint64_t getSettlementCurrencyID(char *dst, const std::uint64_t length) const
    {
        if (length > 32)
        {
             throw std::runtime_error("length too large for getSettlementCurrencyID [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 76, sizeof(char) * length);
        return length;
    }

    ClassDefinition &putSettlementCurrencyID(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 76, src, sizeof(char) * 32);
        return *this;
    }

    std::string getSettlementCurrencyIDAsString() const
    {
        std::string result(m_buffer + m_offset + 76, 32);
        return result;
    }

    ClassDefinition &putSettlementCurrencyID(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 76, str.c_str(), 32);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t effectiveTomorrowId() SBE_NOEXCEPT
    {
        return 119;
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
         return 108;
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
        return (*((std::uint8_t *)(m_buffer + m_offset + 108)));
    }

    ClassDefinition &effectiveTomorrow(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 108)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t tickStepSizeId() SBE_NOEXCEPT
    {
        return 120;
    }

    static SBE_CONSTEXPR std::uint64_t tickStepSizeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool tickStepSizeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= tickStepSizeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t tickStepSizeEncodingOffset() SBE_NOEXCEPT
    {
         return 109;
    }


    static const char *tickStepSizeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t tickStepSizeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t tickStepSizeMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t tickStepSizeMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t tickStepSizeEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t tickStepSize() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 109)));
    }

    ClassDefinition &tickStepSize(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 109)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
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
         return 113;
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
        return (*((std::uint8_t *)(m_buffer + m_offset + 113)));
    }

    ClassDefinition &filler2(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 113)) = (value);
        return *this;
    }
};
}
}
#endif
