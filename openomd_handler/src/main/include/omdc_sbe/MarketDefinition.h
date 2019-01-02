/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDC_SBE_MARKETDEFINITION_H_
#define _OMDC_SBE_MARKETDEFINITION_H_

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

class MarketDefinition
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

    inline void reset(const MarketDefinition& codec)
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

    MarketDefinition() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    MarketDefinition(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    MarketDefinition(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    MarketDefinition(const MarketDefinition& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    MarketDefinition(MarketDefinition&& codec)
    {
        reset(codec);
    }

    MarketDefinition& operator=(MarketDefinition&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    MarketDefinition& operator=(const MarketDefinition& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)36;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)10;
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

    MarketDefinition &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    MarketDefinition &wrapForDecode(
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

    static SBE_CONSTEXPR std::uint16_t marketCodeId() SBE_NOEXCEPT
    {
        return 101;
    }

    static SBE_CONSTEXPR std::uint64_t marketCodeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool marketCodeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= marketCodeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t marketCodeEncodingOffset() SBE_NOEXCEPT
    {
         return 0;
    }


    static const char *marketCodeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::EPOCH: return "unix";
            case MetaAttribute::TIME_UNIT: return "nanosecond";
            case MetaAttribute::SEMANTIC_TYPE: return "String";
            case MetaAttribute::PRESENCE: return "required";
        }

        return "";
    }

    static SBE_CONSTEXPR char marketCodeNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char marketCodeMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char marketCodeMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t marketCodeEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t marketCodeLength() SBE_NOEXCEPT
    {
        return 4;
    }

    const char *marketCode() const
    {
        return (m_buffer + m_offset + 0);
    }

    char marketCode(const std::uint64_t index) const
    {
        if (index >= 4)
        {
            throw std::runtime_error("index out of range for marketCode [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 0 + (index * 1))));
    }

    void marketCode(const std::uint64_t index, const char value)
    {
        if (index >= 4)
        {
            throw std::runtime_error("index out of range for marketCode [E105]");
        }

        *((char *)(m_buffer + m_offset + 0 + (index * 1))) = (value);
    }

    std::uint64_t getMarketCode(char *dst, const std::uint64_t length) const
    {
        if (length > 4)
        {
             throw std::runtime_error("length too large for getMarketCode [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 0, sizeof(char) * length);
        return length;
    }

    MarketDefinition &putMarketCode(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 0, src, sizeof(char) * 4);
        return *this;
    }

    std::string getMarketCodeAsString() const
    {
        std::string result(m_buffer + m_offset + 0, 4);
        return result;
    }

    MarketDefinition &putMarketCode(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 0, str.c_str(), 4);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t marketNameId() SBE_NOEXCEPT
    {
        return 102;
    }

    static SBE_CONSTEXPR std::uint64_t marketNameSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool marketNameInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= marketNameSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t marketNameEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }


    static const char *marketNameMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::EPOCH: return "unix";
            case MetaAttribute::TIME_UNIT: return "nanosecond";
            case MetaAttribute::SEMANTIC_TYPE: return "String";
            case MetaAttribute::PRESENCE: return "required";
        }

        return "";
    }

    static SBE_CONSTEXPR char marketNameNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char marketNameMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char marketNameMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t marketNameEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t marketNameLength() SBE_NOEXCEPT
    {
        return 25;
    }

    const char *marketName() const
    {
        return (m_buffer + m_offset + 4);
    }

    char marketName(const std::uint64_t index) const
    {
        if (index >= 25)
        {
            throw std::runtime_error("index out of range for marketName [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 4 + (index * 1))));
    }

    void marketName(const std::uint64_t index, const char value)
    {
        if (index >= 25)
        {
            throw std::runtime_error("index out of range for marketName [E105]");
        }

        *((char *)(m_buffer + m_offset + 4 + (index * 1))) = (value);
    }

    std::uint64_t getMarketName(char *dst, const std::uint64_t length) const
    {
        if (length > 25)
        {
             throw std::runtime_error("length too large for getMarketName [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 4, sizeof(char) * length);
        return length;
    }

    MarketDefinition &putMarketName(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 4, src, sizeof(char) * 25);
        return *this;
    }

    std::string getMarketNameAsString() const
    {
        std::string result(m_buffer + m_offset + 4, 25);
        return result;
    }

    MarketDefinition &putMarketName(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 4, str.c_str(), 25);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t currencyCodeId() SBE_NOEXCEPT
    {
        return 103;
    }

    static SBE_CONSTEXPR std::uint64_t currencyCodeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool currencyCodeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= currencyCodeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t currencyCodeEncodingOffset() SBE_NOEXCEPT
    {
         return 29;
    }


    static const char *currencyCodeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::EPOCH: return "unix";
            case MetaAttribute::TIME_UNIT: return "nanosecond";
            case MetaAttribute::SEMANTIC_TYPE: return "String";
            case MetaAttribute::PRESENCE: return "required";
        }

        return "";
    }

    static SBE_CONSTEXPR char currencyCodeNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char currencyCodeMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char currencyCodeMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t currencyCodeEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t currencyCodeLength() SBE_NOEXCEPT
    {
        return 3;
    }

    const char *currencyCode() const
    {
        return (m_buffer + m_offset + 29);
    }

    char currencyCode(const std::uint64_t index) const
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for currencyCode [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 29 + (index * 1))));
    }

    void currencyCode(const std::uint64_t index, const char value)
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for currencyCode [E105]");
        }

        *((char *)(m_buffer + m_offset + 29 + (index * 1))) = (value);
    }

    std::uint64_t getCurrencyCode(char *dst, const std::uint64_t length) const
    {
        if (length > 3)
        {
             throw std::runtime_error("length too large for getCurrencyCode [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 29, sizeof(char) * length);
        return length;
    }

    MarketDefinition &putCurrencyCode(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 29, src, sizeof(char) * 3);
        return *this;
    }

    std::string getCurrencyCodeAsString() const
    {
        std::string result(m_buffer + m_offset + 29, 3);
        return result;
    }

    MarketDefinition &putCurrencyCode(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 29, str.c_str(), 3);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t numberOfSecuritiesId() SBE_NOEXCEPT
    {
        return 104;
    }

    static SBE_CONSTEXPR std::uint64_t numberOfSecuritiesSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool numberOfSecuritiesInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= numberOfSecuritiesSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t numberOfSecuritiesEncodingOffset() SBE_NOEXCEPT
    {
         return 32;
    }


    static const char *numberOfSecuritiesMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint32_t numberOfSecuritiesNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t numberOfSecuritiesMinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t numberOfSecuritiesMaxValue() SBE_NOEXCEPT
    {
        return 4294967294;
    }

    static SBE_CONSTEXPR std::size_t numberOfSecuritiesEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t numberOfSecurities() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 32)));
    }

    MarketDefinition &numberOfSecurities(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 32)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }
};
}
}
#endif
