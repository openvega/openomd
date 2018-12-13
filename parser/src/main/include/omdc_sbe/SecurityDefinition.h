/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDC_SBE_SECURITYDEFINITION_H_
#define _OMDC_SBE_SECURITYDEFINITION_H_

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
        return (std::uint16_t)458;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)11;
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


    static SBE_CONSTEXPR std::uint16_t productTypeId() SBE_NOEXCEPT
    {
        return 105;
    }

    static SBE_CONSTEXPR std::uint64_t productTypeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool productTypeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= productTypeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t productTypeEncodingOffset() SBE_NOEXCEPT
    {
         return 24;
    }


    static const char *productTypeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t productTypeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t productTypeMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t productTypeMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t productTypeEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t productType() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 24)));
    }

    SecurityDefinition &productType(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 24)) = (value);
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
         return 25;
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

    char filler() const
    {
        return (*((char *)(m_buffer + m_offset + 25)));
    }

    SecurityDefinition &filler(const char value)
    {
        *((char *)(m_buffer + m_offset + 25)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t spreadTableCodeId() SBE_NOEXCEPT
    {
        return 106;
    }

    static SBE_CONSTEXPR std::uint64_t spreadTableCodeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool spreadTableCodeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= spreadTableCodeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t spreadTableCodeEncodingOffset() SBE_NOEXCEPT
    {
         return 26;
    }


    static const char *spreadTableCodeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char spreadTableCodeNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char spreadTableCodeMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char spreadTableCodeMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t spreadTableCodeEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t spreadTableCodeLength() SBE_NOEXCEPT
    {
        return 2;
    }

    const char *spreadTableCode() const
    {
        return (m_buffer + m_offset + 26);
    }

    char spreadTableCode(const std::uint64_t index) const
    {
        if (index >= 2)
        {
            throw std::runtime_error("index out of range for spreadTableCode [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 26 + (index * 1))));
    }

    void spreadTableCode(const std::uint64_t index, const char value)
    {
        if (index >= 2)
        {
            throw std::runtime_error("index out of range for spreadTableCode [E105]");
        }

        *((char *)(m_buffer + m_offset + 26 + (index * 1))) = (value);
    }

    std::uint64_t getSpreadTableCode(char *dst, const std::uint64_t length) const
    {
        if (length > 2)
        {
             throw std::runtime_error("length too large for getSpreadTableCode [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 26, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putSpreadTableCode(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 26, src, sizeof(char) * 2);
        return *this;
    }

    std::string getSpreadTableCodeAsString() const
    {
        std::string result(m_buffer + m_offset + 26, 2);
        return result;
    }

    SecurityDefinition &putSpreadTableCode(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 26, str.c_str(), 2);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t securityShortNameId() SBE_NOEXCEPT
    {
        return 107;
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
         return 28;
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
        return (m_buffer + m_offset + 28);
    }

    char securityShortName(const std::uint64_t index) const
    {
        if (index >= 40)
        {
            throw std::runtime_error("index out of range for securityShortName [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 28 + (index * 1))));
    }

    void securityShortName(const std::uint64_t index, const char value)
    {
        if (index >= 40)
        {
            throw std::runtime_error("index out of range for securityShortName [E105]");
        }

        *((char *)(m_buffer + m_offset + 28 + (index * 1))) = (value);
    }

    std::uint64_t getSecurityShortName(char *dst, const std::uint64_t length) const
    {
        if (length > 40)
        {
             throw std::runtime_error("length too large for getSecurityShortName [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 28, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putSecurityShortName(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 28, src, sizeof(char) * 40);
        return *this;
    }

    std::string getSecurityShortNameAsString() const
    {
        std::string result(m_buffer + m_offset + 28, 40);
        return result;
    }

    SecurityDefinition &putSecurityShortName(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 28, str.c_str(), 40);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t currencyCodeId() SBE_NOEXCEPT
    {
        return 108;
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
         return 68;
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
        return (m_buffer + m_offset + 68);
    }

    char currencyCode(const std::uint64_t index) const
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for currencyCode [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 68 + (index * 1))));
    }

    void currencyCode(const std::uint64_t index, const char value)
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for currencyCode [E105]");
        }

        *((char *)(m_buffer + m_offset + 68 + (index * 1))) = (value);
    }

    std::uint64_t getCurrencyCode(char *dst, const std::uint64_t length) const
    {
        if (length > 3)
        {
             throw std::runtime_error("length too large for getCurrencyCode [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 68, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putCurrencyCode(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 68, src, sizeof(char) * 3);
        return *this;
    }

    std::string getCurrencyCodeAsString() const
    {
        std::string result(m_buffer + m_offset + 68, 3);
        return result;
    }

    SecurityDefinition &putCurrencyCode(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 68, str.c_str(), 3);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t securityNameGCCSId() SBE_NOEXCEPT
    {
        return 109;
    }

    static SBE_CONSTEXPR std::uint64_t securityNameGCCSSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool securityNameGCCSInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= securityNameGCCSSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t securityNameGCCSEncodingOffset() SBE_NOEXCEPT
    {
         return 71;
    }


    static const char *securityNameGCCSMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char securityNameGCCSNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char securityNameGCCSMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char securityNameGCCSMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t securityNameGCCSEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t securityNameGCCSLength() SBE_NOEXCEPT
    {
        return 60;
    }

    const char *securityNameGCCS() const
    {
        return (m_buffer + m_offset + 71);
    }

    char securityNameGCCS(const std::uint64_t index) const
    {
        if (index >= 60)
        {
            throw std::runtime_error("index out of range for securityNameGCCS [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 71 + (index * 1))));
    }

    void securityNameGCCS(const std::uint64_t index, const char value)
    {
        if (index >= 60)
        {
            throw std::runtime_error("index out of range for securityNameGCCS [E105]");
        }

        *((char *)(m_buffer + m_offset + 71 + (index * 1))) = (value);
    }

    std::uint64_t getSecurityNameGCCS(char *dst, const std::uint64_t length) const
    {
        if (length > 60)
        {
             throw std::runtime_error("length too large for getSecurityNameGCCS [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 71, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putSecurityNameGCCS(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 71, src, sizeof(char) * 60);
        return *this;
    }

    std::string getSecurityNameGCCSAsString() const
    {
        std::string result(m_buffer + m_offset + 71, 60);
        return result;
    }

    SecurityDefinition &putSecurityNameGCCS(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 71, str.c_str(), 60);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t securityNameGBId() SBE_NOEXCEPT
    {
        return 110;
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
         return 131;
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
        return (m_buffer + m_offset + 131);
    }

    char securityNameGB(const std::uint64_t index) const
    {
        if (index >= 60)
        {
            throw std::runtime_error("index out of range for securityNameGB [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 131 + (index * 1))));
    }

    void securityNameGB(const std::uint64_t index, const char value)
    {
        if (index >= 60)
        {
            throw std::runtime_error("index out of range for securityNameGB [E105]");
        }

        *((char *)(m_buffer + m_offset + 131 + (index * 1))) = (value);
    }

    std::uint64_t getSecurityNameGB(char *dst, const std::uint64_t length) const
    {
        if (length > 60)
        {
             throw std::runtime_error("length too large for getSecurityNameGB [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 131, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putSecurityNameGB(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 131, src, sizeof(char) * 60);
        return *this;
    }

    std::string getSecurityNameGBAsString() const
    {
        std::string result(m_buffer + m_offset + 131, 60);
        return result;
    }

    SecurityDefinition &putSecurityNameGB(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 131, str.c_str(), 60);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t lotSizeId() SBE_NOEXCEPT
    {
        return 111;
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
         return 191;
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
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 191)));
    }

    SecurityDefinition &lotSize(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 191)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
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
         return 195;
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

    static SBE_CONSTEXPR std::uint32_t filler2NullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t filler2MinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t filler2MaxValue() SBE_NOEXCEPT
    {
        return 4294967294;
    }

    static SBE_CONSTEXPR std::size_t filler2EncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t filler2() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 195)));
    }

    SecurityDefinition &filler2(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 195)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t previousClosingPriceId() SBE_NOEXCEPT
    {
        return 112;
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
         return 199;
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
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 199)));
    }

    SecurityDefinition &previousClosingPrice(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 199)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t vcmFlagId() SBE_NOEXCEPT
    {
        return 113;
    }

    static SBE_CONSTEXPR std::uint64_t vcmFlagSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool vcmFlagInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= vcmFlagSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t vcmFlagEncodingOffset() SBE_NOEXCEPT
    {
         return 203;
    }


    static const char *vcmFlagMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char vcmFlagNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char vcmFlagMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char vcmFlagMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t vcmFlagEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char vcmFlag() const
    {
        return (*((char *)(m_buffer + m_offset + 203)));
    }

    SecurityDefinition &vcmFlag(const char value)
    {
        *((char *)(m_buffer + m_offset + 203)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t shortSellFlagId() SBE_NOEXCEPT
    {
        return 114;
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
         return 204;
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
        return (*((char *)(m_buffer + m_offset + 204)));
    }

    SecurityDefinition &shortSellFlag(const char value)
    {
        *((char *)(m_buffer + m_offset + 204)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t casFlagId() SBE_NOEXCEPT
    {
        return 115;
    }

    static SBE_CONSTEXPR std::uint64_t casFlagSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool casFlagInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= casFlagSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t casFlagEncodingOffset() SBE_NOEXCEPT
    {
         return 205;
    }


    static const char *casFlagMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char casFlagNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char casFlagMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char casFlagMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t casFlagEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char casFlag() const
    {
        return (*((char *)(m_buffer + m_offset + 205)));
    }

    SecurityDefinition &casFlag(const char value)
    {
        *((char *)(m_buffer + m_offset + 205)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t ccassFlagId() SBE_NOEXCEPT
    {
        return 116;
    }

    static SBE_CONSTEXPR std::uint64_t ccassFlagSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool ccassFlagInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= ccassFlagSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t ccassFlagEncodingOffset() SBE_NOEXCEPT
    {
         return 206;
    }


    static const char *ccassFlagMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char ccassFlagNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char ccassFlagMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char ccassFlagMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t ccassFlagEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char ccassFlag() const
    {
        return (*((char *)(m_buffer + m_offset + 206)));
    }

    SecurityDefinition &ccassFlag(const char value)
    {
        *((char *)(m_buffer + m_offset + 206)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t dummySecurityFlagId() SBE_NOEXCEPT
    {
        return 117;
    }

    static SBE_CONSTEXPR std::uint64_t dummySecurityFlagSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool dummySecurityFlagInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= dummySecurityFlagSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t dummySecurityFlagEncodingOffset() SBE_NOEXCEPT
    {
         return 207;
    }


    static const char *dummySecurityFlagMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char dummySecurityFlagNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char dummySecurityFlagMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char dummySecurityFlagMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t dummySecurityFlagEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char dummySecurityFlag() const
    {
        return (*((char *)(m_buffer + m_offset + 207)));
    }

    SecurityDefinition &dummySecurityFlag(const char value)
    {
        *((char *)(m_buffer + m_offset + 207)) = (value);
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
         return 208;
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
        return (*((char *)(m_buffer + m_offset + 208)));
    }

    SecurityDefinition &filler3(const char value)
    {
        *((char *)(m_buffer + m_offset + 208)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t stampDutyFlagId() SBE_NOEXCEPT
    {
        return 118;
    }

    static SBE_CONSTEXPR std::uint64_t stampDutyFlagSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool stampDutyFlagInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= stampDutyFlagSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t stampDutyFlagEncodingOffset() SBE_NOEXCEPT
    {
         return 209;
    }


    static const char *stampDutyFlagMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char stampDutyFlagNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char stampDutyFlagMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char stampDutyFlagMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t stampDutyFlagEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char stampDutyFlag() const
    {
        return (*((char *)(m_buffer + m_offset + 209)));
    }

    SecurityDefinition &stampDutyFlag(const char value)
    {
        *((char *)(m_buffer + m_offset + 209)) = (value);
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
         return 210;
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

    char filler4() const
    {
        return (*((char *)(m_buffer + m_offset + 210)));
    }

    SecurityDefinition &filler4(const char value)
    {
        *((char *)(m_buffer + m_offset + 210)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t listingDateId() SBE_NOEXCEPT
    {
        return 119;
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
         return 211;
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
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 211)));
    }

    SecurityDefinition &listingDate(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 211)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t delistingDateId() SBE_NOEXCEPT
    {
        return 120;
    }

    static SBE_CONSTEXPR std::uint64_t delistingDateSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool delistingDateInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= delistingDateSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t delistingDateEncodingOffset() SBE_NOEXCEPT
    {
         return 215;
    }


    static const char *delistingDateMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint32_t delistingDateNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t delistingDateMinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t delistingDateMaxValue() SBE_NOEXCEPT
    {
        return 4294967294;
    }

    static SBE_CONSTEXPR std::size_t delistingDateEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t delistingDate() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 215)));
    }

    SecurityDefinition &delistingDate(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 215)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t freeTextId() SBE_NOEXCEPT
    {
        return 121;
    }

    static SBE_CONSTEXPR std::uint64_t freeTextSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool freeTextInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= freeTextSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t freeTextEncodingOffset() SBE_NOEXCEPT
    {
         return 219;
    }


    static const char *freeTextMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char freeTextNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char freeTextMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char freeTextMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t freeTextEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t freeTextLength() SBE_NOEXCEPT
    {
        return 38;
    }

    const char *freeText() const
    {
        return (m_buffer + m_offset + 219);
    }

    char freeText(const std::uint64_t index) const
    {
        if (index >= 38)
        {
            throw std::runtime_error("index out of range for freeText [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 219 + (index * 1))));
    }

    void freeText(const std::uint64_t index, const char value)
    {
        if (index >= 38)
        {
            throw std::runtime_error("index out of range for freeText [E105]");
        }

        *((char *)(m_buffer + m_offset + 219 + (index * 1))) = (value);
    }

    std::uint64_t getFreeText(char *dst, const std::uint64_t length) const
    {
        if (length > 38)
        {
             throw std::runtime_error("length too large for getFreeText [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 219, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putFreeText(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 219, src, sizeof(char) * 38);
        return *this;
    }

    std::string getFreeTextAsString() const
    {
        std::string result(m_buffer + m_offset + 219, 38);
        return result;
    }

    SecurityDefinition &putFreeText(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 219, str.c_str(), 38);
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
         return 257;
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
        return 82;
    }

    const char *filler5() const
    {
        return (m_buffer + m_offset + 257);
    }

    char filler5(const std::uint64_t index) const
    {
        if (index >= 82)
        {
            throw std::runtime_error("index out of range for filler5 [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 257 + (index * 1))));
    }

    void filler5(const std::uint64_t index, const char value)
    {
        if (index >= 82)
        {
            throw std::runtime_error("index out of range for filler5 [E105]");
        }

        *((char *)(m_buffer + m_offset + 257 + (index * 1))) = (value);
    }

    std::uint64_t getFiller5(char *dst, const std::uint64_t length) const
    {
        if (length > 82)
        {
             throw std::runtime_error("length too large for getFiller5 [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 257, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putFiller5(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 257, src, sizeof(char) * 82);
        return *this;
    }

    std::string getFiller5AsString() const
    {
        std::string result(m_buffer + m_offset + 257, 82);
        return result;
    }

    SecurityDefinition &putFiller5(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 257, str.c_str(), 82);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t efnFlagId() SBE_NOEXCEPT
    {
        return 122;
    }

    static SBE_CONSTEXPR std::uint64_t efnFlagSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool efnFlagInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= efnFlagSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t efnFlagEncodingOffset() SBE_NOEXCEPT
    {
         return 339;
    }


    static const char *efnFlagMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char efnFlagNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char efnFlagMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char efnFlagMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t efnFlagEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char efnFlag() const
    {
        return (*((char *)(m_buffer + m_offset + 339)));
    }

    SecurityDefinition &efnFlag(const char value)
    {
        *((char *)(m_buffer + m_offset + 339)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t accruedInterestId() SBE_NOEXCEPT
    {
        return 123;
    }

    static SBE_CONSTEXPR std::uint64_t accruedInterestSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool accruedInterestInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= accruedInterestSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t accruedInterestEncodingOffset() SBE_NOEXCEPT
    {
         return 340;
    }


    static const char *accruedInterestMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint32_t accruedInterestNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t accruedInterestMinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t accruedInterestMaxValue() SBE_NOEXCEPT
    {
        return 4294967294;
    }

    static SBE_CONSTEXPR std::size_t accruedInterestEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t accruedInterest() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 340)));
    }

    SecurityDefinition &accruedInterest(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 340)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t couponRateId() SBE_NOEXCEPT
    {
        return 124;
    }

    static SBE_CONSTEXPR std::uint64_t couponRateSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool couponRateInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= couponRateSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t couponRateEncodingOffset() SBE_NOEXCEPT
    {
         return 344;
    }


    static const char *couponRateMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint32_t couponRateNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t couponRateMinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t couponRateMaxValue() SBE_NOEXCEPT
    {
        return 4294967294;
    }

    static SBE_CONSTEXPR std::size_t couponRateEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t couponRate() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 344)));
    }

    SecurityDefinition &couponRate(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 344)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t filler6Id() SBE_NOEXCEPT
    {
        return 205;
    }

    static SBE_CONSTEXPR std::uint64_t filler6SinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool filler6InActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= filler6SinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t filler6EncodingOffset() SBE_NOEXCEPT
    {
         return 348;
    }


    static const char *filler6MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char filler6NullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char filler6MinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char filler6MaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t filler6EncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t filler6Length() SBE_NOEXCEPT
    {
        return 42;
    }

    const char *filler6() const
    {
        return (m_buffer + m_offset + 348);
    }

    char filler6(const std::uint64_t index) const
    {
        if (index >= 42)
        {
            throw std::runtime_error("index out of range for filler6 [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 348 + (index * 1))));
    }

    void filler6(const std::uint64_t index, const char value)
    {
        if (index >= 42)
        {
            throw std::runtime_error("index out of range for filler6 [E105]");
        }

        *((char *)(m_buffer + m_offset + 348 + (index * 1))) = (value);
    }

    std::uint64_t getFiller6(char *dst, const std::uint64_t length) const
    {
        if (length > 42)
        {
             throw std::runtime_error("length too large for getFiller6 [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 348, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putFiller6(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 348, src, sizeof(char) * 42);
        return *this;
    }

    std::string getFiller6AsString() const
    {
        std::string result(m_buffer + m_offset + 348, 42);
        return result;
    }

    SecurityDefinition &putFiller6(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 348, str.c_str(), 42);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t conversionRatioId() SBE_NOEXCEPT
    {
        return 125;
    }

    static SBE_CONSTEXPR std::uint64_t conversionRatioSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool conversionRatioInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= conversionRatioSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t conversionRatioEncodingOffset() SBE_NOEXCEPT
    {
         return 390;
    }


    static const char *conversionRatioMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint32_t conversionRatioNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t conversionRatioMinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t conversionRatioMaxValue() SBE_NOEXCEPT
    {
        return 4294967294;
    }

    static SBE_CONSTEXPR std::size_t conversionRatioEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t conversionRatio() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 390)));
    }

    SecurityDefinition &conversionRatio(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 390)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t strikePrice1Id() SBE_NOEXCEPT
    {
        return 126;
    }

    static SBE_CONSTEXPR std::uint64_t strikePrice1SinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool strikePrice1InActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= strikePrice1SinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t strikePrice1EncodingOffset() SBE_NOEXCEPT
    {
         return 394;
    }


    static const char *strikePrice1MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t strikePrice1NullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t strikePrice1MinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t strikePrice1MaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t strikePrice1EncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t strikePrice1() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 394)));
    }

    SecurityDefinition &strikePrice1(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 394)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t strikePrice2Id() SBE_NOEXCEPT
    {
        return 127;
    }

    static SBE_CONSTEXPR std::uint64_t strikePrice2SinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool strikePrice2InActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= strikePrice2SinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t strikePrice2EncodingOffset() SBE_NOEXCEPT
    {
         return 398;
    }


    static const char *strikePrice2MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t strikePrice2NullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t strikePrice2MinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t strikePrice2MaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t strikePrice2EncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t strikePrice2() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 398)));
    }

    SecurityDefinition &strikePrice2(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 398)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t maturityDateId() SBE_NOEXCEPT
    {
        return 128;
    }

    static SBE_CONSTEXPR std::uint64_t maturityDateSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool maturityDateInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= maturityDateSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t maturityDateEncodingOffset() SBE_NOEXCEPT
    {
         return 402;
    }


    static const char *maturityDateMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t maturityDateNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t maturityDateMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t maturityDateMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t maturityDateEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t maturityDate() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 402)));
    }

    SecurityDefinition &maturityDate(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 402)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t callPutFlagId() SBE_NOEXCEPT
    {
        return 129;
    }

    static SBE_CONSTEXPR std::uint64_t callPutFlagSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool callPutFlagInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= callPutFlagSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t callPutFlagEncodingOffset() SBE_NOEXCEPT
    {
         return 406;
    }


    static const char *callPutFlagMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char callPutFlagNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char callPutFlagMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char callPutFlagMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t callPutFlagEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char callPutFlag() const
    {
        return (*((char *)(m_buffer + m_offset + 406)));
    }

    SecurityDefinition &callPutFlag(const char value)
    {
        *((char *)(m_buffer + m_offset + 406)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t styleId() SBE_NOEXCEPT
    {
        return 130;
    }

    static SBE_CONSTEXPR std::uint64_t styleSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool styleInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= styleSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t styleEncodingOffset() SBE_NOEXCEPT
    {
         return 407;
    }


    static const char *styleMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char styleNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char styleMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char styleMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t styleEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char style() const
    {
        return (*((char *)(m_buffer + m_offset + 407)));
    }

    SecurityDefinition &style(const char value)
    {
        *((char *)(m_buffer + m_offset + 407)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t filler7Id() SBE_NOEXCEPT
    {
        return 207;
    }

    static SBE_CONSTEXPR std::uint64_t filler7SinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool filler7InActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= filler7SinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t filler7EncodingOffset() SBE_NOEXCEPT
    {
         return 408;
    }


    static const char *filler7MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t filler7NullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t filler7MinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t filler7MaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t filler7EncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t filler7() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 408)));
    }

    SecurityDefinition &filler7(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 408)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t warrantTypeId() SBE_NOEXCEPT
    {
        return 131;
    }

    static SBE_CONSTEXPR std::uint64_t warrantTypeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool warrantTypeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= warrantTypeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t warrantTypeEncodingOffset() SBE_NOEXCEPT
    {
         return 410;
    }


    static const char *warrantTypeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char warrantTypeNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char warrantTypeMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char warrantTypeMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t warrantTypeEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char warrantType() const
    {
        return (*((char *)(m_buffer + m_offset + 410)));
    }

    SecurityDefinition &warrantType(const char value)
    {
        *((char *)(m_buffer + m_offset + 410)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t callPriceId() SBE_NOEXCEPT
    {
        return 132;
    }

    static SBE_CONSTEXPR std::uint64_t callPriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool callPriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= callPriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t callPriceEncodingOffset() SBE_NOEXCEPT
    {
         return 411;
    }


    static const char *callPriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t callPriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t callPriceMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t callPriceMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t callPriceEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t callPrice() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 411)));
    }

    SecurityDefinition &callPrice(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 411)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t decimalsInCallPriceId() SBE_NOEXCEPT
    {
        return 133;
    }

    static SBE_CONSTEXPR std::uint64_t decimalsInCallPriceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool decimalsInCallPriceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= decimalsInCallPriceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t decimalsInCallPriceEncodingOffset() SBE_NOEXCEPT
    {
         return 415;
    }


    static const char *decimalsInCallPriceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t decimalsInCallPriceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t decimalsInCallPriceMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t decimalsInCallPriceMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t decimalsInCallPriceEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t decimalsInCallPrice() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 415)));
    }

    SecurityDefinition &decimalsInCallPrice(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 415)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t entitlementId() SBE_NOEXCEPT
    {
        return 134;
    }

    static SBE_CONSTEXPR std::uint64_t entitlementSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool entitlementInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= entitlementSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t entitlementEncodingOffset() SBE_NOEXCEPT
    {
         return 416;
    }


    static const char *entitlementMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int32_t entitlementNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t entitlementMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t entitlementMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t entitlementEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t entitlement() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 416)));
    }

    SecurityDefinition &entitlement(const std::int32_t value)
    {
        *((std::int32_t *)(m_buffer + m_offset + 416)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t decimalsInEntitlementId() SBE_NOEXCEPT
    {
        return 135;
    }

    static SBE_CONSTEXPR std::uint64_t decimalsInEntitlementSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool decimalsInEntitlementInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= decimalsInEntitlementSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t decimalsInEntitlementEncodingOffset() SBE_NOEXCEPT
    {
         return 420;
    }


    static const char *decimalsInEntitlementMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t decimalsInEntitlementNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t decimalsInEntitlementMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t decimalsInEntitlementMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t decimalsInEntitlementEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t decimalsInEntitlement() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 420)));
    }

    SecurityDefinition &decimalsInEntitlement(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 420)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t noWarrantsPerEntitlementId() SBE_NOEXCEPT
    {
        return 136;
    }

    static SBE_CONSTEXPR std::uint64_t noWarrantsPerEntitlementSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool noWarrantsPerEntitlementInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= noWarrantsPerEntitlementSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t noWarrantsPerEntitlementEncodingOffset() SBE_NOEXCEPT
    {
         return 421;
    }


    static const char *noWarrantsPerEntitlementMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint32_t noWarrantsPerEntitlementNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t noWarrantsPerEntitlementMinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t noWarrantsPerEntitlementMaxValue() SBE_NOEXCEPT
    {
        return 4294967294;
    }

    static SBE_CONSTEXPR std::size_t noWarrantsPerEntitlementEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t noWarrantsPerEntitlement() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 421)));
    }

    SecurityDefinition &noWarrantsPerEntitlement(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 421)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t filler8Id() SBE_NOEXCEPT
    {
        return 208;
    }

    static SBE_CONSTEXPR std::uint64_t filler8SinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool filler8InActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= filler8SinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t filler8EncodingOffset() SBE_NOEXCEPT
    {
         return 425;
    }


    static const char *filler8MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char filler8NullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char filler8MinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char filler8MaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t filler8EncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t filler8Length() SBE_NOEXCEPT
    {
        return 33;
    }

    const char *filler8() const
    {
        return (m_buffer + m_offset + 425);
    }

    char filler8(const std::uint64_t index) const
    {
        if (index >= 33)
        {
            throw std::runtime_error("index out of range for filler8 [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 425 + (index * 1))));
    }

    void filler8(const std::uint64_t index, const char value)
    {
        if (index >= 33)
        {
            throw std::runtime_error("index out of range for filler8 [E105]");
        }

        *((char *)(m_buffer + m_offset + 425 + (index * 1))) = (value);
    }

    std::uint64_t getFiller8(char *dst, const std::uint64_t length) const
    {
        if (length > 33)
        {
             throw std::runtime_error("length too large for getFiller8 [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 425, sizeof(char) * length);
        return length;
    }

    SecurityDefinition &putFiller8(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 425, src, sizeof(char) * 33);
        return *this;
    }

    std::string getFiller8AsString() const
    {
        std::string result(m_buffer + m_offset + 425, 33);
        return result;
    }

    SecurityDefinition &putFiller8(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 425, str.c_str(), 33);
        return *this;
    }


    class NoUnderlyingSecurities
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
        GroupSize16 m_dimensions;

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

        inline void wrapForEncode(char *buffer, const std::uint16_t count, std::uint64_t *pos, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
        {
    #if defined(__GNUG__) && !defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wtype-limits"
    #endif
            if (count < 0 || count > 65534)
            {
                throw std::runtime_error("count outside of allowed range [E110]");
            }
    #if defined(__GNUG__) && !defined(__clang__)
    #pragma GCC diagnostic pop
    #endif
            m_buffer = buffer;
            m_bufferLength = bufferLength;
            m_dimensions.wrap(m_buffer, *pos, actingVersion, bufferLength);
            m_dimensions.blockLength((std::uint16_t)8);
            m_dimensions.numInGroup((std::uint16_t)count);
            m_index = -1;
            m_count = count;
            m_blockLength = 8;
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
            return 8;
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

        inline NoUnderlyingSecurities &next()
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


        static SBE_CONSTEXPR std::uint16_t underlyingSecurityCodeId() SBE_NOEXCEPT
        {
            return 138;
        }

        static SBE_CONSTEXPR std::uint64_t underlyingSecurityCodeSinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool underlyingSecurityCodeInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= underlyingSecurityCodeSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t underlyingSecurityCodeEncodingOffset() SBE_NOEXCEPT
        {
             return 0;
        }


        static const char *underlyingSecurityCodeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

        static SBE_CONSTEXPR std::uint32_t underlyingSecurityCodeNullValue() SBE_NOEXCEPT
        {
            return SBE_NULLVALUE_UINT32;
        }

        static SBE_CONSTEXPR std::uint32_t underlyingSecurityCodeMinValue() SBE_NOEXCEPT
        {
            return 0;
        }

        static SBE_CONSTEXPR std::uint32_t underlyingSecurityCodeMaxValue() SBE_NOEXCEPT
        {
            return 4294967294;
        }

        static SBE_CONSTEXPR std::size_t underlyingSecurityCodeEncodingLength() SBE_NOEXCEPT
        {
            return 4;
        }

        std::uint32_t underlyingSecurityCode() const
        {
            return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::uint32_t *)(m_buffer + m_offset + 0)));
        }

        NoUnderlyingSecurities &underlyingSecurityCode(const std::uint32_t value)
        {
            *((std::uint32_t *)(m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
            return *this;
        }

        static SBE_CONSTEXPR std::uint16_t filler9Id() SBE_NOEXCEPT
        {
            return 209;
        }

        static SBE_CONSTEXPR std::uint64_t filler9SinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool filler9InActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= filler9SinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t filler9EncodingOffset() SBE_NOEXCEPT
        {
             return 4;
        }


        static const char *filler9MetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

        static SBE_CONSTEXPR std::int32_t filler9NullValue() SBE_NOEXCEPT
        {
            return SBE_NULLVALUE_INT32;
        }

        static SBE_CONSTEXPR std::int32_t filler9MinValue() SBE_NOEXCEPT
        {
            return -2147483647;
        }

        static SBE_CONSTEXPR std::int32_t filler9MaxValue() SBE_NOEXCEPT
        {
            return 2147483647;
        }

        static SBE_CONSTEXPR std::size_t filler9EncodingLength() SBE_NOEXCEPT
        {
            return 4;
        }

        std::int32_t filler9() const
        {
            return SBE_LITTLE_ENDIAN_ENCODE_32(*((std::int32_t *)(m_buffer + m_offset + 4)));
        }

        NoUnderlyingSecurities &filler9(const std::int32_t value)
        {
            *((std::int32_t *)(m_buffer + m_offset + 4)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
            return *this;
        }
    };

private:
    NoUnderlyingSecurities m_noUnderlyingSecurities;

public:

    static SBE_CONSTEXPR std::uint16_t noUnderlyingSecuritiesId() SBE_NOEXCEPT
    {
        return 137;
    }


    inline NoUnderlyingSecurities &noUnderlyingSecurities()
    {
        m_noUnderlyingSecurities.wrapForDecode(m_buffer, m_positionPtr, m_actingVersion, m_bufferLength);
        return m_noUnderlyingSecurities;
    }

    NoUnderlyingSecurities &noUnderlyingSecuritiesCount(const std::uint16_t count)
    {
        m_noUnderlyingSecurities.wrapForEncode(m_buffer, count, m_positionPtr, m_actingVersion, m_bufferLength);
        return m_noUnderlyingSecurities;
    }

    static SBE_CONSTEXPR std::uint64_t noUnderlyingSecuritiesSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool noUnderlyingSecuritiesInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= noUnderlyingSecuritiesSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }
};
}
}
#endif
