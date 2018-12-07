/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _OMDD_SBE_MARKETALERT_H_
#define _OMDD_SBE_MARKETALERT_H_

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

using namespace sbe;

namespace omdd {
namespace sbe {

class MarketAlert
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

    inline void reset(const MarketAlert& codec)
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

    MarketAlert() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    MarketAlert(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    MarketAlert(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    MarketAlert(const MarketAlert& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    MarketAlert(MarketAlert&& codec)
    {
        reset(codec);
    }

    MarketAlert& operator=(MarketAlert&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    MarketAlert& operator=(const MarketAlert& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)327;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)323;
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

    MarketAlert &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    MarketAlert &wrapForDecode(
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

    static SBE_CONSTEXPR std::uint16_t alertIDId() SBE_NOEXCEPT
    {
        return 101;
    }

    static SBE_CONSTEXPR std::uint64_t alertIDSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool alertIDInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= alertIDSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t alertIDEncodingOffset() SBE_NOEXCEPT
    {
         return 0;
    }


    static const char *alertIDMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t alertIDNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t alertIDMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t alertIDMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t alertIDEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t alertID() const
    {
        return SBE_LITTLE_ENDIAN_ENCODE_16(*((std::uint16_t *)(m_buffer + m_offset + 0)));
    }

    MarketAlert &alertID(const std::uint16_t value)
    {
        *((std::uint16_t *)(m_buffer + m_offset + 0)) = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sourceId() SBE_NOEXCEPT
    {
        return 102;
    }

    static SBE_CONSTEXPR std::uint64_t sourceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool sourceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= sourceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t sourceEncodingOffset() SBE_NOEXCEPT
    {
         return 2;
    }


    static const char *sourceMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char sourceNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char sourceMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char sourceMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t sourceEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char source() const
    {
        return (*((char *)(m_buffer + m_offset + 2)));
    }

    MarketAlert &source(const char value)
    {
        *((char *)(m_buffer + m_offset + 2)) = (value);
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
         return 3;
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

    static SBE_CONSTEXPR std::uint8_t fillerNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t fillerMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t fillerMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t fillerEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t filler() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 3)));
    }

    MarketAlert &filler(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 3)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t headerId() SBE_NOEXCEPT
    {
        return 103;
    }

    static SBE_CONSTEXPR std::uint64_t headerSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool headerInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= headerSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t headerEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }


    static const char *headerMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char headerNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char headerMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char headerMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t headerEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint64_t headerLength() SBE_NOEXCEPT
    {
        return 320;
    }

    const char *header() const
    {
        return (m_buffer + m_offset + 4);
    }

    char header(const std::uint64_t index) const
    {
        if (index >= 320)
        {
            throw std::runtime_error("index out of range for header [E104]");
        }

        return (*((char *)(m_buffer + m_offset + 4 + (index * 1))));
    }

    void header(const std::uint64_t index, const char value)
    {
        if (index >= 320)
        {
            throw std::runtime_error("index out of range for header [E105]");
        }

        *((char *)(m_buffer + m_offset + 4 + (index * 1))) = (value);
    }

    std::uint64_t getHeader(char *dst, const std::uint64_t length) const
    {
        if (length > 320)
        {
             throw std::runtime_error("length too large for getHeader [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 4, sizeof(char) * length);
        return length;
    }

    MarketAlert &putHeader(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 4, src, sizeof(char) * 320);
        return *this;
    }

    std::string getHeaderAsString() const
    {
        std::string result(m_buffer + m_offset + 4, 320);
        return result;
    }

    MarketAlert &putHeader(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 4, str.c_str(), 320);
        return *this;
    }


    static SBE_CONSTEXPR std::uint16_t lastFragmentId() SBE_NOEXCEPT
    {
        return 104;
    }

    static SBE_CONSTEXPR std::uint64_t lastFragmentSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool lastFragmentInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= lastFragmentSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t lastFragmentEncodingOffset() SBE_NOEXCEPT
    {
         return 324;
    }


    static const char *lastFragmentMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR char lastFragmentNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char lastFragmentMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char lastFragmentMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t lastFragmentEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    char lastFragment() const
    {
        return (*((char *)(m_buffer + m_offset + 324)));
    }

    MarketAlert &lastFragment(const char value)
    {
        *((char *)(m_buffer + m_offset + 324)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t intoTypeId() SBE_NOEXCEPT
    {
        return 105;
    }

    static SBE_CONSTEXPR std::uint64_t intoTypeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool intoTypeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= intoTypeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t intoTypeEncodingOffset() SBE_NOEXCEPT
    {
         return 325;
    }


    static const char *intoTypeMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t intoTypeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t intoTypeMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t intoTypeMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t intoTypeEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t intoType() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 325)));
    }

