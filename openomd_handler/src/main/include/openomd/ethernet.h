#pragma once
#include <cstdint>

namespace openomd
{
const size_t ETHERNET_MAX_PAYLOAD = 0xffff;
constexpr auto ETHER_ADDR_LEN = 6;;

#if !defined(ETHERTYPE_IP)
#define ETHERTYPE_IP 0x0800
#endif

#if !defined(ETHERTYPE_VLAN)
#define ETHERTYPE_VLAN 0x8100
#endif

#if defined(__linux__)
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#define BEGIN_PACK
#define END_PACK      __attribute__((__packed__));
BEGIN_PACK
struct vlan_header {
    uint8_t ether_dhost[ETH_ALEN];
    uint8_t ether_shost[ETH_ALEN];
    uint16_t h_vlan_proto;
    uint16_t h_vlan_TCI;
    uint16_t ether_type;
}
END_PACK
#else
#define BEGIN_PACK __pragma(pack(push, 1))
#define END_PACK   ; __pragma(pack(pop))
#endif

BEGIN_PACK
struct EthernetHdr
{
    uint8_t ether_dhost[ETHER_ADDR_LEN];
    uint8_t ether_short[ETHER_ADDR_LEN];
    uint16_t ether_type;
}
END_PACK

BEGIN_PACK
struct IpHdr
{
    uint8_t ip_vhl; // header length, version
#define IP_V(ip) (((ip)->ip_vhl & 0xf0) >> 4)
#define IP_HL(ip) ((ip)->ip_vhl & 0x0f)
    uint8_t ip_tos; // type of service
    uint16_t ip_len;    // total length
    uint16_t ip_id;     // identification
    uint16_t ip_off;    // fragment offset field
#define IP_DF 0x4000    // dont fragement flag
#define IP_MF 0x2000    // more fragments flag
#define IP_OFFMASK 0x1fff   // mask for fragmenting bits
    uint8_t ip_ttl;     // time to live
    uint8_t ip_p;       // protocol
    uint16_t up_sum;    // checksum
    struct in_addr ip_src, ip_dst;  //source and dest address
}
END_PACK

BEGIN_PACK
struct UdpHdr : public IpHdr
{
    uint16_t uh_sport;  // source port
    uint16_t uh_dport;  // destination port
    uint16_t uh_ulen;   // udp length
    uint16_t uh_sum;    // udp checksum
}
END_PACK

BEGIN_PACK
template <size_t _Size = ETHERNET_MAX_PAYLOAD>
struct UdpFrame
{
    UdpHdr _hdr;
    uint8_t _payload[_Size];
}
END_PACK

BEGIN_PACK
struct TcpHdr : public IpHdr
{
    uint16_t th_sport;  // source port
    uint16_t th_dport;  // destionation port
    uint32_t th_seq;    // sequence number
    uint32_t th_ack;    // acknowledgement number
    uint8_t th_offx2;   // data offset, rsvd
    uint8_t th_flags;
    uint16_t th_win;    // window
    uint16_t th_sum;    // checksum
    uint16_t th_urp;    // urgent pointer
}
END_PACK

BEGIN_PACK
template <size_t _Size = ETHERNET_MAX_PAYLOAD>
struct TcpFrame
{
    TcpHdr _hdr;
    uint8_t _payload[_Size];
}
END_PACK
}
