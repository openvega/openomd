/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDC_SBE_VCMTRIGGER_H_
#define _OMDC_SBE_VCMTRIGGER_H_

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
#include "GroupSize16Reverse.h"
#include "GroupSize8.h"
#include "BrokerQueueItem.h"
#include "GroupSize16.h"

using namespace sbe;

namespace omdc {
namespace sbe {

class VCMTrigger
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

    inline void reset(const VCMTrigger& codec)
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

    VCMTrigger() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    VCMTrigger(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    VCMTrigger(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    VCMTrigger(const VCMTrigger& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    VCMTrigger(VCMTrigger&& codec)
    {
        reset(codec);
    }

    VCMTrigger& operator=(VCMTrigger&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    VCMTrigger& operator=(const VCMTrigger& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)32;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)23;
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

    VCMTrigger &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    VCMTrigger &wrapForDecode(
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

    VCMTrigger &securityCode(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t coolingOffStartTimeId() SBE_NOEXCEPT
    {
        return 102;
    }

    static SBE_CONSTEXPR std::uint64_t coolingOffStartTimeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool coolingOffStartTimeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= coolingOffStartTimeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t coolingOffStartTimeEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }


    static const char *coolingOffStartTimeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint64_t coolingOffStartTimeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT64;
    }

    static SBE_CONSTEXPR std::uint64_t coolingOffStartTimeMinValue() SBE_NOEXCEPT
    {
        return 0x0L;
    }

    static SBE_CONSTEXPR std::uint64_t coolingOffStartTimeMaxValue() SBE_NOEXCEPT
    {
        return 0xfffffffffffffffeL;
    }

    static SBE_CONSTEXPR std::size_t coolingOffStartTimeEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    std::uint64_t coolingOffStartTime() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::uint64_t *)(m_buffer + m_offset + 4)));
    }

    VCMTrigger &coolingOffStartTime(const std::uint64_t value)
    {
        *((std::uint64_t *)(m_buffer + m_offset + 4)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t coolingOffEndTimeId() SBE_NOEXCEPT
    {
        return 103;
    }

    static SBE_CONSTEXPR std::uint64_t coolingOffEndTimeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool coolingOffEndTimeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= coolingOffEndTimeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t coolingOffEndTimeEncodingOffset() SBE_NOEXCEPT
    {
         return 12;
    }


    static const char *coolingOffEndTimeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint64_t coolingOffEndTimeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT64;
    }

    static SBE_CONSTEXPR std::uint64_t coolingOffEndTimeMinValue() SBE_NOEXCEPT
    {
        return 0x0L;
    }

    static SBE_CONSTEXPR std::uint64_t coolingOffEndTimeMaxValue() SBE_NOEXCEPT
    {
        return 0xfffffffffffffffeL;
    }

    static SBE_CONSTEXPR std::size_t coolingOffEndTimeEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    std::uint64_t coolingOffEndTime() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::uint64_t *)(m_buffer + m_offset + 12)));
    }

    VCMTrigger &coolingOffEndTime(const std::uint64_t value)
    {
        *((std::uint64_t *)(m_buffer + m_offset + 12)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t vcmReferencePriceId() SBE_NOEXCEPT
    {
        return 104;
    }

    static SBE_CONSTEXPR std::uint64_t vcmReferencePriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool vcmReferencePriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= vcmReferencePriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t vcmReferencePriceEncodingOffset() SBE_NOEXCEPT
    {
         return 20;
    }


    static const char *vcmReferencePriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t vcmReferencePriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t vcmReferencePriceMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t vcmReferencePriceMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t vcmReferencePriceEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t vcmReferencePrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 20)));
    }

    VCMTrigger &vcmReferencePrice(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 20)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t vcmLowerPriceId() SBE_NOEXCEPT
    {
        return 105;
    }

    static SBE_CONSTEXPR std::uint64_t vcmLowerPriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool vcmLowerPriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= vcmLowerPriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t vcmLowerPriceEncodingOffset() SBE_NOEXCEPT
    {
         return 24;
    }


    static const char *vcmLowerPriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t vcmLowerPriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t vcmLowerPriceMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t vcmLowerPriceMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t vcmLowerPriceEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t vcmLowerPrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 24)));
    }

    VCMTrigger &vcmLowerPrice(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 24)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t vcmUpperPriceId() SBE_NOEXCEPT
    {
        return 106;
    }

    static SBE_CONSTEXPR std::uint64_t vcmUpperPriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool vcmUpperPriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= vcmUpperPriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t vcmUpperPriceEncodingOffset() SBE_NOEXCEPT
    {
         return 28;
    }


    static const char *vcmUpperPriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t vcmUpperPriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t vcmUpperPriceMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t vcmUpperPriceMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t vcmUpperPriceEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t vcmUpperPrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 28)));
    }

    VCMTrigger &vcmUpperPrice(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 28)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }
};
}
}
#endif
