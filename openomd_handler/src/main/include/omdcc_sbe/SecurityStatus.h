/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDCC_SBE_SECURITYSTATUS_H_
#define _OMDCC_SBE_SECURITYSTATUS_H_

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

class SecurityStatus
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

    inline void reset(const SecurityStatus& codec)
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

    SecurityStatus() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    SecurityStatus(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    SecurityStatus(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    SecurityStatus(const SecurityStatus& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    SecurityStatus(SecurityStatus&& codec)
    {
        reset(codec);
    }

    SecurityStatus& operator=(SecurityStatus&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    SecurityStatus& operator=(const SecurityStatus& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)16;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)621;
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

    SecurityStatus &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    SecurityStatus &wrapForDecode(
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

    SecurityStatus &securityCode(const std::uint32_t value)
    {
        *((std::uint32_t *)(m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t securityTradingStatusId() SBE_NOEXCEPT
    {
        return 102;
    }

    static SBE_CONSTEXPR std::uint64_t securityTradingStatusSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool securityTradingStatusInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= securityTradingStatusSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t securityTradingStatusEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }


    static const char *securityTradingStatusMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t securityTradingStatusNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t securityTradingStatusMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t securityTradingStatusMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t securityTradingStatusEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t securityTradingStatus() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 4)));
    }

    SecurityStatus &securityTradingStatus(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 4)) = (value);
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
         return 5;
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
        return 3;
    }

    const char *filler() const
    {
        return (m_buffer + m_offset + 5);
    }

    char filler(const std::uint64_t index) const
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for filler [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 5 + (index * 1))));
    }

    void filler(const std::uint64_t index, const char value)
    {
        if (index >= 3)
        {
            throw std::runtime_error("index out of range for filler [E105]");
        }

        *((char *)(m_buffer + m_offset + 5 + (index * 1))) = (value);
    }

    std::uint64_t getFiller(char *dst, const std::uint64_t length) const
    {
        if (length > 3)
        {
             throw std::runtime_error("length too large for getFiller [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 5, sizeof(char) * length);
        return length;
    }

    SecurityStatus &putFiller(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 5, src, sizeof(char) * 3);
        return *this;
    }

    std::string getFillerAsString() const
    {
        std::string result(m_buffer + m_offset + 5, 3);
        return result;
    }

    SecurityStatus &putFiller(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 5, str.c_str(), 3);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t tradingPhaseCodeId() SBE_NOEXCEPT
    {
        return 103;
    }

    static SBE_CONSTEXPR std::uint64_t tradingPhaseCodeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool tradingPhaseCodeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= tradingPhaseCodeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t tradingPhaseCodeEncodingOffset() SBE_NOEXCEPT
    {
         return 8;
    }


    static const char *tradingPhaseCodeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char tradingPhaseCodeNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char tradingPhaseCodeMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char tradingPhaseCodeMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t tradingPhaseCodeEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t tradingPhaseCodeLength() SBE_NOEXCEPT
    {
        return 8;
    }

    const char *tradingPhaseCode() const
    {
        return (m_buffer + m_offset + 8);
    }

    char tradingPhaseCode(const std::uint64_t index) const
    {
        if (index >= 8)
        {
            throw std::runtime_error("index out of range for tradingPhaseCode [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 8 + (index * 1))));
    }

    void tradingPhaseCode(const std::uint64_t index, const char value)
    {
        if (index >= 8)
        {
            throw std::runtime_error("index out of range for tradingPhaseCode [E105]");
        }

        *((char *)(m_buffer + m_offset + 8 + (index * 1))) = (value);
    }

    std::uint64_t getTradingPhaseCode(char *dst, const std::uint64_t length) const
    {
        if (length > 8)
        {
             throw std::runtime_error("length too large for getTradingPhaseCode [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 8, sizeof(char) * length);
        return length;
    }

    SecurityStatus &putTradingPhaseCode(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 8, src, sizeof(char) * 8);
        return *this;
    }

    std::string getTradingPhaseCodeAsString() const
    {
        std::string result(m_buffer + m_offset + 8, 8);
        return result;
    }

    SecurityStatus &putTradingPhaseCode(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 8, str.c_str(), 8);
        return *this;
    }

};
}
}
#endif
