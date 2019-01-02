/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDC_SBE_STOCKCONNECTDAILYQUOTABALANCE_H_
#define _OMDC_SBE_STOCKCONNECTDAILYQUOTABALANCE_H_

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

class StockConnectDailyQuotaBalance
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

    inline void reset(const StockConnectDailyQuotaBalance& codec)
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

    StockConnectDailyQuotaBalance() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    StockConnectDailyQuotaBalance(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    StockConnectDailyQuotaBalance(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    StockConnectDailyQuotaBalance(const StockConnectDailyQuotaBalance& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    StockConnectDailyQuotaBalance(StockConnectDailyQuotaBalance&& codec)
    {
        reset(codec);
    }

    StockConnectDailyQuotaBalance& operator=(StockConnectDailyQuotaBalance&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    StockConnectDailyQuotaBalance& operator=(const StockConnectDailyQuotaBalance& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)20;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)80;
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

    StockConnectDailyQuotaBalance &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    StockConnectDailyQuotaBalance &wrapForDecode(
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

    StockConnectDailyQuotaBalance &putStockConnectMarket(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 0, src, sizeof(char) * 2);
        return *this;
    }

    std::string getStockConnectMarketAsString() const
    {
        std::string result(m_buffer + m_offset + 0, 2);
        return result;
    }

    StockConnectDailyQuotaBalance &putStockConnectMarket(const std::string& str)
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

    StockConnectDailyQuotaBalance &putTradingDirection(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 2, src, sizeof(char) * 2);
        return *this;
    }

    std::string getTradingDirectionAsString() const
    {
        std::string result(m_buffer + m_offset + 2, 2);
        return result;
    }

    StockConnectDailyQuotaBalance &putTradingDirection(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 2, str.c_str(), 2);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t dailyQuotaBalanceId() SBE_NOEXCEPT
    {
        return 103;
    }

    static SBE_CONSTEXPR std::uint64_t dailyQuotaBalanceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool dailyQuotaBalanceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= dailyQuotaBalanceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t dailyQuotaBalanceEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }


    static const char *dailyQuotaBalanceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::int64_t dailyQuotaBalanceNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT64;
    }

    static SBE_CONSTEXPR std::int64_t dailyQuotaBalanceMinValue() SBE_NOEXCEPT
    {
        return -9223372036854775807L;
    }

    static SBE_CONSTEXPR std::int64_t dailyQuotaBalanceMaxValue() SBE_NOEXCEPT
    {
        return 9223372036854775807L;
    }

    static SBE_CONSTEXPR std::size_t dailyQuotaBalanceEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    std::int64_t dailyQuotaBalance() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::int64_t *)(m_buffer + m_offset + 4)));
    }

    StockConnectDailyQuotaBalance &dailyQuotaBalance(const std::int64_t value)
    {
        *((std::int64_t *)(m_buffer + m_offset + 4)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t dailyQuotaBalanceTimeId() SBE_NOEXCEPT
    {
        return 104;
    }

    static SBE_CONSTEXPR std::uint64_t dailyQuotaBalanceTimeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool dailyQuotaBalanceTimeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= dailyQuotaBalanceTimeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t dailyQuotaBalanceTimeEncodingOffset() SBE_NOEXCEPT
    {
         return 12;
    }


    static const char *dailyQuotaBalanceTimeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint64_t dailyQuotaBalanceTimeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT64;
    }

    static SBE_CONSTEXPR std::uint64_t dailyQuotaBalanceTimeMinValue() SBE_NOEXCEPT
    {
        return 0x0L;
    }

    static SBE_CONSTEXPR std::uint64_t dailyQuotaBalanceTimeMaxValue() SBE_NOEXCEPT
    {
        return 0xfffffffffffffffeL;
    }

    static SBE_CONSTEXPR std::size_t dailyQuotaBalanceTimeEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    std::uint64_t dailyQuotaBalanceTime() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_64(*((std::uint64_t *)(m_buffer + m_offset + 12)));
    }

    StockConnectDailyQuotaBalance &dailyQuotaBalanceTime(const std::uint64_t value)
    {
        *((std::uint64_t *)(m_buffer + m_offset + 12)) = SBE_LITTLE_ENDIAN_ENCODE_64(value);
        return *this;
    }
};
}
}
#endif