    MarketAlert &intoType(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 325)) = (value);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t priorityId() SBE_NOEXCEPT
    {
        return 106;
    }

    static SBE_CONSTEXPR std::uint64_t prioritySinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool priorityInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= prioritySinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t priorityEncodingOffset() SBE_NOEXCEPT
    {
         return 326;
    }


    static const char *priorityMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint8_t priorityNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t priorityMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t priorityMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t priorityEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    std::uint8_t priority() const
    {
        return (*((std::uint8_t *)(m_buffer + m_offset + 326)));
    }

    MarketAlert &priority(const std::uint8_t value)
    {
        *((std::uint8_t *)(m_buffer + m_offset + 326)) = (value);
        return *this;
    }

    class NoLines
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
        GroupSize8 m_dimensions;

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

        inline void wrapForEncode(char *buffer, const std::uint8_t count, std::uint64_t *pos, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
        {
    #if defined(__GNUG__) && !defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wtype-limits"
    #endif
            if (count < 0 || count > 254)
            {
                throw std::runtime_error("count outside of allowed range [E110]");
            }
    #if defined(__GNUG__) && !defined(__clang__)
    #pragma GCC diagnostic pop
    #endif
            m_buffer = buffer;
            m_bufferLength = bufferLength;
            m_dimensions.wrap(m_buffer, *pos, actingVersion, bufferLength);
            m_dimensions.blockLength((std::uint8_t)320);
            m_dimensions.numInGroup((std::uint8_t)count);
            m_index = -1;
            m_count = count;
            m_blockLength = 320;
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
            return 320;
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

        inline NoLines &next()
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


        static SBE_CONSTEXPR std::uint16_t contentId() SBE_NOEXCEPT
        {
            return 108;
        }

        static SBE_CONSTEXPR std::uint64_t contentSinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool contentInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= contentSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t contentEncodingOffset() SBE_NOEXCEPT
        {
             return 0;
        }


        static const char *contentMetaAttribute(const MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

        static SBE_CONSTEXPR char contentNullValue() SBE_NOEXCEPT
        {
            return (char)0;
        }

        static SBE_CONSTEXPR char contentMinValue() SBE_NOEXCEPT
        {
            return (char)32;
        }

        static SBE_CONSTEXPR char contentMaxValue() SBE_NOEXCEPT
        {
            return (char)126;
        }

        static SBE_CONSTEXPR std::size_t contentEncodingLength() SBE_NOEXCEPT
        {
            return 1;
        }

        static SBE_CONSTEXPR std::uint64_t contentLength() SBE_NOEXCEPT
        {
            return 320;
        }

        const char *content() const
        {
            return (m_buffer + m_offset + 0);
        }

        char content(const std::uint64_t index) const
        {
            if (index >= 320)
            {
                throw std::runtime_error("index out of range for content [E104]");
            }

            return (*((char *)(m_buffer + m_offset + 0 + (index * 1))));
        }

        void content(const std::uint64_t index, const char value)
        {
            if (index >= 320)
            {
                throw std::runtime_error("index out of range for content [E105]");
            }

            *((char *)(m_buffer + m_offset + 0 + (index * 1))) = (value);
        }

        std::uint64_t getContent(char *dst, const std::uint64_t length) const
        {
            if (length > 320)
            {
                 throw std::runtime_error("length too large for getContent [E106]");
            }

            std::memcpy(dst, m_buffer + m_offset + 0, sizeof(char) * length);
            return length;
        }

        NoLines &putContent(const char *src)
        {
            std::memcpy(m_buffer + m_offset + 0, src, sizeof(char) * 320);
            return *this;
        }

        std::string getContentAsString() const
        {
            std::string result(m_buffer + m_offset + 0, 320);
            return result;
        }

        NoLines &putContent(const std::string& str)
        {
            std::memcpy(m_buffer + m_offset + 0, str.c_str(), 320);
            return *this;
        }

    };

private:
    NoLines m_noLines;

public:

    static SBE_CONSTEXPR std::uint16_t noLinesId() SBE_NOEXCEPT
    {
        return 107;
    }


    inline NoLines &noLines()
    {
        m_noLines.wrapForDecode(m_buffer, m_positionPtr, m_actingVersion, m_bufferLength);
        return m_noLines;
    }

    NoLines &noLinesCount(const std::uint8_t count)
    {
        m_noLines.wrapForEncode(m_buffer, count, m_positionPtr, m_actingVersion, m_bufferLength);
        return m_noLines;
    }

    static SBE_CONSTEXPR std::uint64_t noLinesSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool noLinesInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= noLinesSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }
};
}
}
#endif
