/*
 * ipv4.hpp
 *
 * Created by Rohit Saluja on 3/24/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#ifndef IPV4_H_
#define IPV4_H_

#include <iostream>
#include <cstdint>

using namespace std;

/*
 * @brief
 * Length os different components of ipv4 header
 */
#define Ipv4AddrLen     4
#define Ipv4MinLen      20
#define Ipv4Version     4

/*
 * @brief
 * Class for Ipv4 addrerss of packet
 */
class Ipv4Addr {
    private:
    uint8_t addr[Ipv4AddrLen];

    public:
    Ipv4Addr (void);
    Ipv4Addr (uint8_t const *pkt);
    uint8_t const * Addr (void) const;
    friend ostream & operator<< (ostream &output, Ipv4Addr const &addr);
    friend bool const operator== (Ipv4Addr const &lhs, Ipv4Addr const &rhs);
    friend bool const operator!= (Ipv4Addr const &lhs, Ipv4Addr const &rhs);
};

/*
 * @brief
 * Different layer3 proto values
 */
#define IP_PROTO_ICMP   1
#define IP_PROTO_IGMP   2
#define IP_PROTO_TCP    6
#define IP_PROTO_UDP    17

/*
 * @brief
 * Class for layer3-proto of packet
 */
class L3Proto {
    private:
    uint8_t proto;

    public:
    L3Proto (void);
    L3Proto (const uint8_t val);
    uint8_t const Proto (void) const;
    string const Name (void) const;
    friend ostream & operator<< (ostream &output, L3Proto const &proto);
    friend bool const operator== (L3Proto const &lhs, L3Proto const &rhs);
    friend bool const operator!= (L3Proto const &lhs, L3Proto const &rhs);
};

/*
 * @brief
 * Class for ipv4 flag
 */
class Ipv4Flag {
    private:
    uint8_t flag:3;

    public:
    Ipv4Flag (void);
    Ipv4Flag (const uint8_t val);
    uint8_t const Flag (void) const;
    string const Name (void) const;
    friend ostream & operator<< (ostream &output, Ipv4Flag const &flag);
    friend bool const operator== (Ipv4Flag const &lhs, Ipv4Flag const &rhs);
    friend bool const operator!= (Ipv4Flag const &lhs, Ipv4Flag const &rhs);
};

/*
 * @brief
 * Different flag names
 */
#define IPV4_FLAG_RSVD  0
#define IPV4_FLAG_DF    1
#define IPV4_FLAG_MF    2

/*
 * @brief
 * Class for ipv4 of packet
 */
class Ipv4 {
    private:
    uint8_t ver:4;
    uint8_t ihl:4;
    uint8_t dscp:6;
    uint8_t ecn:2;
    uint16_t len;
    uint16_t id;
    Ipv4Flag flag;
    uint16_t off:13;
    uint8_t ttl;
    L3Proto proto;
    uint16_t chksum;
    Ipv4Addr srcip;
    Ipv4Addr dstip;
    uint32_t const FieldSum (void) const;
    uint16_t const SumToUint16 (uint32_t sum) const;

    public:
    Ipv4 (void);
    Ipv4 (const uint8_t * pkt);
    uint8_t const Ihl (void) const;
    uint8_t const Dscp (void) const;
    uint8_t const Ecn (void) const;
    uint16_t const Len (void) const;
    uint16_t const Id (void) const;
    Ipv4Flag const Flag (void) const;
    uint16_t const Off (void) const;
    uint8_t const Ttl (void) const;
    L3Proto const Proto (void) const;
    uint16_t const Chksum (void) const;
    Ipv4Addr const SrcIp (void) const;
    Ipv4Addr const DstIp (void) const;
    void GenChksum (void);
    bool const VerifyChksum (void) const;
    bool const isValid (void) const;
    void print (const uint8_t ls=0) const;
    uint8_t const * HexDump (void) const;
    friend bool const operator== (Ipv4 const &lhs, Ipv4 const &rhs);
    friend bool const operator!= (Ipv4 const &lhs, Ipv4 const &rhs);
};

#endif  // IPV4_H_
