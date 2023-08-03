/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDCC_SBE_SECURITYDEFINITION_H_
#define _OMDCC_SBE_SECURITYDEFINITION_H_

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

class SecurityDefinition
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

    inline void reset(const SecurityDefinition& codec)
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

    SecurityDefinition() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    SecurityDefinition(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    SecurityDefinition(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    SecurityDefinition(const SecurityDefinition& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    SecurityDefinition(SecurityDefinition&& codec)
    {
        reset(codec);
    }

    SecurityDefinition& operator=(SecurityDefinition&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    SecurityDefinition& operator=(const SecurityDefinition& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)216;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)611;
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

    SecurityDefinition &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    SecurityDefinition &wrapForDecode(
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

    SecurityDefinition &securityCode(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t marketCodeId() SBE_NOEXCEPT
    {
        return 102;
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
         return 4;
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
        return (m_buffer + m_offset + 4);
    }

    char marketCode(const std::uint64_t index) const
    {
        if (index >= 4)
        {
            throw std::runtime_error("index out of range for marketCode [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 4 + (index * 1))));
    }

    void marketCode(const std::uint64_t index, const char value)
    {
        if (index >= 4)
        {
            throw std::runtime_error("index out of range for marketCode [E105]");
        }

        *((char *)(m_buffer + m_offset + 4 + (index * 1))) = (value);
    }

    std::uint64_t getMarketCode(char *dst, const std::uint64_t length) const
    {
        if (length > 4)
        {
             throw std::runtime_error("length too large for getMarketCode [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 4, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putMarketCode(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 4, src, sizeof(char) * 4);
        return *this;
    }

    std::string getMarketCodeAsString() const
    {
        std::string result(m_buffer + m_offset + 4, 4);
        return result;
    }

    SecurityDefinition &putMarketCode(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 4, str.c_str(), 4);
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
         return 8;
    }


    static const char *isinCodeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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
        return (m_buffer + m_offset + 8);
    }

    char isinCode(const std::uint64_t index) const
    {
        if (index >= 12)
        {
            throw std::runtime_error("index out of range for isinCode [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 8 + (index * 1))));
    }

    void isinCode(const std::uint64_t index, const char value)
    {
        if (index >= 12)
        {
            throw std::runtime_error("index out of range for isinCode [E105]");
        }

        *((char *)(m_buffer + m_offset + 8 + (index * 1))) = (value);
    }

    std::uint64_t getIsinCode(char *dst, const std::uint64_t length) const
    {
        if (length > 12)
        {
             throw std::runtime_error("length too large for getIsinCode [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 8, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putIsinCode(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 8, src, sizeof(char) * 12);
        return *this;
    }

    std::string getIsinCodeAsString() const
    {
        std::string result(m_buffer + m_offset + 8, 12);
        return result;
    }

    SecurityDefinition &putIsinCode(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 8, str.c_str(), 12);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t instrumentTypeId() SBE_NOEXCEPT
    {
        return 104;
    }

    static SBE_CONSTEXPR std::uint64_t instrumentTypeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool instrumentTypeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= instrumentTypeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t instrumentTypeEncodingOffset() SBE_NOEXCEPT
    {
         return 20;
    }


    static const char *instrumentTypeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char instrumentTypeNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char instrumentTypeMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char instrumentTypeMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t instrumentTypeEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t instrumentTypeLength() SBE_NOEXCEPT
    {
        return 4;
    }

    const char *instrumentType() const
    {
        return (m_buffer + m_offset + 20);
    }

    char instrumentType(const std::uint64_t index) const
    {
        if (index >= 4)
        {
            throw std::runtime_error("index out of range for instrumentType [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 20 + (index * 1))));
    }

    void instrumentType(const std::uint64_t index, const char value)
    {
        if (index >= 4)
        {
            throw std::runtime_error("index out of range for instrumentType [E105]");
        }

        *((char *)(m_buffer + m_offset + 20 + (index * 1))) = (value);
    }

    std::uint64_t getInstrumentType(char *dst, const std::uint64_t length) const
    {
        if (length > 4)
        {
             throw std::runtime_error("length too large for getInstrumentType [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 20, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putInstrumentType(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 20, src, sizeof(char) * 4);
        return *this;
    }

    std::string getInstrumentTypeAsString() const
    {
        std::string result(m_buffer + m_offset + 20, 4);
        return result;
    }

    SecurityDefinition &putInstrumentType(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 20, str.c_str(), 4);
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
         return 24;
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

    static SBE_CONSTEXPR std::uint16_t fillerNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t fillerMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t fillerMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t fillerEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t filler() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 24)));
    }

    SecurityDefinition &filler(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 24)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t securityShortNameId() SBE_NOEXCEPT
    {
        return 105;
    }

    static SBE_CONSTEXPR std::uint64_t securityShortNameSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool securityShortNameInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= securityShortNameSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t securityShortNameEncodingOffset() SBE_NOEXCEPT
    {
         return 26;
    }


    static const char *securityShortNameMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char securityShortNameNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char securityShortNameMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char securityShortNameMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t securityShortNameEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t securityShortNameLength() SBE_NOEXCEPT
    {
        return 40;
    }

    const char *securityShortName() const
    {
        return (m_buffer + m_offset + 26);
    }

    char securityShortName(const std::uint64_t index) const
    {
        if (index >= 40)
        {
            throw std::runtime_error("index out of range for securityShortName [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 26 + (index * 1))));
    }

    void securityShortName(const std::uint64_t index, const char value)
    {
        if (index >= 40)
        {
            throw std::runtime_error("index out of range for securityShortName [E105]");
        }

        *((char *)(m_buffer + m_offset + 26 + (index * 1))) = (value);
    }

    std::uint64_t getSecurityShortName(char *dst, const std::uint64_t length) const
    {
        if (length > 40)
        {
             throw std::runtime_error("length too large for getSecurityShortName [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 26, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putSecurityShortName(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 26, src, sizeof(char) * 40);
        return *this;
    }

    std::string getSecurityShortNameAsString() const
    {
        std::string result(m_buffer + m_offset + 26, 40);
        return result;
    }

    SecurityDefinition &putSecurityShortName(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 26, str.c_str(), 40);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t currencyCodeId() SBE_NOEXCEPT
    {
        return 106;
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
         return 66;
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
        return (m_buffer + m_offset + 66);
    }

    char currencyCode(const std::uint64_t index) const
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for currencyCode [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 66 + (index * 1))));
    }

    void currencyCode(const std::uint64_t index, const char value)
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for currencyCode [E105]");
        }

        *((char *)(m_buffer + m_offset + 66 + (index * 1))) = (value);
    }

    std::uint64_t getCurrencyCode(char *dst, const std::uint64_t length) const
    {
        if (length > 3)
        {
             throw std::runtime_error("length too large for getCurrencyCode [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 66, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putCurrencyCode(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 66, src, sizeof(char) * 3);
        return *this;
    }

    std::string getCurrencyCodeAsString() const
    {
        std::string result(m_buffer + m_offset + 66, 3);
        return result;
    }

    SecurityDefinition &putCurrencyCode(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 66, str.c_str(), 3);
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
         return 69;
    }


    static const char *filler2MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint64_t filler2Length() SBE_NOEXCEPT
    {
        return 60;
    }

    const char *filler2() const
    {
        return (m_buffer + m_offset + 69);
    }

    char filler2(const std::uint64_t index) const
    {
        if (index >= 60)
        {
            throw std::runtime_error("index out of range for filler2 [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 69 + (index * 1))));
    }

    void filler2(const std::uint64_t index, const char value)
    {
        if (index >= 60)
        {
            throw std::runtime_error("index out of range for filler2 [E105]");
        }

        *((char *)(m_buffer + m_offset + 69 + (index * 1))) = (value);
    }

    std::uint64_t getFiller2(char *dst, const std::uint64_t length) const
    {
        if (length > 60)
        {
             throw std::runtime_error("length too large for getFiller2 [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 69, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putFiller2(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 69, src, sizeof(char) * 60);
        return *this;
    }

    std::string getFiller2AsString() const
    {
        std::string result(m_buffer + m_offset + 69, 60);
        return result;
    }

    SecurityDefinition &putFiller2(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 69, str.c_str(), 60);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t securityNameGBId() SBE_NOEXCEPT
    {
        return 107;
    }

    static SBE_CONSTEXPR std::uint64_t securityNameGBSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool securityNameGBInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= securityNameGBSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t securityNameGBEncodingOffset() SBE_NOEXCEPT
    {
         return 129;
    }


    static const char *securityNameGBMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char securityNameGBNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char securityNameGBMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char securityNameGBMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t securityNameGBEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t securityNameGBLength() SBE_NOEXCEPT
    {
        return 60;
    }

    const char *securityNameGB() const
    {
        return (m_buffer + m_offset + 129);
    }

    char securityNameGB(const std::uint64_t index) const
    {
        if (index >= 60)
        {
            throw std::runtime_error("index out of range for securityNameGB [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 129 + (index * 1))));
    }

    void securityNameGB(const std::uint64_t index, const char value)
    {
        if (index >= 60)
        {
            throw std::runtime_error("index out of range for securityNameGB [E105]");
        }

        *((char *)(m_buffer + m_offset + 129 + (index * 1))) = (value);
    }

    std::uint64_t getSecurityNameGB(char *dst, const std::uint64_t length) const
    {
        if (length > 60)
        {
             throw std::runtime_error("length too large for getSecurityNameGB [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 129, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putSecurityNameGB(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 129, src, sizeof(char) * 60);
        return *this;
    }

    std::string getSecurityNameGBAsString() const
    {
        std::string result(m_buffer + m_offset + 129, 60);
        return result;
    }

    SecurityDefinition &putSecurityNameGB(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 129, str.c_str(), 60);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t lotSizeId() SBE_NOEXCEPT
    {
        return 108;
    }

    static SBE_CONSTEXPR std::uint64_t lotSizeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool lotSizeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= lotSizeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t lotSizeEncodingOffset() SBE_NOEXCEPT
    {
         return 189;
    }


    static const char *lotSizeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint32_t lotSizeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t lotSizeMinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t lotSizeMaxValue() SBE_NOEXCEPT
    {
        return 4294967294;
    }

    static SBE_CONSTEXPR std::size_t lotSizeEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t lotSize() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 189)));
    }

    SecurityDefinition &lotSize(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 189)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t previousClosingPriceId() SBE_NOEXCEPT
    {
        return 109;
    }

    static SBE_CONSTEXPR std::uint64_t previousClosingPriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool previousClosingPriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= previousClosingPriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t previousClosingPriceEncodingOffset() SBE_NOEXCEPT
    {
         return 193;
    }


    static const char *previousClosingPriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t previousClosingPriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t previousClosingPriceMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t previousClosingPriceMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t previousClosingPriceEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t previousClosingPrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 193)));
    }

    SecurityDefinition &previousClosingPrice(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 193)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
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
         return 197;
    }


    static const char *filler3MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::EPOCH: return "unix";
            case MetaAttribute::TIME_UNIT: return "nanosecond";
            case MetaAttribute::SEMANTIC_TYPE: return "char";
            case MetaAttribute::PRESENCE: return "required";
        }

        return "";
    }

    static SBE_CONSTEXPR char filler3NullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char filler3MinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char filler3MaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t filler3EncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char filler3() const
    {
        return (*((char *)(m_buffer + m_offset + 197)));
    }

    SecurityDefinition &filler3(const char value)
    {
        *((char *)(m_buffer + m_offset + 197)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t shortSellFlagId() SBE_NOEXCEPT
    {
        return 110;
    }

    static SBE_CONSTEXPR std::uint64_t shortSellFlagSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool shortSellFlagInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= shortSellFlagSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t shortSellFlagEncodingOffset() SBE_NOEXCEPT
    {
         return 198;
    }


    static const char *shortSellFlagMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::EPOCH: return "unix";
            case MetaAttribute::TIME_UNIT: return "nanosecond";
            case MetaAttribute::SEMANTIC_TYPE: return "char";
            case MetaAttribute::PRESENCE: return "required";
        }

        return "";
    }

    static SBE_CONSTEXPR char shortSellFlagNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char shortSellFlagMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char shortSellFlagMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t shortSellFlagEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char shortSellFlag() const
    {
        return (*((char *)(m_buffer + m_offset + 198)));
    }

    SecurityDefinition &shortSellFlag(const char value)
    {
        *((char *)(m_buffer + m_offset + 198)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t filler4Id() SBE_NOEXCEPT
    {
        return 204;
    }

    static SBE_CONSTEXPR std::uint64_t filler4SinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool filler4InActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= filler4SinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t filler4EncodingOffset() SBE_NOEXCEPT
    {
         return 199;
    }


    static const char *filler4MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char filler4NullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char filler4MinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char filler4MaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t filler4EncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t filler4Length() SBE_NOEXCEPT
    {
        return 6;
    }

    const char *filler4() const
    {
        return (m_buffer + m_offset + 199);
    }

    char filler4(const std::uint64_t index) const
    {
        if (index >= 6)
        {
            throw std::runtime_error("index out of range for filler4 [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 199 + (index * 1))));
    }

    void filler4(const std::uint64_t index, const char value)
    {
        if (index >= 6)
        {
            throw std::runtime_error("index out of range for filler4 [E105]");
        }

        *((char *)(m_buffer + m_offset + 199 + (index * 1))) = (value);
    }

    std::uint64_t getFiller4(char *dst, const std::uint64_t length) const
    {
        if (length > 6)
        {
             throw std::runtime_error("length too large for getFiller4 [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 199, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putFiller4(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 199, src, sizeof(char) * 6);
        return *this;
    }

    std::string getFiller4AsString() const
    {
        std::string result(m_buffer + m_offset + 199, 6);
        return result;
    }

    SecurityDefinition &putFiller4(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 199, str.c_str(), 6);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t listingDateId() SBE_NOEXCEPT
    {
        return 111;
    }

    static SBE_CONSTEXPR std::uint64_t listingDateSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool listingDateInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= listingDateSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t listingDateEncodingOffset() SBE_NOEXCEPT
    {
         return 205;
    }


    static const char *listingDateMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint32_t listingDateNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t listingDateMinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t listingDateMaxValue() SBE_NOEXCEPT
    {
        return 4294967294;
    }

    static SBE_CONSTEXPR std::size_t listingDateEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t listingDate() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 205)));
    }

    SecurityDefinition &listingDate(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 205)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t filler5Id() SBE_NOEXCEPT
    {
        return 205;
    }

    static SBE_CONSTEXPR std::uint64_t filler5SinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool filler5InActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= filler5SinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t filler5EncodingOffset() SBE_NOEXCEPT
    {
         return 209;
    }


    static const char *filler5MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char filler5NullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char filler5MinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char filler5MaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t filler5EncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t filler5Length() SBE_NOEXCEPT
    {
        return 7;
    }

    const char *filler5() const
    {
        return (m_buffer + m_offset + 209);
    }

    char filler5(const std::uint64_t index) const
    {
        if (index >= 7)
        {
            throw std::runtime_error("index out of range for filler5 [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 209 + (index * 1))));
    }

    void filler5(const std::uint64_t index, const char value)
    {
        if (index >= 7)
        {
            throw std::runtime_error("index out of range for filler5 [E105]");
        }

        *((char *)(m_buffer + m_offset + 209 + (index * 1))) = (value);
    }

    std::uint64_t getFiller5(char *dst, const std::uint64_t length) const
    {
        if (length > 7)
        {
             throw std::runtime_error("length too large for getFiller5 [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 209, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putFiller5(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 209, src, sizeof(char) * 7);
        return *this;
    }

    std::string getFiller5AsString() const
    {
        std::string result(m_buffer + m_offset + 209, 7);
        return result;
    }

    SecurityDefinition &putFiller5(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 209, str.c_str(), 7);
        return *this;
    }

};
}
}
#endif
