/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDC_SBE_STOCKCONNECTMARKETTURNOVER_H_
#define _OMDC_SBE_STOCKCONNECTMARKETTURNOVER_H_

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

class StockConnectMarketTurnover
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

    inline void reset(const StockConnectMarketTurnover& codec)
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

    StockConnectMarketTurnover() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    StockConnectMarketTurnover(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    StockConnectMarketTurnover(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    StockConnectMarketTurnover(const StockConnectMarketTurnover& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    StockConnectMarketTurnover(StockConnectMarketTurnover&& codec)
    {
        reset(codec);
    }

    StockConnectMarketTurnover& operator=(StockConnectMarketTurnover&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    StockConnectMarketTurnover& operator=(const StockConnectMarketTurnover& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)28;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)81;
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

    StockConnectMarketTurnover &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    StockConnectMarketTurnover &wrapForDecode(
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

    static SBE_CONSTEXPR std::uint16_t stockConnectMarketId() SBE_NOEXCEPT
    {
        return 101;
    }

    static SBE_CONSTEXPR std::uint64_t stockConnectMarketSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool stockConnectMarketInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= stockConnectMarketSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t stockConnectMarketEncodingOffset() SBE_NOEXCEPT
    {
         return 0;
    }


    static const char *stockConnectMarketMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char stockConnectMarketNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char stockConnectMarketMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char stockConnectMarketMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t stockConnectMarketEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t stockConnectMarketLength() SBE_NOEXCEPT
    {
        return 2;
    }

    const char *stockConnectMarket() const
    {
        return (m_buffer + m_offset + 0);
    }

    char stockConnectMarket(const std::uint64_t index) const
    {
        if (index >= 2)
        {
            throw std::runtime_error("index out of range for stockConnectMarket [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 0 + (index * 1))));
    }

    void stockConnectMarket(const std::uint64_t index, const char value)
    {
        if (index >= 2)
        {
            throw std::runtime_error("index out of range for stockConnectMarket [E105]");
        }

        *((char *)(m_buffer + m_offset + 0 + (index * 1))) = (value);
    }

    std::uint64_t getStockConnectMarket(char *dst, const std::uint64_t length) const
    {
        if (length > 2)
        {
             throw std::runtime_error("length too large for getStockConnectMarket [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 0, sizeof(char) * length);
        return length;
    }

    StockConnectMarketTurnover &putStockConnectMarket(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 0, src, sizeof(char) * 2);
        return *this;
    }

    std::string getStockConnectMarketAsString() const
    {
        std::string result(m_buffer + m_offset + 0, 2);
        return result;
    }

    StockConnectMarketTurnover &putStockConnectMarket(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 0, str.c_str(), 2);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t tradingDirectionId() SBE_NOEXCEPT
    {
        return 102;
    }

    static SBE_CONSTEXPR std::uint64_t tradingDirectionSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool tradingDirectionInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= tradingDirectionSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t tradingDirectionEncodingOffset() SBE_NOEXCEPT
    {
         return 2;
    }


    static const char *tradingDirectionMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char tradingDirectionNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char tradingDirectionMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char tradingDirectionMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t tradingDirectionEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t tradingDirectionLength() SBE_NOEXCEPT
    {
        return 2;
    }

    const char *tradingDirection() const
    {
        return (m_buffer + m_offset + 2);
    }

    char tradingDirection(const std::uint64_t index) const
    {
        if (index >= 2)
        {
            throw std::runtime_error("index out of range for tradingDirection [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 2 + (index * 1))));
    }

    void tradingDirection(const std::uint64_t index, const char value)
    {
        if (index >= 2)
        {
            throw std::runtime_error("index out of range for tradingDirection [E105]");
        }

        *((char *)(m_buffer + m_offset + 2 + (index * 1))) = (value);
    }

    std::uint64_t getTradingDirection(char *dst, const std::uint64_t length) const
    {
        if (length > 2)
        {
             throw std::runtime_error("length too large for getTradingDirection [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 2, sizeof(char) * length);
        return length;
    }

    StockConnectMarketTurnover &putTradingDirection(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 2, src, sizeof(char) * 2);
        return *this;
    }

    std::string getTradingDirectionAsString() const
    {
        std::string result(m_buffer + m_offset + 2, 2);
        return result;
    }

    StockConnectMarketTurnover &putTradingDirection(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 2, str.c_str(), 2);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t buyTurnoverId() SBE_NOEXCEPT
    {
        return 103;
    }

    static SBE_CONSTEXPR std::uint64_t buyTurnoverSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool buyTurnoverInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= buyTurnoverSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t buyTurnoverEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }


    static const char *buyTurnoverMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int64_t buyTurnoverNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT64;
    }

    static SBE_CONSTEXPR std::int64_t buyTurnoverMinValue() SBE_NOEXCEPT
    {
        return -9223372036854775807L;
    }

    static SBE_CONSTEXPR std::int64_t buyTurnoverMaxValue() SBE_NOEXCEPT
    {
        return 9223372036854775807L;
    }

    static SBE_CONSTEXPR std::size_t buyTurnoverEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    std::int64_t buyTurnover() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::int64_t *)(m_buffer + m_offset + 4)));
    }

    StockConnectMarketTurnover &buyTurnover(const std::int64_t value)
    {
        *((std::int64_t *)(m_buffer + m_offset + 4)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sellTurnoverId() SBE_NOEXCEPT
    {
        return 104;
    }

    static SBE_CONSTEXPR std::uint64_t sellTurnoverSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool sellTurnoverInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= sellTurnoverSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t sellTurnoverEncodingOffset() SBE_NOEXCEPT
    {
         return 12;
    }


    static const char *sellTurnoverMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int64_t sellTurnoverNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT64;
    }

    static SBE_CONSTEXPR std::int64_t sellTurnoverMinValue() SBE_NOEXCEPT
    {
        return -9223372036854775807L;
    }

    static SBE_CONSTEXPR std::int64_t sellTurnoverMaxValue() SBE_NOEXCEPT
    {
        return 9223372036854775807L;
    }

    static SBE_CONSTEXPR std::size_t sellTurnoverEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    std::int64_t sellTurnover() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::int64_t *)(m_buffer + m_offset + 12)));
    }

    StockConnectMarketTurnover &sellTurnover(const std::int64_t value)
    {
        *((std::int64_t *)(m_buffer + m_offset + 12)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t buySellTurnoverId() SBE_NOEXCEPT
    {
        return 105;
    }

    static SBE_CONSTEXPR std::uint64_t buySellTurnoverSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool buySellTurnoverInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= buySellTurnoverSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t buySellTurnoverEncodingOffset() SBE_NOEXCEPT
    {
         return 20;
    }


    static const char *buySellTurnoverMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int64_t buySellTurnoverNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT64;
    }

    static SBE_CONSTEXPR std::int64_t buySellTurnoverMinValue() SBE_NOEXCEPT
    {
        return -9223372036854775807L;
    }

    static SBE_CONSTEXPR std::int64_t buySellTurnoverMaxValue() SBE_NOEXCEPT
    {
        return 9223372036854775807L;
    }

    static SBE_CONSTEXPR std::size_t buySellTurnoverEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    std::int64_t buySellTurnover() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::int64_t *)(m_buffer + m_offset + 20)));
    }

    StockConnectMarketTurnover &buySellTurnover(const std::int64_t value)
    {
        *((std::int64_t *)(m_buffer + m_offset + 20)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }
};
}
}
#endif
